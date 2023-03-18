#include "header_learning.h"

void iterator_fundamental()
{
	//vector as an example
	std::vector<int> ivec = { 1, 2, 33, 43, 245 };
	std::vector<int>::iterator ivec_iter = ivec.begin();
	//ivec.begin() returns an iterator object which points to the first item in ivec
	//ivec.end() returns an iterator object which points to the address next to the last item in ivec
	//we can determine if a vector is empty by comparing ivec.begin() with ivec.end()
	if (ivec.begin() == ivec.end())
	{
		std::cout << "ivec is empty" << std::endl;
	}
	else
	{
		std::cout << "ivec is not empty" << std::endl;
		std::cout << *ivec.begin() << std::endl;//we treat an iterator as a pointer and use *iter to access the value 
	}
	//we can use ++iter or --iter
	std::cout << *--ivec.end() << std::endl;
	//we can create a reverse iterator to iterate over the vector in reverse
	std::vector<int>::reverse_iterator ivec_rIter;
	for (ivec_rIter = ivec.rbegin(); ivec_rIter != ivec.rend(); ++ivec_rIter)
	{
		std::cout << *ivec_rIter << std::endl;
		std::cout << "double" << std::endl;
		*ivec_rIter = *ivec_rIter * 2;
		std::cout << *ivec_rIter << std::endl;
	}
	//const_iterator, an iterator that can only read the elements in vectors
	std::vector<int>::const_iterator ivec_cstIter = ivec.begin();
	while (ivec_cstIter != ivec.end())
	{
		//*ivec_cstIter = 10;CANNOT DO
		std::cout << *ivec_cstIter << std::endl;
		++ivec_cstIter;
	}
	//We CANNOT return a const iterator to a general iterator by using cbegin() and cend()
	//std::vector<int>::iterator ivec_iter = ivec.cbegin();   // ERROR!!!
    ///Notice that a const container can't return a non-const iterator, that is, const_vec.begin() will return a const_iterator
    ///                                                                          const_vec.rbegin() will return a reverse_iterator<const_iterator>

	//vec.insert(pos, value) insert a new element at pos
	//vec.clear() clear the whole vector object
	//we can achieve the same goal by using vec.erase() and an iterator
	while (ivec_iter != ivec.end())//only use vec.end(), don't use a variable that stores the vec.end()
	{                              //because a variable won't update its value
		ivec_iter = ivec.erase(ivec_iter);
	}
	//a better way do the same thing
	std::vector<int> ivec2 = { 1, 2, 3, 4, 5 };
	while (!ivec2.empty())
	{
		auto iter = ivec2.begin();
		ivec2.erase(iter);
	}
	std::cout << ivec.size() << "and" << ivec2.size() << std::endl;
}