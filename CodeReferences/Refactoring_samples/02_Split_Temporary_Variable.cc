#include <algorithm>

double primary_force(15.0);
double mass(5.0);
int delay(3);
double secondary_force(7);

using namespace std;

double GetDistanceTravelled(int time)
{
	double result;
	const double primary_acc = primary_force / mass;
	int primary_time = min(time, delay);
	result = 0.5 * primary_acc * primary_time * primary_time;
	int secondary_time = time - delay;
	if (secondary_time > 0)
	{
		double primary_vel = primary_acc * delay;
		const double secondary_acc = (primary_force + secondary_force) / mass;
		result += primary_vel * secondary_time + 0.5 * secondary_acc * secondary_time * secondary_time;
	}
	return result;
}
