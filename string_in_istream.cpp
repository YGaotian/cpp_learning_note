#include "header_learning.h"

void string_in_istream()
{
	//use getline(cin, str), after that, cin.get() is not needed because getline doesn't leave the eof sign in the queue
	//getline()is not a class method from istream, it only works when used with "string" objects
	std::string oneSentence;
	std::getline(std::cin, oneSentence);
	std::cout << "sentence 1 is:" << oneSentence << std::endl;
	//std::cin.get();//NOT NEEDED
	std::string sentenceB;
	std::getline(std::cin, sentenceB);
	std::cout << "sentence 2 is:" << sentenceB << std::endl;
}