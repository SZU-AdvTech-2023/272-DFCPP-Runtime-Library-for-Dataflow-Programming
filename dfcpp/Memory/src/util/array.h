#ifndef DFCPP_ARRAY_H
#define DFCPP_ARRAY_H

#include <cassert>
namespace D_Memory{

  template <unsigned long N, typename T>
  class Array {
  public:

    inline T& operator()(int index) {
      assert (index < N);
      return _item[index];
    }

    inline const T& operator()(int index) const {
      assert (index < N);
      return _item[index];
    }

  private:

    T _item[N];

  };

}

#endif