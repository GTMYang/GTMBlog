//
//  1connfig6.cpp
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
class myvector {
public:
    void swap(myvector<T, Alloc>&){ cout << "swap()" << endl; }
};

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER  // 只为说明，非本程序内容
template <class T, class Alloc>
inline void swap(myvector<T, Alloc>& x, myvector<T, Alloc>& y) {
    x.swap(y);
}
#endif // 只为说明，非本程序内容

// 以上节录自 stl_vector.h，灰色部分系源代码中的条件编译，非本测试程序内容
//
//int main() {
//    myvector<int> x, y;
//    swap(x, y);  // swap()
//}
