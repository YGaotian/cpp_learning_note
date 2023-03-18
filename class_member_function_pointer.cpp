#include "header_learning.h"

void MemberFuncPtrClass::generalMemberFunc(int argInt)
{
	if (argInt == 1)
		std::cout << "generalMemberFunc called" << std::endl;
	else
		std::cout << "generalMemberFunc called once \ngeneralMemberFunc called twice" << std::endl;
}

void MemberFuncPtrClass::virtMemberFunc()
{
	std::cout << "virtMemberFunc called" << std::endl;
}

void MemberFuncPtrClass::staticMemberFunc()
{
	std::cout << "staticMemberFunc called" << std::endl;
}

void class_member_function_pointer()
{
	//如何声明一个普通类成员函数指针呢，格式如下：
	//	类名::*成员函数名，就是说，对于普通类成员函数指针，我们必须要使用类名进行限定，不然类型会不匹配
	//	因为普通类成员函数并不是随着类实例的构建而产生的，在类实例被构建之前，类成员函数的地址就已经存在，它是跟随着类本身同时产生的，也就是说，它是属于类本身的，若要定义一个指向它的指针，那么这个指针的类型也需要被限定
	void (MemberFuncPtrClass:: * generalMemberFunc_ptr)(int);
	//定义时是这样的：指针名 = &类名::成员函数名
	generalMemberFunc_ptr = &MemberFuncPtrClass::generalMemberFunc;			//这是一个真正的内存地址
	//虽然类成员函数的地址不属于任何类实例，但若想调用该函数的指针，我们依然需要依靠类实例，格式是：(类实例名.*函数指针名)()，如果是类实例的指针，则是：(类实例指针名->*函数指针名)()
	MemberFuncPtrClass mfpc_1, * mfpcptr_1;
	mfpcptr_1 = &mfpc_1;
	(mfpc_1.*generalMemberFunc_ptr)(1);
	(mfpcptr_1->*generalMemberFunc_ptr)(2);

	//如何声明一个类成员虚函数指针呢，格式其实与普通成员函数一样
	void (MemberFuncPtrClass:: * virtMemberFunc_ptr)();
	virtMemberFunc_ptr = &MemberFuncPtrClass::virtMemberFunc;			//虚函数指针指向的其实也是一个真正的内存地址
	//使用时也同普通类成员函数指针一样，需要绑定至类实例
	MemberFuncPtrClass mfpc_2, * mfpcptr_2;
	mfpcptr_2 = &mfpc_2;
	(mfpc_2.*virtMemberFunc_ptr)();
	(mfpcptr_2->*virtMemberFunc_ptr)();

	//如何声明静态成员函数指针呢，只需要直接在函数指针变量名前面加一个*即可
	void (*staticMemberFunc_ptr)();
	//定义时与普通类成员函数指针与类成员虚函数指针无区别，使用&类名::函数名获取函数的地址
	staticMemberFunc_ptr = &MemberFuncPtrClass::staticMemberFunc;			//这也是一个真正的内存地址
	//若要通过函数指针调用静态成员函数，就不需要绑定对象实例了，直接使用即可
	staticMemberFunc_ptr();
}