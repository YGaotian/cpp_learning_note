#include "header_learning.h"

void Myclass::editMemberValue(int& member, int val)
{
	member = val;
}

//常函数在定义和声明时都要在函数名后面加const
void Myclass::showAllMember() const
{
	sumOfAllNums = numA + numB + numC + numD + c_numE;//sumOfAllNums被声明为mutable，所以可以在常函数中赋值
	numA += 1000;//因为numA被声明为mutable，所以即使在常函数中依然可以修改numA的值，详见mutable_learning一节
	//numB += 2000;非mutable成员，所以无法修改值，会报错
	std::cout << "numA+1000:" << numA << std::endl << "numB:" << numB << std::endl
		<< "numC:" << numC << std::endl << "numD:" << numD << std::endl << "c_numE:" << c_numE << std::endl
		<< "sumOfAllNums:" << sumOfAllNums << std::endl;
}

void const_function_learning()
{
	Myclass myc(12, 20);
	myc.showAllMember();//普通对象可以调用常函数
	myc.numD = 4445;//普通对象可以修改自身的成员的值
	myc.editMemberValue(myc.numC, 6676);//普通对象可以调用没有被声明为常函数的成员函数
	std::cout << myc.numC << std::endl;
	const Myclass myc2(133, 212);
	myc2.showAllMember();//常量对象也可以调用常函数
	//myc2.numD = 66;但常量对象不可以修改自身的成员的值
	//myc2.editMemberValue(myc2.numC, 776);常量对象也不可以调用没有被声明为常函数的成员函数
}