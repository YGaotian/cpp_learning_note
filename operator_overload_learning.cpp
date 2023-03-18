#include "header_learning.h"

Myclass& Myclass::operator=(const Myclass& myc)
{
	//赋值运算符重载，返回类型为Myclass&，返回的是*this，就是返回了自己，这样就可以连续赋值了，比如myc1=myc2=myc3，如果返回类型是void，也可以执行，但是就无法连续赋值了
	//如果不返回引用，会生成临时对象，临时对象的产生会调用拷贝构造函数和析构函数，效率低
	//形参使用引用也是为了防止生成临时对象，加上const可以防止在复制的时候错误地更改原值，并且const限定的形参可以接收非const和const实参，不然无法接收const实参
	numA = myc.numA;
	numB = myc.numB;
	numC = myc.numC;
	numD = myc.numD;
	std::cout << "赋值运算符重载调用了 " << std::endl;
	return *this;
}

void operator_overload()
{
	Myclass mc9(20, 30, 40, 60);
	Myclass mc10(176);
	Myclass mc11;
	mc11 = mc10 = mc9;
	mc11.showAllMember();
	mc10.showAllMember();
}