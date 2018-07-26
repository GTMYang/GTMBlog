//
//  1connfig5.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/25.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
using namespace std;

// 一般化设计
template <class I, class O>
struct testClass
{
    testClass() { cout << "I, O" << endl; }
};

// 特殊化设计
template <class T>
struct testClass<T*, T*>
{
    testClass() { cout << "T*, T*" << endl; }
};

// 特殊化设计
template <class T>
struct testClass<const T*, T*>
{
    testClass() { cout << "T*, T*" << endl; }
};

//int main() {
//    testClass<int, char> obj1;
//    testClass<int*, int*> obj2;
//    testClass<const int*, int*> obj3;
//}




