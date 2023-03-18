#include "header_learning.h"

void cin_with_string()
{
	//only cin can receive a string object that contains just word
	std::string aWord;
	std::string aSentence;
	std::cout << "aWord is:";
	std::cin >> aWord;
	//std::cin.get(aSentence);//CANNOT DO
	std::cout << "aWord:" << aWord << std::endl;
	std::cout << "aSentence is:";
	std::cin >> aSentence;
	std::cout << "aSentence:" << aSentence << std::endl;
}