class Customer {
public:
	string GetName();
	void SetName(string name);
private:
	string name_;
};
class Site {
private:
	Customer* customer_;
};
