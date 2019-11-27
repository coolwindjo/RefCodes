#include <iostream>
#include <string>
using namespace std;
#include "sample1.h"
string Customer::GetName() { return name_; }
void Customer::SetName(string name) { name_ = name; }

NullCustomer* NullCustomer::NewNull() {
	static NullCustomer null_item;
	return &null_item;
}

Site::Site() : customer_(0) {}

Customer* Site::GetCustomer() {
	return (customer_ == 0) ? NullCustomer::NewNull() : customer_;
}

int main() {
	Customer* customer1 = new Customer();
	customer1->SetName("Refactoring");
	cout << customer1->GetName() << endl;

//	Customer* customer2;
//	cout << customer2->GetName() << endl;

	Customer *customer3 = new Customer();
	delete customer3;
	customer3 = NullCustomer::NewNull();
	cout << customer3->GetName() << endl;

	Customer* customer4 = NullCustomer::NewNull();
	customer4->SetName("Singleton");
	cout << customer4->GetName() << endl;
	Customer* customer5 = NullCustomer::NewNull();
	cout << customer5->GetName() << endl;

	Customer* customer6 = NullCustomer::NewNull();
	cout << customer6->IsNull() << endl;
	Customer* customer7 = new Customer();
	cout << customer7->IsNull() << endl;

	Site site;
	Customer* customer8 = site.GetCustomer();
	string customer_name;
	if (customer8->IsNull()) {
		customer_name = "null name";
	} else {
		customer_name = customer8->GetName();
	}
	cout << customer_name << endl;
}
