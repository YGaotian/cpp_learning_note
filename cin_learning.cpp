#include "header_learning.h"

void cin_learning()
{
	// cin receives only one word each time
	std::string theWord;
	std::string anotherWord;
	std::cin >> theWord;
	std::cin >> anotherWord;
	std::cout << theWord << anotherWord << std::endl;
}