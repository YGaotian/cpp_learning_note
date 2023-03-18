#include "header_learning.h"

TypeConvertClass::TypeConvertClass(int i) : m_intI(i)
{
	std::cout << "typeConvert constructor called" << std::endl;
}

void type_convert_constructor()
{
	//还有一种有参构造函数，它接收一个参数，这个参数不是本类的const引用，这种构造函数称为类型转换构造函数
	//下面两种实例化的方式看上去都在调用类型转换构造函数，但实际上，只有第一行代码才直接地调用了类型转换构造函数，当我们在类声明中为单参数的构造函数前面加上explicit后，第二行会报错
	TypeConvertClass tcc_1(12);			//这里直接显式地调用了类型转换构造函数（或者说，其实就是一个单参数的构造函数）
	//TypeConvertClass tcc_2 = 11;			//报错了，因为这里实际上是执行了隐式类型转换，想要隐式地执行类型转换构造函数将11转换成TypeConvertClass对象，并赋值给了tcc_2，然而类声明中通过explicit禁止了隐式转换
}