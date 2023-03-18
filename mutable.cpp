#include "header_learning.h"

void mutable_learning()
{
	//writing the keyword "mutable" before a member variable that allows us to edit it
	//even if it belongs to a const object
	const Myclass mycl(10, 20, 30, 444);
	mycl.numA = 777;//numA a mutable member
	//mycl.numB = 888;numB is not a mutable member
	std::cout << "numA:" << mycl.numA << std::endl;
	//we can also edit a mutable members inside a const function
	//see details in introduction_to_class_serious.cpp
	mycl.showAllMember();
}