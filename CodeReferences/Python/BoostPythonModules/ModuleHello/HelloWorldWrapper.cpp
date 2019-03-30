#include <boost/python.hpp>
#include "HelloWorld.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(ModuleHello)
{
	class_<HelloWorld>("HelloWorld")
		.def(init<std::string>())
		.def("sayHello", &HelloWorld::sayHello)
		.def("setMsg", &HelloWorld::setMsg)
		.def("getMsg", &HelloWorld::getMsg)
		;
}