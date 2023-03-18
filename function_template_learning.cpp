#include "header_learning.h"

//定义一个函数模板，需要在函数头的上方写上 template<typename 形参1, typename形参2, ...> 其中，typename关键字也可以换成class关键字，效果是一样的，此处的形参将接收实际的类型名作为实参
template<typename T>
T addTmplFunc(T numA, T numB)
{
	return numA + numB;
}

//函数模板不一定是类型模板参数，还有非类型模板参数，它不使用typename或class，而是使用具体的类型名，就是说函数模板的形参还可能是某个类型的值，接收具体的实参，但这个值必须是常量而非变量
//在编译期间，如果编译到了具体调用模板函数的代码，才会实例化为特定的函数，将非类型模板参数替换为具体的值，如果没有发现具体的函数调用，编译器并不会生成代码
template<int a, int b>
int intAddTmpFunc()
{
	return a + b;
}
//另一个示例，模板接收两个形参，一个是类型模板参数，一个是非类型模板参数
template<typename TY, int y>			//注意，非类型模板参数不允许使用浮点值和类对象，所以像 double y 这样的形参会报错，另外，字符串、内部链接对象(仅当前编译单元有效的对象)和非const的全局指针作为模板参数也是不被允许的
TY TYAddIntReturnTY(TY x)
{
	return x + y;
}
//一个编译器自动推断非类型模板参数的示例
template<unsigned N1>
int returnLenOfCStr(const char (&cstr)[N1])
{
	return N1;
}
//上面的函数模板定义都可以放进头文件中，多个.cpp文件同时include并不会冲突

void function_template()
{
	//调用使用模板的函数的时候，需要在<>中指明真正的类型实参，但有时候也不需要，因为有时编译器能够根据一些信息自动推断类型
	//编译器在编译阶段可以确定使用模板的函数实际接收的类型
	int sumInt = addTmplFunc(10, 202);			//编译器自动推断出了此处的类型是int型，所以就实例化了一个int类型的addTmplFunc()
	std::cout << sumInt << std::endl;
	//有时，编译器会无法推断出正确的类型，比如下面的情况
	//double sumDbl = addTmplFunc(100, 3.14);			//报错，因为根据函数模板的定义，两个参数的类型应该是相同的，但此处的调用提供了一个int参数和一个double参数，于是无法正确推断实际的类型

	//非类型模板参数的函数调用，需要用户自己传值，但有时候编译器也会自动推断
	int sumOfIntAdd = intAddTmpFunc<33, 766>();			//不使用传统的传递形参的方法调用函数，而是在<>内显式指定非类型模板参数
	std::cout << sumOfIntAdd << std::endl;
	//另一个示例的结果
	double sumOfTY = TYAddIntReturnTY<double, 22>(3.67);			//调用模板函数时，圆括号内的实参究竟是什么类型，并不是根据参数本身去推断的，而是根据尖括号内的类型实参确定的
																	//	如果圆括号内传入的参数与类型实参的类型不符，参数会进行类型转换
	std::cout << sumOfTY << std::endl;
	//编译器自动推断非类型模板参数的函数示例的结果
	std::cout << returnLenOfCStr("Nayuta") << std::endl;			//结果是7，nayuta加上一个末尾的空字符，结果是正确的，当我们调用这个模板函数时，编译器自动为我们根据传入的字符串的长度实例化了一个函数
																	//	这个函数将函数模板中的N1替换成了一个无符号数字，这个数字等于字符串长度
	//当然我们也可以手动传入这个函数的非类型模板参数
	std::cout << returnLenOfCStr<6>("China") << std::endl;			//但是这里函数圆括号中的实参必须与非类型模板参数的值匹配，如果非类型模板参数传入了一个10，但是圆括号中的字符串长度并不是10，就会报错
	/*
	模板函数也可以是内联的，inline关键字放在模板参数列表之后，函数头之前，如下所示：
	template< ... >
	inline returnType functionName( ... ){}
	*/
}