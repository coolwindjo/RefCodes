#include <iostream>

struct BM	
{
	BM()  { std::cout << "BM()" << std::endl; }
	~BM() { std::cout << "~BM()" << std::endl; }
};
struct DM
{
	DM() { std::cout << "DM()" << std::endl; }
	~DM() { std::cout << "~DM()" << std::endl; }
};
struct Base
{
	BM bm;
	Base()		// Base(): bm()  
	{
		std::cout << "Base()" << std::endl; 
	}
	~Base() { std::cout << "~Base()" << std::endl; }
};
struct Derived : public Base
{
	DM dm;
	Derived()  	// Derived(): Base(), dm()
	{
		std::cout << "Derived()" << std::endl; 
	}
	~Derived() { std::cout << "~Derived()" << std::endl; }
};

// Constructor calling sequence
// 1. Base class's Member constructors
// 2. Base class constructor
// 3. Derived class's Member constructors
// 4. Derived class constructor
int main()
{
	Derived d;
}
