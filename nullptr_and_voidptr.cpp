#include "header_learning.h"

void nullptr_and_voidptr()
{
	/*
	nullptr和NULL的功能一样，都是空指针，但是NULL其实是整型0，
	而nullptr是一个明确的指针类型的对象，指向与NULL相同的地址
	void*是万能指针，可以在最初指向空指针，并在之后的实际使用中转换成其它类型指针，但必须进行显式类型转换，不支持隐式转换
	*/
	void* vptr = NULL;
	void* voidptr = nullptr;
	std::cout << vptr << std::endl;
	std::cout << voidptr << std::endl;
	int* v2intptr = (int*)vptr;
	double* void2dblptr = (double*)voidptr;
	std::cout << v2intptr << std::endl;
	std::cout << void2dblptr << std::endl;
	int five = 5;
	double six = 6.0;
	v2intptr = &five;
	void2dblptr = &six;
	std::cout << *v2intptr << " and " << *void2dblptr << std::endl;
	//也可以将void*指向其他类型，并且这种类型转换是隐式的，无需进行强制类型转换
	int anum = 77;
	int* int_ptr = &anum;
	void* void_ptr = int_ptr;
	//但是不能对void*取值
	//*void_ptr;  DON'T DO THIS
	std::cout << *(int*)void_ptr << std::endl;//如果非要取值，可以强制类型转换一下
}