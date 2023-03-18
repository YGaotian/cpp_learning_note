#include "header_learning.h"

void Dude::repeatPassword(const Man& m) const
{
	//Dude类是Man类的友元类，所以Dude类的所有方法都可以访问Man类的私有成员以及调用Man类的私有方法
	m.sayPassword();
}

void friend_class()
{
	Dude* dd = new Dude();
	char supername[20] = "Titan";
	Man superman = supername;
	dd->repeatPassword(superman);
	delete dd;
}