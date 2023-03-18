#include "header_learning.h"

Teddy::~Teddy() = default;

//cpp风格指针类型转换结果检查函数
void is_ptr_type_convertion_succeeded(const void* ptr)
{
	if (ptr == nullptr) std::cout << "type convertion failed." << std::endl;
	else std::cout << "type convertion succeeded." << std::endl;
}

void RTTI_learning()
{
	//RTTI 即 run time type identification，这种技术使得程序可以在运行时识别基类指针（或引用）所指的（或所引用的）对象的实际类型
	//RTTI有两个运算符，分别是
	//dynamic_cast：将基类指针或引用安全地转换为子类指针或引用
	//typeid：返回指针或引用所指对象的实际类型
	//注意：基类中必须有至少一个虚函数，否则RTTI的两个运算符可能无法按照预期的那样正常工作，因为只有虚函数的存在，才能使得系统在内部查找绑定到基类指针上的对象类型的虚函数表，以得到该对象的详细信息

	//已知Dog是Canine的子类
	char food[10] = "pizza";
	Canine* c = new Dog(food);
	//虽然父类指针c指向的是子类Dog的实例对象，但是它依然是基类指针，无法调用非虚函数的子类成员函数，只有子类对象调用父类非虚函数的操作
	//所以想把父类指针c转换为子类指针
	Dog* c_dc = (Dog*)(c);			//c语言风格指针类型转换
	c_dc->testfunc();
	//虽然可以这么做，但这并不安全，因为如果有另一个类，假设叫Lion也同样继承了基类Canine，我们同样可以用c风格类型转换将基类指针c转换为Lion指针，但c实际指向的是匿名的Dog类对象，这样程序就无法如预期地运行
	//所以我们应该使用c++风格的安全的类型转换，dynamic_cast，该运算符可以帮助我们检查基类指针是否可以转换为我们所写的目标类型的指针
    ///仅当A类型的基类指针a指向了B类型的子类对象b，a才可以dynamic_cast变成B类型指针
	Dog* cpp_dc = dynamic_cast<Dog*>(c);			//cpp风格指针类型转换
	cpp_dc->testfunc();

	//两种方式的区别如下
	Teddy* c_tc = (Teddy*)(c);			//c风格强制指针类型转换，不安全，因为没有类型检查，所以可以转换成功，而且没有任何提示
	Teddy* cpp_tc = dynamic_cast<Teddy*>(c);			//cpp风格强制指针类型转换，安全，因为有类型检查，所以不会转换成功，虽然不会报错，但转换后的结果是nullptr
	is_ptr_type_convertion_succeeded(c_tc);			//转换成功，得到了不安全的指针
	is_ptr_type_convertion_succeeded(cpp_tc);			//转换失败，得到了空指针
	//再来看看正确转换的指针在检查函数中运行的结果
	is_ptr_type_convertion_succeeded(cpp_dc);			//转换成功，得到了正确的子类指针

	//不论如何，别忘了释放内存，虽然有这么多指针，但由于都是指向同一个对象，所以只需要对任意一个指针释放一次内存即可，否则会对同一块内存释放多次
	delete cpp_dc;

	//上面的代码演示了指针的转换，下面看看引用的转换
	Canine* c2 = new Dog(food);
	Canine& cref = *c2;			//*c是匿名Dog对象本身
	Dog& dref = dynamic_cast<Dog&>(cref);
	dref.testfunc();			//至此都可以正常执行
	//对引用类型的转换失败，系统会抛出一个异常，而不是像空指针那样有一个空引用，这个异常被定义在标准库中，叫std::bad_cast，需使用try和catch处理
	try
	{
		Teddy& tref = dynamic_cast<Teddy&>(cref);
		std::cout << "引用类型转换成功" << std::endl;
	}
	catch (std::bad_cast)
	{
		std::cout << "引用类型转换失败" << std::endl;
	}
	std::cout << dref.id << std::endl;			//这里还没有被释放内存，所以可以查询的到成员变量的值
	delete c2;
	dref.testfunc();			//这里内存已经被释放了，因为是引用，虽然还可以调用成员函数，但实际上内存确实已经被释放
	std::cout << dref.id << std::endl;			//所以这里再一次输出，显示了乱码，因为这一块内存空间已经不是我们的可用区域了


	//下面来看看typeid运算符
	//typeid返回的是一个标准库类型 type_info 的常量对象的引用，也就是说，返回的其实是 const type_info 对象的引用，所以我们可以调用这个对象的各种成员方法
	std::cout << typeid(Canine).name() << std::endl;			//传入了类型名
	Canine* canine_ptr = new Dog;
	Canine& canine = *canine_ptr;
	Dog& dog = dynamic_cast<Dog&>(canine);
	std::cout << typeid(canine_ptr).name() << std::endl;			//传入了指针
	std::cout << typeid(dog).name() << std::endl;			//传入了引用
	delete canine_ptr;
	std::cout << typeid(666).name() << std::endl;
	std::cout << typeid("tql").name() << std::endl;
	//typeid常用来判断两个基类指针所指对象的类型是否一致
	Canine* cp = new Canine;
	Canine* cpd = new Dog;
	//但是有容易犯的陷阱错误
	//错误示范
	if (typeid(cp) == typeid(cpd))
	{
		std::cout << "same type" << std::endl;			//结果是same type，因为我们传入的是cp和cpd本身，typeid得到的是Canine*类型，如果我们想判断所指对象的类型，应该传入*cp和*cpd
	}
	else
	{
		std::cout << "different type" << std::endl;
	}
	//正确示范
	if (typeid(*cp) == typeid(*cpd))
	{
		std::cout << "same type" << std::endl;			//结果是same type，因为我们传入的是cp和cpd本身，typeid得到的是Canine*类型，如果我们想判断所指对象的类型，应该传入*cp和*cpd
	}
	else
	{
		std::cout << "different type" << std::endl;
	}
	//判断指针所指对象是否是某一个类型
	if (typeid(*cpd) == typeid(Dog))			//相等，但注意，基类中是有虚函数的，所以可以这么比较，如果基类没有虚函数，这个判断语句中的表达式就不会成立
	{
		std::cout << "*cpd type: class Dog" << std::endl;
	}

	//既然typeid返回的是一个const type_info&对象，那么我们当然可以用一个这样的常量去接收它
	const std::type_info& typeInfo = typeid(*cpd);
	std::cout << typeInfo.name() << std::endl;
}