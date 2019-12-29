#include "../../ProbSolvStart.h"

int ComputeNumBags(const int size1, const int size2, const int amount)
{
	// Guard clause
	if (amount < 3 || amount > 5000)
	{
		printf("-1\n");
	}
	else
	{
		int min_sum_a_b = amount;
		for (int num_bs = amount / size2; num_bs >= 0; num_bs--)
		{
			int remainder_b = amount - size2 * num_bs;
			if (remainder_b >= size1)
			{
				int remainder_a = remainder_b % size1;
				if (remainder_a == 0)
				{
					int num_as = remainder_b / size1;
					if (num_as + num_bs < min_sum_a_b)
					{
						min_sum_a_b = num_as + num_bs;
					}
					else
						continue;
				}
				else
					continue;
			}
			else
			{
				if (remainder_b == 0)
				{
					min_sum_a_b = num_bs;
				}
				else
					continue;
			}
		}

		if (min_sum_a_b == amount)
		{
			printf("-1\n");
		}
		else
		{
			printf("%d\n", min_sum_a_b);
		}
	}

	return  0;
}


int main()
{
	size_t numSamples = 0;
	cin >> numSamples;

	
	for(size_t i = 0; i < numSamples; i++)
	{
		/* code */
		int n = 0;
		cin >> n;
		ComputeNumBags(3, 5, n);
	}

	return  0;
}
