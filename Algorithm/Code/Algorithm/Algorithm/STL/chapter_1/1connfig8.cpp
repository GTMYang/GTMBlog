//
//  1connfig8.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/25.
//  Copyright © 2018年 GTM. All rights reserved.
//
// 参考：https://blog.csdn.net/bolike/article/details/19129591

#include <iostream>
using namespace std;

class alloc {
};

template <class T, class Alloc = alloc>
class vector1 {
public:
    typedef T value_type;
    typedef value_type* iterator;
    
    template <class I>
    void insert(iterator position, I first, I last) {
        cout << "insert()" << endl;
    }
};


//int main() {
//    int ia[5] = {0, 1, 2, 3, 4};
//    
//    vector1<int> x;
//    vector1<int>::iterator ite;
//    x.insert(ite, ia, ia+5);
//    
//}


