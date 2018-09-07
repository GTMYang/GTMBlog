//
//  ctl_alloc.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/8/11.
//  Copyright © 2018年 GTM. All rights reserved.
//

#ifndef ctl_alloc_hpp
#define ctl_alloc_hpp

#include <cstdlib>

namespace ctl {
    
    #if 0
    #   include <new>
    #   define __THROW_BAD_ALLOC throw bad_alloc
    #elif !defined(__THROW_BAD_ALLOC)
    #   include <iostream>
    #   define __THROW_BAD_ALLOC cerr << "out of memory" << endl; exit(1)
    #endif
    
    // 一级配置器
    template <int inst>
    class __alloc_alloc_template {
        
    private:
        // 以下函数将用来处理内存不足情况
        static void *oom_malloc(size_t);
        static void *oom_realloc(void*, size_t);
        static void (* __malloc_alloc_oom_handler)();
        
    public:
        static void * allocate(size_t n) {
            void *result = malloc(n);  // 第一级配置器直接用 malloc()
            // 以下无法满足需求时， 改用 oom_malloc()
            if (0 == result) { result = oom_malloc(n); }
            
            return result;
        }
        
        static void deallocate(void * p, size_t /* n */) {
            free(p);    // 第一级配置器直接用 free()
        }
        
        static void * reallocate(void * p, size_t /* old_sz */, size_t new_sz) {
            void * result = realloc(p, new_sz);   // 第一级配置器直接用 realloc()
            if (0 == result) { result = oom_realloc(p, new_sz); }
            
            return result;
        }
        
        // 以下仿真 C++ 的 set_new_handler() 换句话说，你可以通过它
        // 指定你自己的 out-of-memory handler
        
        static void (* set_malloc_handler(void (*f)()))() {
            void (* old)() = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = f;
            
            return(old);
        }
    };
    // malloc_alloc out-of-memory handling
    // 初值为0. 有待客端设定
    
    template <int inst>
    void (* __alloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0; // 默认指向空指针，交由客端实现
    
    template <int inst>
    void * __alloc_alloc_template<inst>::oom_malloc(size_t n) {
        void (* my_malloc_handler)();
        void *result;
        
        for (; ; ) {   // 不断尝试释放, 配置，再释放，再配置
            my_malloc_handler = __malloc_alloc_oom_handler;
            if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
            (*my_malloc_handler)();
            result = malloc(n);
            if (result) {
                return result;
            }
        }
    }
    
    template <int inst>
    void * __alloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
        void (* my_malloc_handler)();
        void *result;
        
        for (; ; ) {   // 不断尝试释放, 配置，再释放，再配置
            my_malloc_handler = __malloc_alloc_oom_handler;
            if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
            (*my_malloc_handler)();
            result = realloc(p, n);
            if (result) {
                return result;
            }
        }
    }
    // 注意，以下直接将参数 inst 指定为 0
    typedef __alloc_alloc_template<0> malloc_alloc;
    
    
    // 二级配置器
    enum {__ALIGN = 8};
    enum {__MAX_BYTES = 128};
    enum {__NFREELISTS = __MAX_BYTES/__ALIGN};
    
    template <bool threads, int inst>
    class __default_alloc_template {
        
    private:
        // ROUND_UP()  将 bytes 上调至 8 的倍数
        static size_t ROUND_UP(size_t bytes) {
            return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
        }
    private:
        // free-lists 的节点构造
        union obj {
            union obj * free_list_link;
            char client_data[1];
        };
    private:
        // 16 个 free-lists
        static obj * volatile free_list[__NFREELISTS];
        // 以下函数根据区块大小，决定使用第 n 号 free-list。n 从 0 起算
        static size_t FREELIST_INDEX(size_t bytes) {
            return (((bytes) + __ALIGN-1)/__ALIGN - 1);
        }
        
        // 返回一个大小为 n 的对象， 并可能加入大小为 n 的其它区块到 free list
        static void *refill(size_t n);
        // 配置一大块空间， 可容纳 nobjs 个大小为 "size" 的区块
        // 如果配置 nobjs 有所不便， nobjs 可能会降低
        static char *chunk_alloc(size_t size, int &nobjs);
        
        // chunk allocation state
        static char *start_free;    // 内存池起始位置
        static char *end_free;      // 内存池结束位置
        static size_t heap_size;
        
        
    public:
        static void * allocate(size_t n);
        static void deallocate(void * p, size_t n);
        static void * reallocate(void * p, size_t old_sz, size_t new_sz);
        
    };
}

#endif /* ctl_alloc_hpp */
