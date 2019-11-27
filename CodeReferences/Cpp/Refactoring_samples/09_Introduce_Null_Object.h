#include <string>
using namespace std;

class Customer
{
public:
	virtual ~Customer() {};
	string GetName();
	void SetName(string strName);
	virtual bool IsNull() { return false; };

private:
	string m_strName;

};

class NullCustomer : public Customer
{
public:
	static NullCustomer* NewNull();
	virtual bool IsNull() { return true; };
private:

};

class Site
{
public:
	Site();
	Customer* GetCustomer();
private:
	Customer* m_poCumtomer;
};
