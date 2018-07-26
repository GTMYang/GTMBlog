//
//  1config-temp-object.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/25.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


template <typename T>
class print {
public:
    void operator()(const T& elem)    // operator 重载
    {
        cout << elem << endl;
    }
};


//int main() {
//    int ia[6] = {0, 1,2,3,4,5};
//    vector<int> iv(ia, ia+6);
//    
//    // print<int>()  是一个临时对象，不是一个函数调用操作
//    for_each(iv.begin(), iv.end(), print<int>());
//}
