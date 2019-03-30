#include <boost\python.hpp>

using namespace boost::python;

class BaseA
{
private:
	int a = 0;
public:
	BaseA() {};
	explicit BaseA(int a) :a(a) {};
	virtual ~BaseA() {};
	virtual int getA() { return a; };
	virtual void setA(int a) { this->a = a; };
};

BOOST_PYTHON_MODULE(ModuleA)
{
	class_<BaseA>("BaseA", init<>())
		.def(init<int>())
		.def("getA", &BaseA::getA)
		.def("setA", &BaseA::setA);
};