#include <iostream>
#include "HelloWorld.h"

void HelloWorld::sayHello(void)
{
	std::cout << "Hello " << m_Msg << std::endl;
}

void HelloWorld::setMsg(std::string msg)
{
	m_Msg = msg;
}

std::string HelloWorld::getMsg(void)
{
	return m_Msg;
}