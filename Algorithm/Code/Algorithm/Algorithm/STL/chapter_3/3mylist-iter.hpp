//
//  3mylist-iter.hpp
//  Algorithm
//
//  Created by 骆扬 on 2018/8/1.
//  Copyright © 2018年 GTM. All rights reserved.
//

#ifndef _mylist_iter_hpp
#define _mylist_iter_hpp
#include "3mylist1.hpp"

template <class Item>
struct ListIter {
    Item* ptr;
    
    ListIter(Item* p = 0) : ptr(p) { } // default ctor
    

    Item& operator*() const { return *ptr; }
    Item* operator->() const { return ptr; }
    
    // pre-increment operator
    ListIter& operator++() {
        ptr = ptr->next();
        return *this;
    }
    // post-increment operator
    ListIter operator++(int) {
        ListIter tmp = *this;
        ++*this;
        return tmp;
    }
    
    bool operator==(const ListIter& i) const {
        return ptr == i.ptr;
    }
    bool operator!=(const ListIter& i) const {
        return ptr != i.ptr;
    }
    
};

#endif /* _mylist_iter_hpp */
