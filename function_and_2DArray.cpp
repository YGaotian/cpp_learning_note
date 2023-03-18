#include "header_learning.h"

/*
BAD PROTOTYPE
void receive(int arr[5])
{
	for (int i = 0; i < 5; ++i)
		std::cout << arr[i] << std::endl;
}
应该将数组形参与数组长度分开，作为两个形参，分别传入函数
*/

//2-dimensional array
void _2DArrOutput(int _2DArr[][5], int size)
{
	for (int s = 0; s < size; ++s)
	{
		for (int i = 0; i < 5; ++i)
			std::cout << _2DArr[s][i] << " ";
		std::cout << std::endl;
	}
	
}

void function_2DArray()
{
	int arr[3][5] = {
					{ 1,12,11,123,4 },
					{ 2,4,6,8,10 },
					{ 1,2,3,4,5 }
	};
	_2DArrOutput(arr, 3);
}

