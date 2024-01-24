#ifndef DFCPP_CONFIG_H
#define DFCPP_CONFIG_H

#define SUPERBLOCK_SIZE 32768*2   // 每个超级块的大小
#define SMALL_SIZE 16384        // 小对象的大小
#define ALLOC_SIZE  262144      // 一次向系统申请的内存大小
#define BINS 11                 // 小对象的阶数 


#ifdef __GNUC__
#define unlikely(expr) __builtin_expect(!!(expr), 0)
#else
#define unlikely(expr) (expr)
#endif


#endif