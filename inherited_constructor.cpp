#include "header_learning.h"

Papa::Papa() : m_hair(0), m_tall(185), m_arg(args::lemon)
{
	std::cout << "Papa constructor called" << std::endl;
}
Papa::Papa(int h, float t, args arg) : m_hair(h), m_tall(t), m_arg(arg)
{
	std::cout << "Papa constructor called" << std::endl;
}
Papa::~Papa()
{
	std::cout << "Papa destroyed" << std::endl;
}

Mom::Mom() : m_feetSize(35.0f), m_appearence(appearance::notBad)			//在默认构造函数中，通常我们需要为所有成员设置默认值，即初始化，但此处没有手动初始化string类型的m_hairLen，因为默认会初始化为空字符串
{
	std::cout << "Mom constructor called" << std::endl;
}
Mom::Mom(float feetSize, std::string hairLen, appearance apr) : m_feetSize(feetSize), m_hairLen(hairLen), m_appearence(apr)
{
	std::cout << "Mom constructor called" << std::endl;
}
Mom::~Mom()
{
	std::cout << "Mom destroyed" << std::endl;
}

Kid::~Kid()
{
	std::cout << "Kid destroyed" << std::endl;
}

void inherited_constructor()
{
	//因为父类Papa的有参构造函数的参数列表中，有两个形参具有默认值，所以我们可以用3种不同数量参数的有参构造函数实例化子类，再加上Mom的有参构造函数，也有两个默认值，所以又有3种通过基类Mom的有参构造函数实例化子类的方法
	Kid k1(3000000);
	Kid k2(3000000, 180);
	Kid k3(3000000, 165, args::lemon);
	//Kid类继承了多个基类，但是有参构造函数无法混用，如果调用其中一个基类的有参构造函数，继承自有参构造函数没有被调用的那个基类的子类成员，它不会被初始化
	Kid k4(37.5f, "so long");
	Kid k5(37.77f, "not too long", appearance::beautiful);
	Kid k6(36.8f);
	std::cout << k1.m_hair << std::endl << k1.m_tall << std::endl << static_cast<int>(k1.m_appearence) << " and " << k1.m_hairLen << std::endl;			//m_hairLen没有被初始化，打印结果为空
	std::cout << k2.m_hair << std::endl << k2.m_tall << std::endl << static_cast<int>(k2.m_appearence) << " and " << k2.m_hairLen << std::endl;
	std::cout << k3.m_hair << std::endl << k3.m_tall << std::endl << static_cast<int>(k3.m_appearence) << " and " << k3.m_hairLen << std::endl;
	std::cout << k4.m_tall << " and " << static_cast<int>(k4.m_appearence) << " and " << k4.m_hairLen << std::endl;			//k4.m_tall没有被初始化，打印结果是乱码
	std::cout << k5.m_feetSize << " and " << static_cast<int>(k5.m_appearence) << " and " << k5.m_hairLen << std::endl;	
	std::cout << k6.m_feetSize << " and " << static_cast<int>(k6.m_appearence) << " and " << k6.m_hairLen << std::endl;	
	Kid k7;			//成功通过编译，因为父类中有默认构造函数，所以子类中编译器也合成了默认构造函数
	std::cout << "k7.m_hair: " << k7.m_hair << "k7.m_feetSize" << k7.m_feetSize << std::endl;
}