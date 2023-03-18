﻿#include "header_learning.h"

void why_we_can_put_class_definition_into_header_files()
{
	std::cout << "头文件中可以写类（class）的定义。因为在程序中创建一个类的对象时，"
		<< "编译器只有在这个类的定义完全可见的情况下，才能知道这个类的对象应该如何布局，"
		<< "所以，关于类的定义的要求，跟内联函数是基本一样的。所以把类的定义放进头文件，在"
		<< "使用到这个类的 .cpp 文件中去包含这个头文件，是一个很好的做法。在这里，值得一提的是，"
		<< "类的定义中包含着数据成员和函数成员。数据成员是要等到具体的对象被创建时才会被定义（分配空间）"
		<< "，但函数成员却是需要在一开始就被定义的，这也就是我们通常所说的类的实现。一般，我们的做法是，"
		<< "把类的定义放在头文件中，而把函数成员的实现代码放在一个 .cpp 文件中。这是可以的，"
		<< "也是很好的办法。不过，还有另一种办法。那就是直接把函数成员的实现代码也写进类定义里面。"
		<< "在 C++ 的类中，如果函数成员在类的定义体中被定义，那么编译器会视这个函数为内联的。因此，"
		<< "把函数成员的定义写进类定义体，一起放进头文件中，是合法的。注意一下，如果把函数成员的定义写在"
		<< "类定义的头文件中，而没有写进类定义中，这是不合法的，因为这个函数成员此时就不是内联的了。一旦头"
		<< "文件被两个或两个以上的 .cpp 文件包含，这个函数成员就被重定义了" << std::endl;
}