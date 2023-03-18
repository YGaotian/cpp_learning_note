#include "header_learning.h"

void new_array()
{
	//dynArrayPtr指向的是array的第一个元素的地址，相当于&dynArrayPtr[0]，dynArrayPtr+1就是array第二个元素的地址,相当于&dynArrayPtr[1],若要获取array中的第2个元素内容，则为dynArrayPtr[1]或*(dynArrayPtr+1)
	//&dynArrayPtr则是指针本身的地址了
	int* dynArrayPtr = new int[3];
	dynArrayPtr[0] = 12;
	dynArrayPtr[1] = 130;
	dynArrayPtr[2] = 155;
	std::cout << "dynArrayPtr:" << dynArrayPtr << std::endl;
	std::cout << "*dynArrayPtr:" << *dynArrayPtr << std::endl;
	std::cout << "&(*dynArrayPtr):" << &(*dynArrayPtr) << std::endl;
	std::cout << "*dynArrayPtr+1:" << *dynArrayPtr+1 << std::endl;
	std::cout << "*(dynArrayPtr+1):" << *(dynArrayPtr + 1) << std::endl;
	std::cout << "&dynArrayPtr:" << &dynArrayPtr << std::endl;
	std::cout << "&dynArrayPtr[0]:" << &dynArrayPtr[0] << std::endl;
	std::cout << "&(*(dynArrayPtr+1)):" << &(*(dynArrayPtr+1)) << std::endl;
	std::cout << "&dynArrayPtr[1]:" << &dynArrayPtr[1] << std::endl;
	std::cout << "dynArrayPtr+1:" << dynArrayPtr+1 << std::endl;
	delete [] dynArrayPtr;
}