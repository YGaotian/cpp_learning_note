#include "header_learning.h"

void ezfunc(int);//prototype
/*
注意！！！
在函数外无法进行赋值操作，只能在函数外进行声明，函数内进行赋值，或者在函数外进行初始化
*/
void (*ezf_ptr)(int a) = ezfunc;//func pointer initialization, remember to use () to make sure ezf_ptr is a pointer, or it will be a function that returns nothing
//或者这样
void (*ezf_ptr_2)(int);//在函数外声明，但不赋值

void function_pointer()
{
	//两种通过函数指针调用函数的写法，都可以执行
	ezf_ptr(12);
	(*ezf_ptr)(50);
	ezf_ptr_2 = ezfunc;//函数内赋值
	(*ezf_ptr)(66);
	//鉴于这里有两个函数指针，如果有不止两个函数指针，当这些指针数量庞大的时候，我们希望有一个数组在管理它们，这样调用的时候也会方便
	//声明一个函数指针的数组,方括号要写在函数数组名后面，特征标在最后，别忘了使用()将*与数组名包含在一起，否则就是在声明一个void*类型的函数数组了，函数数组是无法被声明的，会报错
	void (*ezf_pArray[2])(int) = { ezf_ptr, ezf_ptr_2 };//顺便把初始化做了吧
	ezf_pArray[1](54565);

	//下面再声明一个指向这个数组的指针
	//(*funcPtrArr_ptr)强调了这是一个指针，紧随其后的[2]表示这个指针指向包含2个元素的数组，(*(*funcPtrArr_ptr)[2])最外层括号里的*表明所指向的数组中，元素是指针，就是说这是个指向指针数组的指针，
	//最后，前面的void表明了指向数组的指针的类型，注意必须先用括号将*与(*funcPtrArr_ptr)[2]先结合起来，否则由于运算符优先级关系，*将与void结合，末尾还带有特征标(int)会使得声明变成一个void*类型的函数数组声明
	void (*(*funcPtrArr_ptr)[2])(int) = &ezf_pArray;//顺便做了初始化
	//也可以用自动类型推断简化操作
	auto funcPtrArr_ptr_2 = &ezf_pArray;
	//要调用函数，可以这样
	(*funcPtrArr_ptr_2)[1](122);
}

void ezfunc(int a)
{
	std::cout << "your arg is:" << a << std::endl;
}