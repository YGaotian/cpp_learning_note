#include "header_learning.h"

//DogTypeAnimal
Canine::Canine()
{
	std::cout << "A canine is created." << std::endl;
}
Canine::Canine(char food[10])
{
	strcpy_s(likedFood, food);
	std::cout << "A canine is created." << std::endl;
}
void Canine::move()
{
	std::cout << "The canine moves randomly" << std::endl;
}
void Canine::move(int step)
{
	if (step == 0)
		std::cout << "The canine doesn't move" << std::endl;
	else if (step == 1)
		std::cout << "The canine moves " << step << " step forward" << std::endl;
	else if (step == -1)
		std::cout << "The canine moves " << step << "step back" << std::endl;
	else
		std::cout << "步子不要迈得太大，一步一步走，我还不是狗" << std::endl;
}
void Canine::bark()
{
	std::cout << "Owww!" << std::endl;
}
void Canine::talk()
{
	std::cout << "I have " << ears << " ears, " << tails << " tail and " << legs << " legs." << std::endl;
	std::cout << "My favourite food is " << likedFood << std::endl;
}
Canine::~Canine()
{
	std::cout << "Canine destroyed." << std::endl;
}

//Dog
Dog::Dog()
{
	std::cout << "A dog is created." << std::endl;
}
Dog::Dog(char food[10])
{
	strcpy_s(likedFood, food);
	std::cout << "A dog is created." << std::endl;
}
void Dog::move(int steps)
{
	if (steps > 1)
		std::cout << "The dog moves " << steps << " steps forward" << std::endl;
	else if (steps == 0)
		std::cout << "The dog doesn't move" << std::endl;
	else if (steps < -1)
		std::cout << "The dog moves " << steps << "steps back" << std::endl;
	else if (steps == 1)
		std::cout << "The dog moves " << steps << " step forward" << std::endl;
	else
		std::cout << "The dog moves " << steps << "step back" << std::endl;
}
void Dog::talk(char o[50])
{
	strcpy_s(owner, o);
	std::cout << "My owner is " << owner << std::endl;
}
void Dog::testfunc()
{
	std::cout << "Dog test" << std::endl;
}
Dog::~Dog()
{
	std::cout << "Dog destroyed." << std::endl;
}

void class_inheritance()
{
	char food[20] = "rice";
	Canine dta(food);
	dta.move();
	dta.move(1);
	dta.move(-3);
	dta.bark();
	dta.talk();

	//子类对象实例化的时候，会先调用父类的默认构造函数
	//类的构造函数都要自己实现自己的，子类的构造不能单纯使用父类的构造函数完成
	Dog dog1;
	//如果子类想调用父类方法，子类中没有与父类同名的方法时，可以直接调用
	dog1.bark();
	//如果子类想调用父类方法，子类中有了与父类同名的方法，则在调用的时候要写成 子类名.父类名::方法()
	dog1.Canine::talk();
	char name[50] = "T.H.";
	//子类可以重载父类的方法，写一个有着与父类相同方法名但参数类型或返回类型不同的方法
	//因为这个方法是属于子类的，所以调用的时候很自然，不用加父类的作用域
	dog1.talk(name);
	Dog dog2(food);
	dog2.Canine::talk();
	dog2.talk(name);
	//但是一旦子类重写了父类的方法，将父类中的某一个方法自己重新实现了一遍(注意不是重载)，那么子类再调用这个方法的时候，调用的是自己版本的方法
	dog2.move(22);
	//不过这时候父类的其他同名但参数类型不同的方法，子类就不能调用了，产生了函数遮蔽，如果想调用，可以在头文件中子类的类定义里使用using关键字，使父类的方法以子类的函数重载的方式在子类中可见
	dog2.move();//在子类的类定义中写了using DogTypeAnimal::move;所以现在可以通过子类调用move()，即dog2.move();
	//其实上述的两条规则都可以用显式的写法来规避，以通过子类调用父类的方法，这种显式的写法使得我们不需要在类定义的时候写using
	dog2.Canine::move();
	dog2.Canine::move(1);
}