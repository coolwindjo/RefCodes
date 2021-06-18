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
}
