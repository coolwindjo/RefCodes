#ifndef HELLOWORLD_H_
#define HELLOWORLD_H_

#include <string>

class HelloWorld
{
public:
	HelloWorld() : m_Msg("World") {}
	HelloWorld(std::string msg) : m_Msg(msg) {}
	~HelloWorld() {}

	void sayHello(void);
	void setMsg(std::string msg);
	std::string getMsg(void);

private:
	std::string m_Msg;
};

#endif