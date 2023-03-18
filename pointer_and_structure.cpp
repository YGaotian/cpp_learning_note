#include "header_learning.h"

void pointer_and_struct()
{
	struct color
	{
		int red;
		int green;
		int blue;
		std::string c;

	};
	color* myColor = new color;
	std::cout << "Enter to initialize the color:" << std::endl;
	std::cin >> myColor->red;
	std::cin >> myColor->green;
	std::cin >> myColor->blue;
	std::cout << "Your color is: " << "( " << myColor->red << ", " << myColor->green << ", " << myColor->blue << " )" << std::endl;
	delete myColor;//DO NOT FORGET!!!

}