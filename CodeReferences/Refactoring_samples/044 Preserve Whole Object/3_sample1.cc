#include "sample1.h"

bool HeatingPlan::WithinRange(TempRange roomRange)
{
	return roomRange.GetLow() >= range.GetLow() && roomRange.GetHigh() <= range.GetHigh();
}

bool Room::WithinPlan(HeatingPlan plan)
{
	return plan.WithinRange(DaysTempRange());
}

TempRange Room::DaysTempRange()
{
	return range;
}
