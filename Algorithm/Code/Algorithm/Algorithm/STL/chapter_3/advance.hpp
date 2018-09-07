//
//  advance.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/8/2.
//  Copyright © 2018年 GTM. All rights reserved.
//

#ifndef advance_hpp
#define advance_hpp
#include <iterator>
#include <type_traits>
using namespace std;

// 5个作为标记用的类别（tag types）
struct minput_iterator_tag { };
struct moutput_iterator_tag { };
struct mforward_iterator_tag: public minput_iterator_tag { };
struct mbidirectional_iterator_tag: public mforward_iterator_tag { };
struct mrandom_access_iterator_tag: public mbidirectional_iterator_tag { };

template <class InputIterator, class Distance>
void __advance(InputIterator& i, Distance n, minput_iterator_tag) {
    // 单向，逐一前进
    while (n--) {
        ++i;
    }
}
template <class InputIterator, class Distance>
void __advance(InputIterator& i, Distance n, mforward_iterator_tag) {
    __advance(i, n, minput_iterator_tag());
}
template <class BidirectionalIterator, class Distance>
void __advance(BidirectionalIterator& i, Distance n, mbidirectional_iterator_tag) {
    // 双向，逐一前进
    if (n >= 0) {
        while (n--) {
            ++i;
        }
    } else {
        while (n++) {
            --i;
        }
    }
}
template <class RandomAccessIterator, class Distance>
void __advance(RandomAccessIterator& i, Distance n, mrandom_access_iterator_tag) {
    // 双向，跳跃前进
    i += n;
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n) {
    __advance(i, n, iterator_traits<InputIterator>::iterator_category());
}

#endif /* advance_hpp */
