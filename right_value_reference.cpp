﻿#include "header_learning.h"

void right_value_reference()
{
	int&& r_ref = 6;			//右值引用&&有点像一个临时变量的感觉，可以直接引用一个常量，其实是将一个右值引用绑定到了常量上
	r_ref = 666;			//并且可以随意更换引用对象
	//我们希望将右值引用绑定到一些即将销毁的对象或一些临时对象上
	//临时对象被系统当做右值，左值引用无法绑定到右值
	//但const &可以绑定到右值上，尽管它也是一个左值引用
	const std::string& AString{ "Oh yeah" };			//此处的"Oh yeah"其实是赋给了一个临时对象
	//前置递增递减的变量，如++i，--i，它们是左值，可以被赋值，也可以用左值引用来引用它们
	//后置递增递减的变量，却是右值，为什么呢，因为后置递增递减的变量是先使用，后修改的，这其中是编译器先生成了一个临时对象，记录了该变量的值，然后对该变量进行了+1或-1操作，我们使用的时候，用的是这个临时对象，是个右值，使用完以后，临时对象被销毁
	int i = 10;
	r_ref = i++;
	std::cout << r_ref << " != " << i << std::endl;
	int& l_ref = r_ref;
	std::cout << "r_ref refers to a right value, but r_ref itself is a left value" << std::endl;			//所以我们可以用一个左值引用绑定到右值引用这个对象本身上去
	std::cout << "l_ref: " << l_ref << std::endl;
	l_ref = 20;
	std::cout << "r_ref: " << r_ref << std::endl;
	//右值引用被c++11引入的目的
	//我们知道一个类对象可以调用拷贝构造函数，将其他同类对象的数据拷贝到自己身上，这需要开辟一块新的内存空间
	//其实还有一种构造函数叫做移动构造函数，与之对应的还有一个移动赋值运算符，与拷贝赋值运算符一样是等号=
	//移动构造函数可以直接接管另一个同类对象的数据的地址，达到了使用另一个对象的数据的目的，同时，还能提高程序运行效率，减少开销，但需注意的是这意味着另一个对象将不能再被使用

	//std::move
	//该函数其实并不做任何移动操作，它只是可以将一个左值强制转换成一个右值
	int q = 6;
	//int&& w = q;			//不行
	int&& w = std::move(q);			//成功，将左值q转换成了右值，并将右值引用w绑定到了q上
	q = 7;
	std::cout << w << std::endl;			//7
	w = 8;
	std::cout << q << std::endl;			//8

	int&& e = 9;	//右值引用，这个引用对象e本身是个左值，是有内存地址的
	//int&& r = e;			//不行，因为e本身是左值，需要使用std::move()来转换为右值
	int&& r = std::move(e);
	r = 10;
	std::cout << "e == r == " << e << std::endl;
	//再来看看string
	std::string str1 = "wolf";
	std::string str2 = std::move(str1);		//这里str2不是一个右值引用，但是接收了std::move(str1)，并不是说std::move()将str1移动到了str2里面
	//结果是str2是wolf，str1为空
	std::cout << str2 << " and " << str1 << std::endl;			//这并不是move的作用，move只是将str1转换为右值而已，它并没有将str1的值移动到str2，真正做了移动操作的其实是str2的移动构造函数，因为移动构造函数接收一个右值引用参数
	//然而，由于一些限制，string对象本身的移动构造函数并没有将str1中的字符串的地址移交给str2，而是依然开辟了一块新内存空间，仅仅是将值移动了过来，这其中并没有节省一次开辟内存的操作
	//一旦对某对象使用了move函数，一个建议是该对象就应该被当做不能再被使用的对象去对待，因为通常将它转换为右值是为了移动该对象的成员到另一个对象中去，尽管有些场景它依然可以被再次使用，比如将一个右值引用绑定到该对象时需要使用move函数将该对象转换为右值
}