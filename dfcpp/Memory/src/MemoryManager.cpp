#include "MemoryManager.h"

namespace D_Memory{

MemoryManager::MemoryManager(){

}

MemoryManager::~MemoryManager(){

}

/*
    分配空闲的block给对应的线程
    
    @size : 分配的大小
    @thread_id : 线程id
    @numa_id : numa结点id
*/
void * MemoryManager::alloc(int size)
{
    /* 向系统申请一块 */
    void * ptr = nullptr;
    /* 在numa结点对应的交换空间内搜索满足条件的partial_block */
        /* 遍历partial_block */
            /*
                如果能找到，那么就将这个block挂在到本地缓存中(block和其附带的缓存block也要记录)

                找不到就从系统申请block，然后挂在到本地缓存中
            */

    
    /* 这里是向系统申请了 */
    // ptr = numa_alloc_onnode(size, numa_node_of_cpu(sched_getcpu()));
    // printf("the first alloc address is %p \n", ptr);
    // ptr = numa_alloc_onnode(size, numa_node_of_cpu(sched_getcpu()));
    // printf("the second alloc address is %p \n", ptr);
    // ptr = numa_alloc_onnode(size, numa_node_of_cpu(sched_getcpu()));
    // printf("the second alloc address is %p \n", ptr);
    /* 修改header的superblock指针 */
    return ptr;

}

/* 
    释放线程对应的block，执行这个函数的情况是，当A线程将block占满后丢弃对该block的控制权，一旦有线程释放，就会存放到交换   
    区，此时block还是未上锁状态(同样也是未分配状态)。其他线程通过这个接口直接释放对应的block。当这个block被其他的线程申请到 
    并上锁时，如果有其他的线程再次释放，就会直接缓存下来此次的释放，等到用这个block的线程把他切换出来时再集中释放。

    @ptr : 释放的block的地址
    @thread_id : 线程id
    @numa_id : numa结点id
*/
void MemoryManager::free(void * ptr)
{

}

/* 
    交换空间数据不足时向系统申请内存块
    当线程本地缓存没有数据，且交换空间也没有数据时，就会向系统申请内存块，且直接将申请到的内存块返回给线程缓存，不会放入交换空间
    @size : 申请的大小
*/
void * MemoryManager::alloc_from_system(int size)
{
    /* 
        判断size的大小是否属于slab管理的范围
            如果属于，申请对应的Superblock，然后将这个block直接挂载给线程缓存
        

        大数据的情况下使用大页模式
    */
}

MemoryManager* MemoryManager::get_instance()
{
    static MemoryManager instance;
    return &instance;
}

}