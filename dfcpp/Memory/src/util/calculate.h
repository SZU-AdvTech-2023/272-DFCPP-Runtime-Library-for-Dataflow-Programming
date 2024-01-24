/* 
    @date   : 2024/1/4
    @author : Tlx
    @brief  : 通用的计算函数实现
*/
#ifndef DFCpp_CALCULATE_H
#define DFCpp_CALCULATE_H

#include <cstddef>
namespace D_Memory{

/* 计算size 对应的阶数*/
constexpr inline unsigned int ilog2 (const size_t sz)
  {
    return ((unsigned int) (sizeof(size_t) * 8UL) - (unsigned int) __builtin_clzl((sz << 1) - 1UL) - 1);
  }

}

#endif