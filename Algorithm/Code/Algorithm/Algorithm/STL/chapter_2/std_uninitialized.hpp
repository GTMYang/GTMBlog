//
//  std_uninitialized.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/8/1.
//  Copyright © 2018年 GTM. All rights reserved.
//

#ifndef std_uninitialized_hpp
#define std_uninitialized_hpp

#include <cstddef>
#include <type_traits>
#include "stl_construct.hpp"
using namespace std;


template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialied_fill_n(ForwardIterator first, Size n, const T& x) {
    
}


template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialied_fill_n(ForwardIterator first, Size n, const T& x, T1*) {
    typedef typename ::is_pod<T1> is_POD;
    return __uninitialied_fill_n_aux(first, n, x, is_POD());
}


template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialied_fill_n_aux(ForwardIterator first, Size n, const T& x, true_type) {
    return fill_n(first, n, x);
}
template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialied_fill_n_aux(ForwardIterator first, Size n, const T& x, false_type) {
    ForwardIterator cur = first;
    for (; n > 0; --n, ++cur) {
        construct(&*cur, x);
    }
    return cur;
}





#endif /* std_uninitialized_hpp */
