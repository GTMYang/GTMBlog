//
//  1config-operator-overloading.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/7/26.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
using namespace std;


// C++中引用（&）的用法和应用实例 http://www.cnblogs.com/Mr-xu/archive/2012/08/07/2626973.html

class INT {
    friend ostream& operator<<(ostream& os, const INT& i);
    
public:
    INT(int i) : m_i(i) { };
    // prefix
    INT& operator++() {
        ++(this->m_i); // class 不同，本行应该有不同的操作
        return *this;
    }
    // postfix
    const INT operator++(int){
        INT temp = *this;
        ++(*this);
        return temp;
    }
    // prefix
    INT operator--(){
        --(this->m_i); // class 不同，本行应该有不同的操作
        return *this;
    }
    // postfix
    const INT operator--(int){
        INT temp = *this;
        --(*this);
        return temp;
    }
    // dereference
    int& operator*() const {
        return (int&)m_i;
    }
    
private:
    int m_i;
};

ostream& operator<<(ostream& os, const INT& i){
    os << '[' << i.m_i << ']' ;
    return os;
}

//int main() {
//    INT I(5);
//    
//    cout << I++ << endl;
//    cout << ++I << endl;
//    cout << I-- << endl;
//    cout << --I << endl;
//    cout << *I << endl;
//}





