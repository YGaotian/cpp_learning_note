#include "header_learning.h"

Myclass& Myclass::_getSelf()
{
	//this是一个Myclass * const指针常量，指向类的实例化对象本身的地址，*this可以返回对象本身
	return *this;
}

void this_learning()
{
	Myclass mycl2;
	std::cout << mycl2._getSelf().numA << std::endl;
}