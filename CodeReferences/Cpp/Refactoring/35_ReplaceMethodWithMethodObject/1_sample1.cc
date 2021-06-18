class Account {
public:
	int delta() const;
	int gamma(int inputVal, int quantity, int yearToDate);
};

class Gamma {
public:
	Gamma(Account* account, int inputVal, int quantity, int yearToDate) {
		_account = account;
		_inputVal = inputVal;
		_quantity = quantity;
		_yearToDate = yearToDate;
	};
	int Compute() {
		_importantValue1 = (_inputVal * _quantity) + _account->delta();
		_importantValue2 = (_inputVal * _yearToDate) + 100;
		if ((_yearToDate - _importantValue1) > 100) {
			_importantValue2 -= 20;
		}
		_importantValue3 = _importantValue2 * 7;
		return _importantValue3 - 2 * _importantValue1;
	}
private:
	const Account* _account;
	int _inputVal;
	int _quantity;
	int _yearToDate;
	int _importantValue1;
	int _importantValue2;
	int _importantValue3;
};

int Account::delta() const {
	return 0.1;
}
int Account::gamma(int inputVal, int quantity, int yearToDate) {
	Gamma gamma(this, inputVal, quantity, yearToDate);
	return gamma.Compute();
}
