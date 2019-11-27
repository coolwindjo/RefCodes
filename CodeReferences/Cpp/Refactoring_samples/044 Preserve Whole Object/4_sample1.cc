#include "sample1.h"

bool TempRange::Includes(TempRange arg)
{
	return arg.GetLow() >= GetLow() && arg.GetHigh() <= GetHigh();
}

bool HeatingPlan::WithinRange(TempRange roomRange)
{
	return range.Includes(roomRange);;
}

bool Room::WithinPlan(HeatingPlan plan)
{
	return plan.WithinRange(DaysTempRange());
}

TempRange Room::DaysTempRange()
{
	return range;
}
