/* 
    @date   :  2023/12/26
    @Author :  Tlx
    @Brief  :  暴露出来的内存接口，转接申请到本地的线程缓存区
*/

#include <numa.h>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <pthread.h>
#include <dlfcn.h> 
#include "ThreadBufferHeader.h"
#include "MemoryManager.h"
/* 
    这里暂时试验了一下功能，之后要跳转至线程的本地缓存区中
    （这里要开的应该是一个本地缓存堆，根据malloc申请的大小进入到对应大小的ThreadBuffer中）
    找不到的话再通过ThreadBufferHeader跳转至交换空间去申请数据
    交换空间处的链表要怎么存储是个问题？
    准备一个块存放地址链表还是？这样子的话多个数据就会争抢锁？
    已经确定的事情是，单个超级块为32764，不同bin之间的超级快容纳个数不同，一次性分配多个超级快存放在交换空间中，所以空闲的超级快可以有自己的空间，指向下一个空闲的超级快，但是对于半满的超级快，这个不行，因为接管一个超级块，这个freelist是要有地方存的(所以得开个16的块，一个地址一个是对于的freelist，要不要分bin？没必要好像，因为块的大小是一致的)。对于大数据的情况，直接丢给默认的内存分配器算了，或者后面通过mmap的方式来
*/
using D_Memory::ThreadBufferHeader;

using D_Memory::MemoryManager;
MemoryManager* _memoryManager_ptr = nullptr;

#define BUFFER_SIZE (sizeof(ThreadBufferHeader) / sizeof(double) + 1)
#define INITIAL_EXEC_ATTR __attribute__((tls_model ("initial-exec")))

static __thread double _local_heap[BUFFER_SIZE] INITIAL_EXEC_ATTR;      // 本地缓存区
static __thread ThreadBufferHeader* _threadBufferHeader_ptr = nullptr; // 重构对象

void* _xxmalloc(size_t size) {
    std::cout << "Custom new: Allocating " << size << " bytes" << std::endl;
    return _threadBufferHeader_ptr->alloc(size);
}

// 释放对应的内存块，同理，也要先跳转至线程的本地缓存区
void _xxfree(void* ptr) {
    return _threadBufferHeader_ptr->free(ptr);
}


void* operator new(std::size_t size) {
    std::cout << "Custom new: Allocating " << size << " bytes" << std::endl;
    void* ptr = numa_alloc_onnode(size, numa_node_of_cpu(sched_getcpu()));
    return ptr;
}

void operator delete(void* ptr) noexcept {
    std::cout << "Custom delete: Freeing memory" << std::endl;
    numa_free(ptr, numa_node_of_cpu(sched_getcpu()));
}


// 初始化函数，使用 __attribute__((constructor)) 使其在程序加载时自动执行
static void init() __attribute__((constructor));


extern "C" void* show(void* arg)
{   
    fprintf(stderr,"show:\n");
    new (reinterpret_cast<char *>(&_local_heap)) ThreadBufferHeader(_memoryManager_ptr);
    _threadBufferHeader_ptr = reinterpret_cast<ThreadBufferHeader *>(&_local_heap);
    return nullptr;
}

// // 初始化逻辑
// // 这里按道理是要初始化一个交换空间的数据出来的
void init() {
    /*  初始化交换空间 */
    if(!_memoryManager_ptr) _memoryManager_ptr=MemoryManager::get_instance();
    show(nullptr);
}


// /* 重构的线程创建函数----------------------------------------------------------------- */

// // 原始的pthread_create函数
// typedef int (*pthread_create_type)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*);
// // 自定义的线程数据结构
// struct ThreadData {
//     pthread_create_type original_pthread_create; // 原始的pthread_create函数
//     void* (*start_routine)(void*); // 函数指针，指向线程执行的函数
//     void* arg; // 函数的参数
// };

// // 重定义的pthread_create函数
// extern "C" int pthread_create(pthread_t* thread, const pthread_attr_t* attr,
//                                void* (*start_routine)(void*), void* arg) {
//     // 获取原始的pthread_create函数地址
//     pthread_create_type original_pthread_create = (pthread_create_type)dlsym(RTLD_NEXT, "pthread_create");
//     if (original_pthread_create == nullptr) {
//         std::cerr << "Failed to get the address of pthread_create" << std::endl;
//         return -1;
//     }

//     // 创建一个结构体，用于传递给线程的参数
//     ThreadData* threadData = new ThreadData{original_pthread_create, start_routine, arg};

//     // 在调用真正的pthread_create之前执行一些操作
//     std::cout << "Before calling pthread_create, calling show function" << std::endl;

//     // 调用原始的pthread_create函数
//     int result = original_pthread_create(thread, attr, [](void* data) -> void* {
//         ThreadData* threadData = static_cast<ThreadData*>(data);
        
//         // 在新线程的执行函数中调用原始的线程执行函数和show函数
//         show(threadData->arg);
//         void* result = threadData->start_routine(threadData->arg);
        
//         delete threadData; // 释放为线程参数分配的内存
//         return result;
//     }, threadData);

//     if (result != 0) {
//         std::cerr << "Failed to create thread" << std::endl;
//         delete threadData;
//     }

//     return result;
// }