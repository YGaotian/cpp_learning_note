#include "header_learning.h"

DataA::DataA(int val) : m_dataVal(val) {}
DataA::DataA(const DataA& data) : m_dataVal(data.m_dataVal) {}
DataA::~DataA() = default;

DataAgrp::DataAgrp(DataA dt) : m_dataA(&dt) {}
DataAgrp::DataAgrp(const DataAgrp & datagrp) : m_dataA(datagrp.m_dataA)
{
	std::cout << "copy constructor" << std::endl;
}
DataAgrp::DataAgrp(DataAgrp && datagrp) noexcept : m_dataA(datagrp.m_dataA)			//移动构造函数在声明和定义时都要加上noexcept，这样可以防止程序出现问题时抛出异常
{																					//一旦运行的过程中有问题，程序会被std::terminate终止，这么做的目的是，移动构造函数在移动数据的时候，如果抛出了异常
	datagrp.m_dataA = nullptr;			//disconnection								//原始对象的数据可能会因为抛出的异常而丢失，所以有问题时立即终止程序有效地阻止了异常的传播和扩散，并且也能提高编译器的工作效率
	std::cout << "move constructor" << std::endl;
}
DataAgrp& DataAgrp::operator=(const DataAgrp & dgp)			//拷贝赋值运算符
{
	if (this == &dgp)
	{
		return *this;
	}
	m_dataA = dgp.m_dataA;
	return *this;
}
DataAgrp& DataAgrp::operator=(DataAgrp && dgp) noexcept			//移动赋值运算符
{
	if (this == &dgp)
	{
		return *this;
	}
	m_dataA = dgp.m_dataA;
	dgp.m_dataA = nullptr;
	return *this;
}
DataAgrp::~DataAgrp() {}

static DataAgrp return_DataAgrp(DataAgrp & datagrp)
{
	DataAgrp agrp(datagrp);			//这一步发生了拷贝构造，将实参拷贝给了局部的DataAgrp对象
	return agrp;			//这一步局部对象中的数据被移动给了临时对象，因为局部对象即将销毁，意味着以后不再会使用，而且我们定义了移动构造函数，所以编译器选择调用移动构造函数，不然会调用拷贝构造函数
}

void move_constructor()
{
	//移动构造函数，并不是将某一块内存区域中的值搬到另一块内存区域，而是直接转交了内存的所有权
	//移动构造函数，要确保数据从原对象移动到新对象之后，原对象与这些数据断开了关系，即使销毁了原对象，这些数据也能在新对象中正常使用
	//移动构造函数调用后，原对象就不应该被再次使用
	DataA dta(208);
	DataAgrp dtagrp_a(dta);
	DataAgrp dtagrp_b(dtagrp_a);			//copy constructor
	std::cout << dtagrp_a.m_dataA << std::endl;
	std::cout << dtagrp_b.m_dataA << std::endl;
	DataAgrp dtagrp_c = return_DataAgrp(dtagrp_a);			//dtagrp_c接收了函数返回的临时对象。此处既发生了拷贝构造，又发生了移动构造，具体原因看函数定义部分的分析
	std::cout << dtagrp_a.m_dataA << std::endl;
	std::cout << dtagrp_c.m_dataA << std::endl;
	//显式调用移动构造函数
	DataAgrp dtagrp_d(std::move(dtagrp_b));
	std::cout << dtagrp_d.m_dataA << std::endl;
	std::cout << dtagrp_b.m_dataA << std::endl;			//空指针，与移动后的数据已经打断关系

	//移动赋值运算符
	DataAgrp dtagrp_e(dta);
	std::cout << "dtagrp_e.m_data:　" << dtagrp_e.m_dataA << std::endl;
	DataAgrp dtagrp_f = std::move(dtagrp_e);
	//拷贝赋值运算符
	DataAgrp dtagrp_g = dtagrp_f;
	dtagrp_g = dtagrp_d;
	std::cout << "dtagrp_e.m_data:　" << dtagrp_e.m_dataA << std::endl << dtagrp_f.m_dataA << std::endl
		<< dtagrp_g.m_dataA << std::endl;

	//合成的移动构造函数和移动赋值运算符
	//一旦我们定义了自己的拷贝构造函数，或拷贝赋值运算符，或是析构函数，编译器将不会为这个类合成默认的移动赋值运算符和移动构造函数
	//如果我们没有定义自己的移动构造函数和移动赋值运算符，编译器会调用拷贝构造函数和拷贝赋值运算符代替移动操作
	//只有我们的类没有自己版本的拷贝构造函数和拷贝赋值运算符，并且没有定义析构函数，而且所有非静态类成员都可以移动，编译器才会合成移动赋值运算符和移动构造函数
		//什么样的非静态类成员是可以移动的：1 内置类型的类成员；2 定义了移动操作相关函数的类型的类成员
}