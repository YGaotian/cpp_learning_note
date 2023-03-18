#include "header_learning.h"

void new_pointer_learning()
{
	//delete指向new的指针后，该指针所指向的内存被释放，这意味着不能再访问ptr所指向的地址，虽然允许这么干，但会有警告，如果尝试获取该指针所指向的地址中的值，会抛出异常
	//若想再次使用该指针，则需重新初始化该指针，使指针指向一个新的内存空间new xxx，或者也可以让它指向一个变量
	//别忘了，指针指向new开辟的内存空间，用完后要被delete掉，但是指向已存在的变量时则不需要也不能使用delete，
	std::string* ptr = new std::string;
	std::cout << ptr << std::endl;
	*ptr = "world";
	std::cout << *ptr << std::endl;
	delete ptr;
	//std::cout << "ptr after delete is:" << *ptr << std::endl;//CANNOT DO, ERROR
	ptr = new std::string;
	*ptr = "another";
	std::cout << ptr << std::endl;
	std::cout << *ptr << std::endl;
	delete ptr;
	std::string str = "hello";
	ptr = &str;
	std::cout << *ptr << " in the " << ptr <<std::endl;
	//可以在new的时候直接初始化指针指向地址上的值
	int* numptr = new int(200);
	std::cout << *numptr << std::endl;
	delete numptr;
}
