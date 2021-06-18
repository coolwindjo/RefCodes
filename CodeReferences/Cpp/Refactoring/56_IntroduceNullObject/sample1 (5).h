class Customer {
public:
	string GetName();
	void SetName(string name);
	virtual bool IsNull() { return false; };
private:
	string name_;
};
class NullCustomer : public Customer {
public:
	static NullCustomer* NewNull();
	virtual bool IsNull() { return true; };
};
class Site {
private:
	Customer* customer_;
};
