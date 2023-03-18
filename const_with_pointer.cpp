#include "header_learning.h"

void const_pointer_and_pointer_const()
{
	int val_a = 100;
	int val_b = 200;
	const int* cst_ptr = &val_a;//const int * == int const *
	cst_ptr = &val_b;
	//*cst_ptr = 101; cannot do
	std::cout << "The value of val_a is:" << val_a << " with the address:" << &val_a << std::endl
		<< "The value of val_b is:" << val_b << " with the address:" << &val_b << std::endl
		<< "the address pointed by cst_ptr is:" << cst_ptr << " , its value is:" << *cst_ptr << std::endl
		<< "cst_ptr is a const pointer that the variable pointed by "
		<< "itself can be changed while the value of the variable cannot be changed." << std::endl;
	std::cout << "=========================" << std::endl;
	int* const ptr_cst = &val_a;
	*ptr_cst = val_b;
	//ptr_cst = &val_b; cannot do
	std::cout << "The value of val_a is:" << val_a << " with the address:" << &val_a << std::endl
		<< "The value of val_b is:" << val_b << " with the address:" << &val_b << std::endl
		<< "the address pointed by ptr_cst is:" << ptr_cst << " , its value is:" << *ptr_cst << std::endl
		<< "ptr_cst is a pointer-type const value that the variable pointed by "
		<< "itself cannot be changed while the value of the variable can be changed." << std::endl;
	/*
	常量指针const *是一个指向常量类型的变量的指针，它的指向可以修改，但不能通过它去修改指向的变量的值，因为这个指针把它所指向的变量视为常量
	指针常量* const是一个指针类型的常量，因为是常量所以它指向的对象不能更改，但可以通过它去更改指向的对象的值
	*/
	const int cst_val_b = 20;
	//int* const ptr_cst_b = &cst_val_b; cannot do
	const int* cst_ptr_b = &cst_val_b;
	//*cst_ptr_b = 0; cannot do
}