#include "header_learning.h"

TypeConvertClass::operator int() const
{
	return m_intI;
}
TypeConvertClass::operator double()
{
	return static_cast<double>(m_intI) + 0.0001;
}

void type_convert_operator()
{
	//类型转换运算符与类型转换构造函数功能相反，它是一个类的成员函数，它将该类的对象转换为一个其他类型对象
	//类型转换运算符的格式：operator type() const
	//其中const是可选的，因为转换数据类型的时候可能会修改原值，type是要转换为的类型，可以是任何可被函数返回的类型，函数和数组不是可返回类型，但函数指针和数组指针是可返回类型
	//因为类型转换运算符都是隐式执行的，所以类型转换运算符不接受任何形参，同时，也不能指定返回类型，但是它可以返回一个type类型的值
	TypeConvertClass typeCvtCls_1(6672.7945);
	int typeCvtCls2int_1 = typeCvtCls_1;			//TypeConvertClass的类型转换运算符被隐式调用了，转换成了int
	std::cout << typeCvtCls2int_1 << std::endl;
	//其实也是可以显式地调用的
	int typeCvtCls2int_2 = typeCvtCls_1.operator int() + 8;
	std::cout << typeCvtCls2int_2 << std::endl;
	//我们也可以禁止隐式类型转换，只需在类声明中在类型转换运算符前面加上explicit，这样想做类型转换时就必须使用static_cast，当然，直接以成员函数的方法调用operator type()也是可以的
	TypeConvertClass typeCvtCls_2(6);
	double typeCvtCls2dbl = static_cast<double>(typeCvtCls_2);
	std::cout << typeCvtCls2dbl << std::endl;
}