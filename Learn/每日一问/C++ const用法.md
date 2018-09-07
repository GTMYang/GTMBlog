C++ const用法
===

[C++ const用法](https://www.cnblogs.com/Forever-Kenlen-Ja/p/3776991.html)

### 左定值
const位于*号的左边，p变量的值不可修改。
```c++
// 例如：
const int *p = 8; // 指针指向的内容8不可改变
```
### 右定向
const位于*号的右边，对于const指针p其指向的内存地址不能够被改变。
```c++
// 例如：
  int a = 8;

  int* const p = &a;

  *p = 9; //it’s right

  int  b = 7;

  p = &b; //it’s wrong

```
