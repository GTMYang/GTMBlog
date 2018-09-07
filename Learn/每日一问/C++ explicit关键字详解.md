C++ explicit关键字详解
===

[C++ explicit关键字详解](https://www.cnblogs.com/ymy124/p/3632634.html)

* explicit关键字只能用于修饰只有一个参数的类构造函数
* explicit关键字取消了隐式转换

### 隐式转换
```c++

class CxString  // 没有使用explicit关键字的类声明, 即默认为隐式声明  
{  
public:  
    char *_pstr;  
    int _size;  
    CxString(int size)  
    {  
        _size = size;                // string的预设大小  
        _pstr = malloc(size + 1);    // 分配string的内存  
        memset(_pstr, 0, size + 1);  
    }  
    CxString(const char *p)  
    {  
        int size = strlen(p);  
        _pstr = malloc(size + 1);    // 分配string的内存  
        strcpy(_pstr, p);            // 复制字符串  
        _size = strlen(_pstr);  
    }  
    // 析构函数这里不讨论, 省略...  
};  

    // 下面是调用:  

    CxString string1(24);     // 这样是OK的, 为CxString预分配24字节的大小的内存  
    CxString string2 = 10;    // 这样是OK的, 编译齐做了隐式转换 CxString string2(10)
```
