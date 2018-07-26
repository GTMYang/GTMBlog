//
//  stl_construct.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/26.
//  Copyright © 2018年 GTM. All rights reserved.
//

#ifndef stl_construct_hpp
#define stl_construct_hpp

#include <new>
#include <type_traits>
using namespace std;

template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
    // placement new (格式：new(T1* p) T1(value) ) 在已分配好的内存空间上构建对象
    new(p) T1(value);
}


template <class T>
inline void destroy(T* pointer) {
    pointer->~T();
}


template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    
}


template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
    //typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    //👇
    // is_trivial<T>
    __destroy_aux(first, last, is_trivial<T>());
}

template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, false_type) {
    for (; first < last; ++first) {
        destroy(first);
    }
}
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, true_type) { }

inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}


#endif /* stl_construct_hpp */
