#include <string>
#include "sample1.h"

using namespace std;

int Score::SetScore(string name, int wins, int losses)
{
	name_ = name;
	wins_ = wins;
	losses_ = losses;

	return wins + losses;
}
