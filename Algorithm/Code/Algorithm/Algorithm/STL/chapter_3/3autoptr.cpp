//
//  3autoptr.cpp
//  Algorithm
//
//  Created by 骆扬 on 2018/8/1.
//  Copyright © 2018年 GTM. All rights reserved.
//



template <class T>
class auto_ptr {
    
public:
    explicit auto_ptr(T *p = 0) : pointee(p) {}  // explicit关键字取消隐式转换，如：auto_ptr<T> ap = T()
    template <class U>
    auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()) {}
    ~auto_ptr() { delete pointee; }
    
    template <class U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
        if (this != rhs) {
            reset(rhs.release());
        }
        return *this;
    }
    T& operator*() const { return *pointee; }
    T* operator->() const { return pointee; }
    T* get() const { return pointee; }
    // ...
private:
    T *pointee;
    
};
