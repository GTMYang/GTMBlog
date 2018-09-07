//
//  level_2_alloc.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/27.
//  Copyright © 2018年 GTM. All rights reserved.
//

#ifndef level_2_alloc_hpp
#define level_2_alloc_hpp
#include <cstddef>
#include "level_1_alloc.hpp"
using namespace std;

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
    static void * allocate(size_t n) {
        obj * volatile * my_free_list;
        obj * result;
        
        // 大于128就调用第一级配置器
        if (n > (size_t) __MAX_BYTES) {
            return (malloc_alloc::allocate(n));
        }
        // 寻找合适的 free list
        my_free_list = free_list + FREELIST_INDEX(n);
        result = *my_free_list;
        if (result == 0) {
            void *r = refill(ROUND_UP(n)); // 重新填充 free list
            return r;
        }
        // 调整 free list
        *my_free_list = result -> free_list_link;
        
        return (result);
    }
    static void deallocate(void * p, size_t n) {
        obj *q = (obj *)p;
        obj * volatile * my_free_list;
        
        if (n > (size_t)__MAX_BYTES) {
            malloc_alloc::deallocate(p, n);
            return;
        }
        
        my_free_list = free_list + FREELIST_INDEX(n);
        q -> free_list_link = *my_free_list;  // 回收区块
        *my_free_list = q;
    }
    
    static void * reallocate(void * p, size_t old_sz, size_t new_sz) { /* 后面 */ }
    
    
};

// 以下是 static data member 的定义与初始设定
template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::start_free = 0;

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj * volatile __default_alloc_template<threads, inst>::free_list[__NFREELISTS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


template <bool threads, int inst>
void * __default_alloc_template<threads, inst>::refill(size_t n) {
    int nobjs = 20;
    // 注意参数 nobjs 是 pass by reference
    char * chunk = chunk_alloc(n, nobjs); // 下节详述
    obj * volatile * my_free_list;
    obj * result;
    obj * current_obj, * next_obj;
    int i;
    
    // 如果只获得1个区块， 这个区块就分配给调用者用， free list 无新节点
    if (1 == nobjs) {
        return chunk;
    }
    // 否则准备调整 free list
    my_free_list = free_list + FREELIST_INDEX(n);
    
    // 以下在chunk 空间内建立 free list
    result = (obj *)chunk;
    // 以下引导 free list 指向新配置的空间
    *my_free_list = next_obj = (obj *)(chunk + n);
    // 以下将 free list 各节点串联起来
    for (i = 0; ; i++) { // 从1开始，第0个将返回给客端
        current_obj = next_obj;
        next_obj = (obj *)((char *)next_obj + n);
        
        if (nobjs - 1 == i) { // 最后一个
            current_obj -> free_list_link = 0;
            break;
        } else {
            current_obj -> free_list_link = next_obj;
        }
    }
    
}

template <bool threads, int inst>
char *
__default_alloc_template<threads, inst>::chunk_alloc(size_t size, int &nobjs) {
    char *result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;  // 内存池剩余空间
    
    if (bytes_left >= total_bytes) {
        // 内存池剩余空间足够
        result = start_free;
        start_free += total_bytes;
        
        return(result);
    } else if (bytes_left >= size) {
        // 内存池剩余空间只能满足部分需求
        nobjs = bytes_left/size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        
        return(result);
    } else {
        // 内存池无法提供空间
        size_t bytes_go_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        // 以下试着让内存池中的残余零头还有利用价值
        if (bytes_left > 0) {
            // 内存池中的零头先配给适当的 free list
            // 首先寻找适当的 free list
            obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
            // 调整 free list，将内存池中的残余空间编入
            ((obj *)start_free) -> free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }
        
        // 配置 heap 空间，用来补充内存池
        start_free = (char *)malloc(bytes_go_get);
        if (0 == start_free) {
            // heap 空间不足，malloc()失败
            int i;
            obj * volatile * my_free_list, *p;
            // 试着检索我们手上拥有的东西。这不会造成伤害。我们不打算尝试配置
            // 较小的区块，因为那在多进程机器上容易导致灾难
            // 以下搜寻适当的 free list
            // 所谓适当是指 “尚有未用区块，且区块够大” 之 free list
            for (i = size; i <= __MAX_BYTES; i += __ALIGN) {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (0 != p) {
                    // 调整 free list 以释放出未用区块
                    *my_free_list = p -> free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;
                    // 递归调用自己，为了修正 nobjs
                    return(chunk_alloc(size, nobjs));
                    // 注意，任何残余零头将会被编入适当的 free-list 备用
                }
            }
            end_free = 0;  // 如果出现意外（到处都没有内存可用了）
            
            // 调用第一级配置器，看看 out-of-memory 机制能否尽点力
            start_free = (char *)malloc_alloc::allocate(bytes_go_get);
            // 这会导致抛出异常，或内存不足的情况获得改善
        }
        heap_size += bytes_go_get;
        end_free = start_free + bytes_go_get;
        // 递归调用自己， 为了修正 nobjs
        return (chunk_alloc(size, nobjs));
    }
}


#endif /* level_2_alloc_hpp */









