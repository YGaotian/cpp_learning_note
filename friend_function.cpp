#include "header_learning.h"

void Man::sayPassword() const
{
	std::cout << "Password is: " << name << "2021" << std::endl;
}

void tellMeYourPassword(const Man& m)
{
	//普通的外部函数是无法调用Man实例的私有成员函数sayPassword的，但是在Man的类声明中，将void tellMeYourPassword()声明为了友元函数，所以现在可以调用
	m.sayPassword();
}

void friend_function()
{
	char name[20] = "Biden";
	Man man(name);
	tellMeYourPassword(man);
}