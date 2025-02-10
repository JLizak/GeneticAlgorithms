#include "GroupingEvaluator.h"

using namespace GA;

CGroupingEvaluator::CGroupingEvaluator(int iNumberOfGroups, const vector<CPoint>& vPoints)
	: i_number_of_groups(iNumberOfGroups), v_points(vPoints)
{

}

double CGroupingEvaluator::dEvaluate(const int* piSolution) const
{
	bool b_error = !piSolution || v_points.empty();

	double d_distance;
	double d_distance_sum = 0;

	for (size_t i = 0; i + 1 < v_points.size() && !b_error; i++)
	{
		if (piSolution[i] >= iGetLowerBound() && piSolution[i] <= iGetUpperBound())
		{
			for (size_t j = i + 1; j < v_points.size(); j++)
			{
				if (piSolution[i] == piSolution[j])
				{
					d_distance = v_points[i].dCalculateDistance(v_points[j]);

					if (d_distance >= 0)
					{
						d_distance_sum += 2.0 * v_points[i].dCalculateDistance(v_points[j]);
					}
					else
					{
						b_error = true;
					}
				}
			}
		}
		else
		{
			b_error = true;
		}
	}

	if (b_error)
	{
		return d_WRONG_VALUE;
	}

	return d_distance_sum;
}

double CGroupingEvaluator::dEvaluate(const vector<int>* pvSolution) const
{
	if (!pvSolution)
	{
		return d_WRONG_VALUE;
	}

	return dEvaluate(*pvSolution);
}

double CGroupingEvaluator::dEvaluate(const vector<int>& vSolution) const
{
	if (vSolution.size() != v_points.size())
	{
		return d_WRONG_VALUE;
	}

	return dEvaluate(vSolution.data());
}