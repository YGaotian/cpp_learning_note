#include "header_learning.h"

Ball::Ball(double radius)
{
	m_ballRadius = radius;
	std::cout << "A ball is created, details: " << m_ballRadius << " cm" << std::endl;
}
Ball::Ball(double radius, char color[10])
{
	m_ballRadius = radius;
	strcpy_s(m_ballColor, color);
	std::cout << "A ball is created, details: " << m_ballRadius << " cm and " << m_ballColor << std::endl;
}
Ball::Ball(const Ball& ball)
{
	m_ballRadius = ball.m_ballRadius;
	strcpy_s(m_ballColor, ball.m_ballColor);
}
Ball::~Ball()
{
	std::cout << "Ball destroyed" << std::endl;
}

Basketball::Basketball(double radius, char color[10], double weight) :Ball(radius, color)			//子类的构造函数初始化列表，对基类的有参构造函数传了参数，只需使用其中一个有参构造函数即可
																									//若类声明中有成员变量未初始化，应使用可初始化所有成员的那一个构造函数
{
	m_basketballRadius = radius;
	strcpy_s(m_basketballColor, color);
	m_basketballWeight = weight;
	std::cout << "A basketball is created, details: " << m_basketballRadius << " cm, " << m_basketballWeight << " g and " << m_basketballColor << std::endl;
}
Basketball::~Basketball()
{
	std::cout << "Basketball destroyed" << std::endl;
}

void more_about_the_inheritance()
{
	//如果我们有一个基类，它只有一个或多个有参构造函数，并且一个子类继承了该基类，会发生什么？
	//答案是，我们无法定义子类的构造函数，除非子类构造函数的定义使用构造函数初始化列表，对父类的构造函数传参
	char col[10] = "red";
	Ball* ball = new Basketball(30, col, 800);
	std::cout << ball->m_ballColor << std::endl;
	Basketball* basketball = dynamic_cast<Basketball*>(ball);
	std::cout << basketball->m_basketballColor << std::endl;
	delete ball;

	//什么是静态类型和动态类型
	//只有基类指针或基类引用，才存在静态类型和动态类型不一样的情况
	//在上述代码中，Ball* ball = new Basketball(30, col, 800);这里的静态类型就是Ball，是在声明的时候基类指针的类型，在编译阶段就已知的类型。
	//动态类型是Basketball，是动态绑定到基类指针上的对象的类型，在程序运行时才能知道具体的类型

	//关于基类与子类对象的拷贝与赋值
	//我们可以对基类的拷贝构造函数中传入一个子类对象
	Basketball newbasketball(30, col, 800);
	Ball newball(newbasketball);			//拷贝构造函数仅拷贝子类对象中的基类部分的成员，其余部分不作处理
	std::cout << newball.m_ballColor << newball.m_ballRadius << std::endl;
}