#include "header_learning.h"

GrandBase::GrandBase() : m_grandRank("default Grand")
{
	std::cout << "GrandBase created" << std::endl;
}
GrandBase::GrandBase(std::string rank) : m_grandRank(rank)
{
	std::cout << "GrandBase created" << std::endl;
}
GrandBase::~GrandBase()
{
	std::cout << "GrandBase destroyed" << std::endl;
}

FatherBaseA::FatherBaseA() : m_fatherARank("default FatherA"), objID(00001),	//一旦使用虚继承，继承链后面的Grandson类在调用构造函数以实例化时，
								GrandBase("default FatherA's base")				//	通过构造函数调用链自动调用的FatherBaseA类构造函数就不再负责初始化基类GrandBase了，而是由Grandson类自己初始化
{																									
	std::cout << "FatherBaseA created" << std::endl;
}
FatherBaseA::FatherBaseA(std::string rank, int oid) : m_fatherARank(rank), objID(oid),	//如上所述，当该类的子类Grandson实例化（调用构造函数）时，不会通过此处初始化列表的GrandBase有参构造函数来初始化
														GrandBase(rank+"'s base")		//	GrandBase成员，而是由子类Grandson自己初始化
{																									
	std::cout << "FatherBaseA created" << std::endl;
}
FatherBaseA::~FatherBaseA()
{
	std::cout << "FatherBaseA destroyed" << std::endl;
}

FatherBaseB::FatherBaseB() : m_fatherBRank("default FatherB"), GrandBase("default FatherB's base")			//同上，当子类Grandson实例化，调用构造函数时，不会通过此处初始化列表的GrandBase有参构造函数
{																											//	来初始化GrandBase成员，而是由子类Grandson自己初始化
	std::cout << "FatherBaseB created" << std::endl;
}
FatherBaseB::FatherBaseB(std::string rank) : m_fatherBRank(rank), GrandBase(rank + "'s base")			//如上所述，当子类Grandson实例化，调用构造函数时，不会通过此处初始化列表的GrandBase有参构造函数
{																										//	来初始化GrandBase成员，而是由子类Grandson自己初始化
	std::cout << "FatherBaseB created" << std::endl;
}
FatherBaseB::~FatherBaseB()
{
	std::cout << "FatherBaseB destroyed" << std::endl;
}

Grandson::Grandson() : m_grandsonRank("default Grandson"), FatherBaseA("default Grandson's FatherBaseA", 00001),			//此处Grandson自己来初始化父类和爷爷类，而不会通过调用父类的构造函数初始化爷爷类
							FatherBaseB("default Grandson's FatherBaseB"), GrandBase("default Grandson's GrandBase")			//如果此处Grandson自己没有初始化GrandBase，那么GrandBase会调用默认构造
{
	std::cout << "Grandson created" << std::endl;
}
Grandson::Grandson(std::string rank) : m_grandsonRank(rank), FatherBaseA(rank+"'s FatherBaseA", 00001),			//此处初始化父类和爷爷类
											FatherBaseB(rank+"'s FatherBaseB"), GrandBase(rank+"'s GrandBase")			//如果此处Grandson自己没有初始化GrandBase，那么GrandBase会调用默认构造
{
	std::cout << "Grandson created" << std::endl;
}
Grandson::~Grandson()
{
	std::cout << "Grandson destroyed" << std::endl;
}

void virtual_inheritance()
{
	//如果一个类A有两个子类B1和B2，又有一个类C继承了B1和B2，那么类C中就会继承到分别存在于B1和B2中的两份类A的成员，这样的话无法通过类C访问继承链中的顶级基类A的成员，除非使用作用域前缀，否则会报错提示该成员不明确
	//所以要使用虚继承，在类声明时，继承部分要加virtual前缀
	//虚继承对基类的直接子类无实际意义，因为它只是使基类中的成员在所有子类中只存在一份，也就是说在多重继承时，如在本例中只对同时继承了FatherBaseA和FatherBaseB的Grandson有意义，避免了出现两份GrandBase类成员的现象
	Grandson gs_1;
	std::cout << std::endl;
	std::cout << gs_1.m_grandRank << std::endl;			//由于使用了虚继承，所以尽管同时继承了FatherBaseA和FatherBaseB，GrandBase类中的成员只有唯一的一份
	std::cout << std::endl;
	Grandson gs_2("BIG HEAD SON");
	std::cout << std::endl;
	std::cout << gs_2.m_grandRank << " and " << gs_2.m_fatherARank << " with ID " << gs_2.objID << std::endl;
	std::cout << std::endl;
	FatherBaseB faB_1("LITTLE HEAD FATHER");
	std::cout << std::endl;
	std::cout << faB_1.m_fatherBRank << " and " << faB_1.m_grandRank << std::endl;
	std::cout << std::endl;
	FatherBaseB faB_2;
	std::cout << std::endl;
	std::cout << faB_2.m_fatherBRank << " and " << faB_2.m_grandRank << std::endl;
	std::cout << std::endl;
	FatherBaseA faA_1("Base class FatherA", 1001);
	std::cout << faA_1.m_fatherARank << " with ID " << faA_1.objID << " and " << faA_1.m_grandRank << std::endl;
	//如果以后Grandson也有了子类，那么它的子类也要自己初始化所有基类
	//另外，虽然在inherited_constructor一节中说过，继承链中的类的初始化顺序是按照类声明时所写的在派生列表中的先后顺序执行的，但使用了虚继承的情况不一样
	//	不管虚基类的子类写在了孙子类的派生列表中的第几位，虚基类都会优先被初始化，然后才会按照派生列表中的顺序初始化虚基类的子类和其余的类
	//	那如果有多个虚基类呢？那么编译器会按照派生列表中的顺序，先找列表中的第一个类有没有虚基类，如果有就先初始化，再找第二个类有没有虚基类，以此类推
	//销毁顺序和构造顺序相反
	//如果FatherBaseA和FatherBaseB中都有与虚基类GrandBase同名的成员，那么它们就会覆盖虚基类中的该成员
	//	然而由于它们是平级的关系，在Grandson中，如果不通过作用域运算符显式地作限定，依然无法区分它们，这时候我们可以在该子类中也定义一个同名的成员以覆盖父级

	//虚继承常用于菱形继承的时候，如果基类有虚函数，子类没有自己的虚函数，那么孙子类就可以不实现这个函数，如果子类也实现了基类中的虚函数，那么孙子类就需要自己实现这个函数了
	//因为菱形继承中，两个子类都一起实现了基类中的函数，到了孙子类就会发现两个同名的函数，会产生歧义，只有自己也实现了这个函数，才能把有歧义的函数覆盖掉
}