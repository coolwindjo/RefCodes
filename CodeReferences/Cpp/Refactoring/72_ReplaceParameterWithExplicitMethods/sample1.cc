#include "sample1.h"

int getEmployeeSw(int type)
{
	switch (type)
	{
	case ENGINEER:
		return VISUALSTUDIO;
	case SALESMAN:
		return EXCEL;
	case MANAGER:
		return POWERPOINT;
	default:
		return NO_DEFINED;
	}
}

int createEmployee(int type)
{
	int employeeSw = getEmployeeSw(type);

	return employeeSw;
}
