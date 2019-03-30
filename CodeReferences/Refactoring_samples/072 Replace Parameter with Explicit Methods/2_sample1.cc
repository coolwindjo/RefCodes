#include "sample1.h"

int engineerSw()
{
	return VISUALSTUDIO;
}

int salesmanSw()
{
	return EXCEL;
}

int managerSw()
{
	return POWERPOINT;
}

int noDefined()
{
	return NO_DEFINED;
}

int getEmployeeSw(int type)
{
	switch (type)
	{
	case ENGINEER:
		return engineerSw();
	case SALESMAN:
		return salesmanSw();
	case MANAGER:
		return managerSw();
	default:
		return noDefined();
	}
}

int createEmployee(int type)
{
	int employeeSw = engineerSw();

	return employeeSw;
}
