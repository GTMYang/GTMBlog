//
//  icnfig-null-template-arguments.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/25.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
#include <cstddef>
using namespace std;


class alloc{ };

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
    
public:
    deque() { cout << "deque" << endl; }
};



//template <class T, class Sequence>
//class stack;
//
//template <class T, class Sequence>
//bool operator==(const stack<T, Sequence>& x,
//                const stack<T, Sequence>& y);
//
//template <class T, class Sequence>
//bool operator<(const stack<T, Sequence>& x,
//               const stack<T, Sequence>& y);



template <class T, class Sequence = deque<T>>
class stack {
    // 写成这样是可以的
    friend bool operator== <T> (const stack<T>&, const stack<T>&);
    friend bool operator< <T> (const stack<T>&, const stack<T>&);
//    // 写成这样也是可以的
//    friend bool operator== <T> (const stack&, const stack&);
//    friend bool operator< <T> (const stack&, const stack&);
//    // 写成这样也是可以的
//    friend bool operator== <> (const stack&, const stack&);
//    friend bool operator< <> (const stack&, const stack&);
//    // 写成这样也是可以的
//    friend bool operator== (const stack&, const stack&);
//    friend bool operator< (const stack&, const stack&);
    
public:
    stack() { cout << "stack" << endl; }
private:
    Sequence c;
};

template <class T, class Sequence>
bool operator==(const stack<T, Sequence>& x,
                const stack<T, Sequence>& y) {
    cout << "operator==" << "\t";
    return true;
}


template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& x,
                const stack<T, Sequence>& y) {
    cout << "operator<" << "\t";
    return false;
}
//
//int main() {
//    stack<int> x;
//    stack<int> y;
////    stack<char> y1;
//    
//    cout << (x == y) << endl;
////    cout << (x < y) << endl;
//    
//    
////    cout << (x == y1) << endl;
////    cout << (x < y1) << endl;
//}









