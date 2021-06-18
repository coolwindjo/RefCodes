#include "sample1.h"

bool TempRange::Includes(const TempRange &range)
{
	return GetLow() <= range.GetLow() && GetHigh() >= range.GetHigh();
}

bool HeatingPlan::WithinRange(TempRange room_range)
{
	return range.Includes(room_range);
}

bool Room::WithinPlan(HeatingPlan plan)
{
	return plan.WithinRange(DaysTempRange());
}

TempRange Room::DaysTempRange()
{
	return range;
}
