//
//  1connfig10.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/25.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
#include <cstddef>
using namespace std;

class alloc {
};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
    deque() { cout << "deque" << endl; }
};

template <class T, class Sequence = deque<T> >
class stack {
    
public:
    stack() {
        cout << "stack" << endl;
    }
private:
    Sequence c;
};

//int main() {
//    stack<int> x;
//}







