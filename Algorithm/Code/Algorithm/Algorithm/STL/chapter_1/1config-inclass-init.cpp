//
//  1config-inclass-init.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/26.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
using namespace std;


template <typename T>
class testClass {
public:
    static const int _datai = 5;
    static const int _datal = 3L;
    static const int _dataca = 'a';
    static const int _datacb = 'b';
    static const int _datacc = 'c';
    static const int _datacz = 'z';
    static const int _dataca1 = 'A';
    static const int _datacb1 = 'B';
    static const int _datacc1 = 'C';
    static const int _datacz1 = 'Z';
};


//int main() {
//    cout << testClass<int>::_datai << endl;
//    cout << testClass<int>::_datal << endl;
//    
//    cout << testClass<int>::_dataca << endl;
//    cout << testClass<int>::_datacb << endl;
//    cout << testClass<int>::_datacc << endl;
//    cout << testClass<int>::_datacz << endl;
//    cout << testClass<int>::_dataca1 << endl;
//    cout << testClass<int>::_datacb1 << endl;
//    cout << testClass<int>::_datacc1 << endl;
//    cout << testClass<int>::_datacz1 << endl;
//    // abcde fghij klmno pqrst uvwxy z
//}
