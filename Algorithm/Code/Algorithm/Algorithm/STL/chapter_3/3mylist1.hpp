//
//  3mylist1.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/8/1.
//  Copyright © 2018年 GTM. All rights reserved.
//

#include <iostream>
using namespace std;

template <typename T>
class ListItem {
public:
    T value() const { return _value; }
    ListItem* next() const { return _next; }
    
private:
    T _value;
    ListItem *_next;  // 单向链表
};

template <typename T>
class List {
    
public:
    void insert_front(T value);
    void insert_end(T value);
    void display(std::ostream &os = std::cout) const;
    
private:
    ListItem<T>* _end;
    ListItem<T>* _front;
    
    long _size;
};

//template <typename T>
//void List<T>::insert_front(T value) {
//    ListItem<T> tmp(value);
//
//    tmp.next() = this->_front;
//    this->_front = tmp;
//}
//template <typename T>
//void List<T>::insert_end(T value) {
//    ListItem<T> tmp(value);
//    tmp.next() = this->_end;
//    this->_end = tmp;
//}
//template <typename T>
//void List<T>::display(std::ostream &os = std::cout) const {
//    
//}
