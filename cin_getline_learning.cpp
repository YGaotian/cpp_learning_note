#include "header_learning.h"

void cin_getline_learning()
{
	//cin.getline() receives one whole line each time, cin.get() is not needed even an empty line is entered
	char the_sentence[30];
	char another_sentence[30];
	std::cout << "write the first sentence:";
	std::cin.getline(the_sentence, 30);
	std::cout << "write the second sentence:";
	std::cin.getline(another_sentence, 30);
	std::cout << "first:" << the_sentence << std::endl;
	std::cout << "second:" << another_sentence << std::endl;
}