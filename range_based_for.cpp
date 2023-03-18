#include "header_learning.h"

void range_based_for_read()
{
	int list[5] = { 1,2,3,4,5 };
	for (int i : list)
	{
		std::cout << i << std::endl;
	}
}

void range_based_for_modify()
{
	double dlist[5] = { .1,.2,.3,.4,.5 };
	//Use typename& to modify all elements from the list one-by-one
	for (auto & dbl : dlist)
	{
		++dbl;
	}
	for (auto e : dlist)
	{
		std::cout << e << std::endl;
	}
	//Don't ever modify the length of an array or any other container inside the range-based-for-loop
	//such as the method: push_back()
}

void range_based_for()
{
	range_based_for_read();
	range_based_for_modify();
}