#include "sample1.h"

bool HeatingPlan::WithinRange(TempRange roomRange, int low, int high)
{
	return roomRange.GetLow() >= range.GetLow() && roomRange.GetHigh() <= range.GetHigh();
}

bool Room::WithinPlan(HeatingPlan plan)
{
	int low = DaysTempRange().GetLow();
	int high = DaysTempRange().GetHigh();

	return plan.WithinRange(DaysTempRange(), low, high);
}

TempRange Room::DaysTempRange()
{
	return range;
}
