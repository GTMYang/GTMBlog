swift 基础知识
===

## 访问控制
控制符  | 说明
:-|:-
** private **    |    当前entity内部可以访问
** file private ** |  当前source文件内可访问
** internal ** |      module内任何地方可以访问
** public ** |        任何地方都可访问（方法在module外 不能重写）
** open ** |          任何地方都可访问（方法在module外 可重写）

<p style="color: #AD5D0F;font-size: 12px;" >
* Classes with public access, or any more restrictive access level, can be subclassed only within the module where they’re defined.
* Class members with public access, or any more restrictive access level, can be overridden by subclasses only within the module where they’re defined.
* Open classes can be subclassed within the module where they’re defined, and within any module that imports the module where they’re defined.
* Open class members can be overridden by subclasses within the module where they’re defined, and within any module that imports the module where they’re defined.
</p>
[[参考：官方说明]](https://docs.swift.org/swift-book/LanguageGuide/AccessControl.html#//apple_ref/doc/uid/TP40014097-CH41-ID3)
