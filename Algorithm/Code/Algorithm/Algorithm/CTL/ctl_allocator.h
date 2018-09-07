//
//  ctl_allocator.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/8/11.
//  Copyright © 2018年 GTM. All rights reserved.
//

#ifndef ctl_allocator_hpp
#define ctl_allocator_hpp
#include <new>          // for placement new
#include <cstddef>      // for ptrdiff_t, size_t
#include <cstdlib>      // for exit()
#include <climits>      // for UINT_MAX
#include <iostream>     // for cerr

using namespace std;
#include "ctl_alloc.hpp"


namespace ctl {
    
    template <class T>
    inline T* _allocate(ptrdiff_t size, T*) {
        // set_new_handler 设置new操作失败时的处理函数（此函数试图获得更多可用空间）
        // 在尚未用set_new_handler设置处理函数，或者设置的处理函数为空时，将调用默认的处理函数
        set_new_handler(0);
        
        T *temp = (T*)(::operator new((size_t) (size * sizeof(T))));
        if (temp == 0) {
            cerr << "out of memory" << endl;
            exit(1);
        }
        return temp;
    }
    
    template <class T>
    inline void _deallocate(T* buffer) {
        ::operator delete(buffer);
    }
    
    template <class T1, class T2>
    inline void _construct(T1* p, const T2& value) {
        // new(T1* p) T1(value) 在已分配好的内存空间上构建对象
        new(p) T1(value);    // placement new. invoke ctor of T1
    }
    
    template <class T>
    inline void _destory(T* ptr) {
        ptr->~T();
    }
    
    template <class T>
    class allocator {
    public:
        typedef T value_type;   // typedef定义类型的别名
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;  // ptrdiff_t类型变量通常用来保存两个指针减法操作的结果。
        
        // rebind allocator of type U
        template <class U>
        struct rebind {
            typedef allocator<U> other;
        };
        
        // hint used for locality. ref.[Austern],p189
        pointer allocate(size_type n, const void* hint = 0) {
            return  _allocate((difference_type)n, (pointer)0);
        }
        
        void deallocate(pointer p, size_type n) {
            _deallocate(p);
        }
        
        void construct(pointer p, const T& value) {
            _construct(p, value);
        }
        
        void destroy(pointer p) {
            _destory(p);
        }
        
        pointer address(reference x) {
            return (pointer)&x;
        }
        
        const_pointer const_address(const_reference x) {
            return (const_pointer)&x;
        }
        
        size_type max_size() const { // const成员函数 说明该函数不需要修改对象内容
            return size_type(UINT_MAX/sizeof(T));
        }
    };
    
}

#endif /* ctl_allocator_hpp */
