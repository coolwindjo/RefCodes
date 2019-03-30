#ifndef _SAMPLE_H_
#define _SAMPLE_H_

using namespace std;

#include <vector>
#include <ctime>

class Entry {
	double value_;
	time_t charge_date_;
public:
	Entry(double value, time_t charge_date);

	time_t GetDate();
	double GetValue();
};

class Account {
public:
	vector<Entry> entries_;

	void Init();
	void PrintDate();
	double GetFlowBetween(time_t start, time_t end);
	static int OneDay();
};

#endif
