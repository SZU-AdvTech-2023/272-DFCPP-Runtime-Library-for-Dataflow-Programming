#include "Superblock.h"

namespace D_Memory{

Superblock::Superblock(int size):object_size(size)
{

}

Superblock::~Superblock()
{

}


/* 从超级块中获取内存 */
void * Superblock::alloc(int size)
{
    void *ptr = nullptr;
    ptr = numa_alloc_onnode(size, numa_node_of_cpu(sched_getcpu()));
    printf("the first alloc address is %p \n", ptr);
    ptr = numa_alloc_onnode(size, numa_node_of_cpu(sched_getcpu()));
    printf("the second alloc address is %p \n", ptr);
    /* 看看超级块地址是否还有空闲位置，如果有，指针偏移后将地址返回*/
    /* 如果没有，地址后3位可以用做标记为，是否为全新超级块或是交换空间的残块 */
        /* 若是残块，向交换空间发起空闲队列查询请求，更新空闲队列(空闲到一定数量才会解锁) */

    /* 没有的话则向交换空间申请一个新的超级块，将地址返回 */

    return ptr;
}   


void Superblock::free(void * ptr)
{
    threadBuffer_ptr->free(ptr);
    return;

}

}