/* 
    @Date   : 2023/12/26
    @Author : Tlx
    @Brief  : 内存管理器，将数据空间划分为User Space 和 Swap Space
*/


#ifndef DFCPP_MEMORYMANAGER_H
#define DFCPP_MEMORYMANAGER_H
#include <numa.h>

/* 调试添加 */
#include <numa.h>
#include <iostream>
/* 调试添加 */

namespace D_Memory{

/*  
    @全局的内存管理器 
    @负责调度用户空间和交换空间的内存块置换、分配和申请 
    @用户不会直接和管理器打交道，前面暴露出来的那个抽象接口也只会和线程本地的存储打交道，当线程本地存储的资源不够分配时，再由线程 
    向此管理器申请资源
    @管理器会维护一个交换空间，负责调控同一Numa结点之间的内存申请
    @此处的管理数据存放在程序数据段中
    @这里不必管理交换空间中的全满块，释放的时候通过地址判断加入进对应的链表中就可以
*/

/* 单例模式 */
class MemoryManager{
    
public:
    /* 公有接口函数 */
    void * alloc(int size);     /* 分配空闲的block给对应的线程 */
    void free(void * ptr);      /* 释放线程对应的block */   

    static MemoryManager * get_instance();                  /* 获取单例对象 */
      
    

private:

    MemoryManager();
    ~MemoryManager();
    /* 内部接口函数 */
    void * alloc_from_system(int size);     /* 交换空间数据不足时向系统申请内存块 */


    /* 成员变量 */
    /* 这里要根据大小来区分不同的链表 32768 */
    void ** partial_block;  /* 达到分配条件半满的内存块链表*/
    void ** freeze_block;   /* 冻结的内存块链表，此时有空闲块，但块数过少还没有达到分配条件 */
    void ** free_block;     /* 空闲的内存块链表，总数维持在一个固定的值，用于平衡程序的内存申请 */
};



}
#endif