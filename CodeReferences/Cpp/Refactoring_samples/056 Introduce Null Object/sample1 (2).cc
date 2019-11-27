#include <iostream>
#include <string>
using namespace std;
#include "sample1.h"
string Customer::GetName() { return name_; }
void Customer::SetName(string name) { name_ = name; }
int main() {
	Customer* customer1 = new Customer();
	customer1->SetName("Refactoring");
	cout << customer1->GetName() << endl;

	Customer* customer2;
	cout << customer2->GetName() << endl;
}
