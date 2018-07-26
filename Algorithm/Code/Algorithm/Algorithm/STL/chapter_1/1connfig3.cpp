//
//  1connfig3.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/23.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
using namespace std;

template <typename T>
class testClass {
public:
    static int _data;
};

template<> int testClass<int>::_data = 1;
template<> int testClass<char>::_data = 2;

void main1() {
    cout << testClass<int>::_data << endl;
    cout << testClass<char>::_data << endl;
    
    testClass<int> obji1, obji2;
    testClass<char> objc1, objc2;
    
    cout << obji1._data << endl;
    cout << obji2._data << endl;
    cout << objc1._data << endl;
    cout << objc2._data << endl;
    
    obji1._data = 3;
    objc2._data = 4;
    
    cout << obji1._data << endl;
    cout << obji2._data << endl;
    cout << objc1._data << endl;
    cout << objc2._data << endl;
    
}
