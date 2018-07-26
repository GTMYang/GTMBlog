//
//  jjallocator.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/26.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include "jjallocator.hpp"
#include <vector>
#include <iostream>
//using namespace std;

int main() {
    int ia[5] = {0,1,2,3,4};
    unsigned int i;
    
    vector<int, JJ::allocator<int>> iv(ia, ia+5);
    for (i=0; i<iv.size(); i++) {
        cout << iv[i] << ' ';
    }
    cout << endl;
}

