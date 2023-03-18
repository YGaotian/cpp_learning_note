#include "header_learning.h"

Flower::Flower(int petalNum) :m_petalNum(petalNum)			//petal有默认值，为3，默认值在类声明中已确定
{
	std::cout << "A flower which has " << m_petalNum << " petals created" << std::endl;
}
Flower::Flower(const Flower& fl):m_petalNum(fl.m_petalNum)
{
	std::cout << "Flower copied" << std::endl;
}
Flower::~Flower()
{
	std::cout << "A flower which has " << m_petalNum << " petals destroyed" << std::endl;
}
Flower& Flower::operator=(const Flower& fl)
{
	m_petalNum = fl.m_petalNum;
	std::cout << "Flower operator= called" << std::endl;
	return *this;
}

void get_string_ref_1(std::string& str)
{
	//do nothing
}
void get_string_ref_2(const std::string& str)
{
	std::cout << &str << std::endl;
}

Myclass returnMyclass_1()
{
	Myclass amc(2, 4, 4, 3);
	return amc;
}
Myclass returnMyclass_2()
{
	return Myclass(2, 4, 4, 3);
}

void flower_temp_example()
{
	//下面的代码在运行时悄悄地创建了临时对象，我们无法直接看到它，但它确实存在，并使得程序运行时多干了三件事
	Flower flower;			//调用了有参构造函数，使用了参数的默认值
	std::cout << "petal: " << flower.m_petalNum << std::endl;
	flower = 5;			//将数字5通过隐式类型转换，转换成了Flower类型，实际就是创建了一个m_petalNum为5的Flower类型的临时对象，那么这里就会多调用一次构造函数
						//然后通过拷贝赋值运算符赋给了flower对象，最后临时对象调用析构函数被销毁
	std::cout << "petal: " << flower.m_petalNum << std::endl;
	flower.m_petalNum = 12;
	std::cout << "petalNum changed: " << flower.m_petalNum << std::endl;
	//如果上述代码合成一句，就可以节省开销
	Flower flower2 = 7;			//程序运行结果只有两行，即构造函数和析构函数，没有临时对象的创建，直接使用了flower2预留的内存空间初始化的
}

void string_temp_example()
{
	//我们再来看另一种情况，它使用引用
	std::string word_1 = "I love China";
	char word_2[13] = "I love China";
	get_string_ref_1(word_1);
	//get_string_ref_1(word_2);			报错了，看上去string&不能接受一个char[]作为参数
	std::cout << &word_1 << std::endl;	//成功，输出结果与下一行相同，输出了引用的对象的地址
	get_string_ref_2(word_1);			//成功，输出结果与上一行相同，输出了引用的对象的地址

	//但是这个就可以接收char[]作为参数，函数定义中接受的是const string&
	get_string_ref_2(word_2);			//这行与下一行的输出结果不同，尽管“本意”是为了输出引用的对象的地址
	std::cout << &word_2 << std::endl;	//这行与上一行的输出结果不同，尽管“本意”是为了输出引用的对象的地址
	//原来原因是这样：因为传入char[]的时候，该对象会被隐式类型转换为string，就是说生成了一个临时的string对象，来存储char[]对象的值，再被函数所引用
	// 所以上面两行代码的输出结果不一样，输出了不同的地址，原因就是一个输出了原对象的地址，另一个输出了临时对象的地址
	// 如果没有const，编译器就会怀疑一个临时对象可能被修改，然而因为是临时对象，所以程序员并不会知道这个对象的名字，在函数中通过引用修改了该临时对象的值后，
	// 等到函数退出时，这个临时对象又无法被程序员访问，这样毫无意义
	// 另一方面，还记得吗，上节说过临时对象是右值，右值也是无法被修改的！所以，c++不允许非const左值引用指向临时对象，c++只能使用const左值引用去接收临时对象								
}

void myclass_temp_example()
{
	//还有一种情况
	std::cout << "=== 版本一 ===" << std::endl;
	returnMyclass_1();			//由于这个函数中，创建了一个局部的Myclass对象amc，所以会调用一次构造函数，到了函数返回的时候，由于局部对象无法在函数退出后继续存在，所以该对象会被拷贝到一个临时对象上
								//此时，临时对象的拷贝构造函数被调用了，然后局部对象会被销毁，调用了析构函数，而临时对象被返回出来
								//但是由于没有任何函数外部的对象来接收这个临时对象，所以该临时对象会立刻调用析构函数进行销毁
	//上面这个版本的函数会调用两次构造函数和两次析构函数，但下面这个版本构造函数和析构函数的调用会各减少一次，减少了开销
	std::cout << "=== 版本二 ===" << std::endl;
	Myclass bmc = returnMyclass_2();			//因为这个版本的函数并没有在函数内部创建局部对象，并且函数直接返回了参数是2,4,4,3的临时对象，而且有一个函数外部的bmc变量接收了该临时对象
												//所以只有临时对象的构造函数调用，以及在程序结束时bmc被销毁，产生的析构函数调用，这样就降低了程序的开销，提高了运行效率
}

void temporary_object()
{
	flower_temp_example();
	string_temp_example();
	myclass_temp_example();
}