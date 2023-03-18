#pragma once
#include <iostream>

template<typename T=double, int size=10>   //类模板可以有默认参数，默认参数只需要在类模板声明的开头写上，在后面的类成员函数定义的开头不用写，和普通类的规则类似
class MyList
{
public:
	typedef T* MLIterator;  //使用 using MLIterator = T*; 也是可以的
public:
	MyList();
	MyList& operator=(const MyList& mlst);			//类模板声明的内部并不需要使用<>来传入类型形参，不过想自己写上也可以，MyList<T>& operator=(const MyList<T>& mlst)并不会报错
	MLIterator lstBegin();
	MLIterator lstEnd();
};

//将类成员函数的函数体写在类声明之外，写在外面的时候需要在开头写上 template<typename Type> ，并且作用域运算符的前面，类名后也要写上 <Type>，实际上整个 MyList<T> 表示的才是类型名
template<typename T, int size>
MyList<T, size>::MyList()
{
	std::cout << "A list of " << typeid(T).name() << " " << size << " type is created" << std::endl;
}

//因为整个 MyList<T> 才是类型名，所以有返回值的成员函数，它的返回值类型也要写完整
template<typename T, int size>
MyList<T, size>& MyList<T, size>::operator=(const MyList<T, size>& mlst)			//函数参数列表中，形参的类型可以不写<T>，并不会报错
{
	return *this;
}




template<typename T1>
class MyTemplateClassA
{
public:
    MyTemplateClassA();

public:
    template<typename FT>
    void tmplFunc(FT funcTempArg);

public:
    T1 m_tVar;
};

template<typename T1>
MyTemplateClassA<T1>::MyTemplateClassA():m_tVar(20)
{

}

template<typename T1>   //类模板
template<typename FT>   //函数模板
void MyTemplateClassA<T1>::tmplFunc(FT funcTempArg)
{
    std::cout << funcTempArg + m_tVar << std::endl;
}