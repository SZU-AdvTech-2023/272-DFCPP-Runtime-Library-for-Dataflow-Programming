/* 
    @date   :  2023/12/28
    @author :  Tlx
    @brief  :  线程本地缓存区，用于存放线程的内存块
*/

#include "ThreadBuffer.h"

namespace D_Memory{

ThreadBuffer::ThreadBuffer(){
    /* 初始化空闲内存块链表 */
    freelist.next = nullptr;
    std::cout << "i coming " << std::endl;
    
}

ThreadBuffer::~ThreadBuffer(){

}


/* 
    申请内存 
    @size : 申请的大小
    
    函数先在本地缓存的空闲内存块中查找，如果为空则搜索本地的超级块，若还是没有则将请求转发给管理器
*/
void * ThreadBuffer::alloc(int size)
{
    void * ptr = nullptr;
    
    /* 先去空闲内存块链表查找 */
    if(freelist.next != nullptr){
        /* 有的话就直接返回 */
        ptr = freelist.next;
        freelist.next = freelist.next->next;
        std::cout<< "malloc from loacl freelist : " << ptr << std::endl;
        return ptr;
    }
    else{
        /* 先判断超级快存不存在 */
        if(unlikely(!superblock_ptr)) return nullptr;
        else { 
            ptr = superblock_ptr->alloc(size); 
            std::cout << "malloc form local suplerblock : " << ptr << std::endl;
        }
    }
    return ptr;
}

/* 分配内存 */
void ThreadBuffer::free(void * ptr)
{
    /* 将缓存信息加入的空闲链表中 */
    FreeThreadBuffer * free_ptr = (FreeThreadBuffer *)ptr;
    free_ptr->next = freelist.next;
    freelist.next = free_ptr;
    std::cout << "free_ptr->next : " << free_ptr->next << std::endl;
}

}