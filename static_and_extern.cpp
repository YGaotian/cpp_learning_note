#include "header_learning.h"

//定义Myclass中的静态成员变量，静态成员变量在定义时不用在开头加上static关键字，普通成员变量在创建类对象时被分配内存
//而静态成员变量是隶属于整个类的，所以它并不在类对象实例被创建的时候分配内存，所以一般我们在某一个cpp文件的开头定义
//静态成员变量，以确保它在任何函数调用之前被初始化（分配空间）
int Myclass::numS = 999;    //静态类成员对象的生命周期是整个程序的运行周期

//如果在函数外初始化了一个static，该变量也存储在静态存储区，该变量的作用范围是当前cpp文件，在其他cpp文件中无法被访问，当然，也可以定义一个静态函数，如static int intAdd(int , int); 同样该函数的作用范围是当前文件
static int k = 123456;

//注意！！！父类的静态成员变量不会被子类继承，但可以通过子类访问

//extern可以用来访问另一个cpp文件中的非静态对象，我们在这里定义的变量,可以在main_learning.cpp中访问
int global_k = 123477;			//函数体外面只能初始化变量，而不能只是对变量赋值

void static_in_func()
{
	//如果在一个函数内部初始化一个static变量，那么这个局部静态变量就会存储在静态存储区，在调用过该函数后，该变量的值不变
	//在下一次调用该函数时，该变量的值不会再次初始化，而是继续用上一次的值
	//如果一个static变量没有初始化且没有被赋值，那么编译器会为其赋值0
	static int static_int_i = 10;
	static_int_i += 1;
	std::cout << static_int_i << std::endl;
	if (static_int_i < 15)
		static_in_func();
}

//静态成员函数的定义依然不用再在开头写一边static关键字，它只能访问静态成员变量，无法访问普通成员变量
void Myclass::printNumSValue()
{
	std::cout << numS << std::endl;
}

void static_learning()
{
	static_in_func();
	//我们用类名::静态成员变量名或类对象名.静态成员变量名来访问静态成员变量
	std::cout << Myclass::numS << std::endl;
	//一旦静态成员变量被修改，那么所有的类对象中的静态成员变量是一起被改变的，因为静态成员不属于类对象，而是属于类，所有通过类对象访问静态成员得到的东西都是同一个存在于类之中的对象
	Myclass mycl3;
	mycl3.numS += 10;
	Myclass mycl4;
	mycl3.printNumSValue();
}