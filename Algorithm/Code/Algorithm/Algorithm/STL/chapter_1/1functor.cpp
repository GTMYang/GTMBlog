//
//  1functor.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/26.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
using namespace std;

// 由于将operator()重载了， 因此plus成了一个仿函数
template <class T>
struct myplus {
    T operator()(const T& x, const T& y) const { return  x + y; }
};

// 由于将operator()重载了， 因此minus成了一个仿函数
template <class T>
struct myminus {
    T operator()(const T& x, const T& y) const { return  x - y; }
};

//int main() {
//    // 产生仿函数对象
//    myplus<int> plusobj;
//    myminus<int> myminusobj;
//    
//    // 以下使用仿函数就像使用函数一般
//    cout << plusobj(3, 5) << endl;
//    cout << myminusobj(3, 5) << endl;
//    
//    // 直接产生临时变量
//    cout << myplus<int>()(43, 45) << endl;
//    cout << myminus<int>()(43, 45) << endl << endl;
//    
//    
//}
