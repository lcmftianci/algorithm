# C++ Foundation

C++历史
```
C++是C语言的继承，它既可以进行C语言的过程化程序设计，又可以进行以抽象数据类型为特点的基于对象的程序设计，还可以进行以继承和多态为特点的面向对象的程序设计。C++擅长面向对象程序设计的同时，还可以进行基于过程的程序设计，因而C++就适应的问题规模而论，大小由之;
C++不仅拥有计算机高效运行的实用性特征，同时还致力于提高大规模程序的编程质量与程序设计语言的问题描述能力。
1979年，Bjame Sgoustrup到了Bell实验室，开始从事将C改良为带类的C（C with classes）的工作。1983年该语言被正式命名为C++。自从C++被发明以来，它经历了3次主要的修订，每一次修订都为C++增加了新的特征并作了一些修改。第一次修订是在1985年，第二次修订是在1990年，而第三次修订发生在c++的标准化过程中。在20世纪90年代早期，人们开始为C++建立一个标准，并成立了一个ANSI和ISO（Intemational Standards Organization）国际标准化组织的联合标准化委员会。该委员会在1994年1月25曰提出了第一个标准化草案。在这个草案中，委员会在保持Stroustrup最初定义的所有特征的同时，还增加了一些新的特征。
在完成C++标准化的第一个草案后不久，发生了一件事情使得C++标准被极大地扩展了：Alexander stepanov创建了标准模板库（Standard Template Library，STL）。STL不仅功能强大，同时非常优雅，然而，它也是非常庞大的。在通过了第一个草案之后，委员会投票并通过了将STL包含到C++标准中的提议。STL对C++的扩展超出了C++的最初定义范围。虽然在标准中增加STL是个很重要的决定，但也因此延缓了C++标准化的进程。
委员会于1997年11月14日通过了该标准的最终草案，1998年，C++的ANSI/IS0标准被投入使用。

C++ 98 标准 C++标准第一版，1998年发布。正式名称为ISO/IEC 14882:1998 [18]
C++ 03 标准 C++标准第二版，2003年发布。正式名称为ISO/IEC 14882:2003 [19]
C++ 11 标准 C++标准第三版，2011年8月12日发布。正式名称为ISO/IEC 14882:2011 [20]
C++11对容器类的方法做了三项主要修改。
首先，新增的右值引用使得能够给容器提供移动语义。其次，由于新增了模板类initilizer_list，因此新增了将initilizer_list作为参数的构造函数和赋值运算符。第三，新增的可变参数模板（variadic template）和函数参数包（parameter pack）使得可以提供就地创建（emplacement）方法。 [21]
C++ 14 标准
C++标准第四版，2014年8月18日发布。正式名称为ISO/IEC 14882:2014 [22]
C++14是C++11的增量更新，主要是支持普通函数的返回类型推演，泛型 lambda，扩展的 lambda 捕获，对 constexpr 函数限制的修订，constexpr变量模板化等
```

1.1. 关键字：const,static,this,inline,volatile


1.2. 数据结构对齐方式
#pragma pack(n),以前用到OpenCV的项目上用到了
#pragma pack(1),图片数据拷贝时崩溃
```
#pragma pack(push)  // 保存对齐状态
#pragma pack(4)     // 设定为 4 字节对齐

struct test
{
    char m1;
    double m4;
    int m3;
};

#pragma pack(pop)   // 恢复对齐状态
```

1.3. extern "C"使用
被 extern 限定的函数或变量是 extern 类型的
被 extern "C" 修饰的变量和函数是按照 C 语言方式编译和链接的
extern "C" 的作用是让 C++ 编译器将 extern "C" 声明的代码当作 C 语言代码处理，可以避免 C++ 因符号修饰导致代码不能和C语言库中的符号进行链接的问题。
```
#ifdef __cplusplus
extern "C" {
#endif
void *memset(void *, int, size_t);
#ifdef __cplusplus
}
#endif
```

我们在使用ffmepg这些纯C的类库时需要引入用extern "C"导入
