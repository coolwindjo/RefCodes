#include "9_Introduce_Null_Object.h"
#include <iostream>

using namespace std;

string Customer::GetName()
{
	return m_strName;
}

void Customer::SetName(string strName)
{
	m_strName = strName;
}

NullCustomer* NullCustomer::NewNull()
{
	static NullCustomer oNullItem;
	return &oNullItem;
}

Site::Site()
	: m_poCumtomer(0)
{

}

Customer* Site::GetCustomer()
{
	return (m_poCumtomer == 0) ? NullCustomer::NewNull() : m_poCumtomer;
}

int main()
{
	Customer* customer1 = new Customer();
	customer1->SetName("Refactoring");
	cout << customer1->GetName() <<endl;

//	Customer* customer2;
//	cout << customer2->GetName() <<endl;

	Customer* customer3 = new Customer();
	delete customer3;
	customer3 = NullCustomer::NewNull();
	cout << customer3->GetName() <<endl;

	Customer* customer4 = NullCustomer::NewNull();
	customer4->SetName("Singleton");

	cout << customer4->GetName() <<endl;

	Customer* customer5 = NullCustomer::NewNull();
	cout << customer5->GetName() <<endl;

	Customer* customer6 = NullCustomer::NewNull();
	cout << customer6->IsNull() <<endl;

	Customer* customer7 = new Customer();
	cout << customer7->IsNull() <<endl;

	// 해당 Class를 멤버변수로 가지는 클래스에서 사용
	Site site;
	Customer* customer8 = site.GetCustomer();
	string strCustomerName;
	if (customer8->IsNull())
	{
		strCustomerName = "Null Name";
	}
	else
	{
		strCustomerName = customer8->GetName();
	}

	cout << strCustomerName <<endl;


	Customer* customer9 = new Customer();
	customer9->SetName("210");
	if (customer9->IsNull())
	{
		strCustomerName = "Null Name";
	}
	else
	{
		strCustomerName = customer9->GetName();
	}

	cout << strCustomerName <<endl;

	return 0;
}
