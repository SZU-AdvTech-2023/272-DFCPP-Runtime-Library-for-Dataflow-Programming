#include <iostream>
#include "MemoryAllocator.h"
#include <pthread.h>
#include <unistd.h>
extern int i;


void* threadFunction(void* arg) {
    // 在新线程中打印线程ID
    printf("Thread ID: %lu\n", (unsigned long)pthread_self());
    int * malloc_ptr = (int *)malloc(sizeof(int));
    // 其他线程逻辑

    return NULL;
}

int main() {
    std::cout << "Hello, world!" << std::endl;
    // int * ptr = new int;
    // delete ptr;

    int * malloc_ptr = (int *)malloc(15);

    *malloc_ptr = 1;
    std::cout << *malloc_ptr << std::endl;
    free(malloc_ptr);

    // 获取当前进程的 ID
    pid_t processId = getpid();
    // 打印进程 ID
    std::cout << "Process ID: " << processId << std::endl;

    void * ptr;
    ptr = numa_alloc_onnode(15, numa_node_of_cpu(sched_getcpu()));
    printf("the main first alloc address is %p \n", ptr);
    ptr = numa_alloc_onnode(15, numa_node_of_cpu(sched_getcpu()));
    printf("the main second alloc address is %p \n", ptr);
    ptr = numa_alloc_onnode(15, numa_node_of_cpu(sched_getcpu()));
    printf("the main third alloc address is %p \n", ptr);

    while(1)
    {

    }
    // int * malloc_ptr_2 = (int *)malloc(size of(int));
    // *malloc_ptr = 2;
    // std::cout << *malloc_ptr << std::endl;
    // free(malloc_ptr);

    // std::cout << i << std::endl;
    // pthread_t thread;
    // // 调用 pthread_create 创建新线程
    // if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
    //     fprintf(stderr, "Failed to create thread\n");
    //     return 1;
    // }
    // // 等待新线程结束
    // if (pthread_join(thread, NULL) != 0) {
    //     fprintf(stderr, "Failed to join thread\n");
    //     return 1;
    // }

    return 0;
}