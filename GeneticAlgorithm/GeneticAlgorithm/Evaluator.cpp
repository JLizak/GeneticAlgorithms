#include "Evaluator.h"
#include <map>

using namespace GA;

Evaluator::Evaluator(int iNumberOfGroups, const vector<CPoint>& vPoints)
	: i_number_of_groups(iNumberOfGroups), v_points(vPoints) {
}

double Evaluator::dEvaluate(const int* piSolution) const
{
	if (!piSolution || v_points.empty()) return d_WRONG_VALUE;

	map<int, std::vector<size_t> > group_map;

	for (size_t i = 0; i < v_points.size(); i++)
	{
		int group = piSolution[i];

		if (group < iGetLowerBound() || group > iGetUpperBound()) return d_WRONG_VALUE;

		group_map[group].push_back(i);
	}

	double d_distance_sum = 0;

	map<int, vector<size_t> >::iterator it;
	for (it = group_map.begin(); it != group_map.end(); ++it)
	{
		std::vector<size_t>& indices = it->second;
		size_t group_size = indices.size();

		for (size_t i = 0; i < group_size; i++)
		{
			for (size_t j = i + 1; j < group_size; j++)
			{
				double d_distance = v_points[indices[i]].dCalculateDistance(v_points[indices[j]]);
				if (d_distance < 0) return d_WRONG_VALUE;

				d_distance_sum += 2.0 * d_distance;
			}
		}
	}

	return d_distance_sum;
}

double Evaluator::dEvaluate(const vector<int>* pvSolution) const
{
	if (!pvSolution)
	{
		return d_WRONG_VALUE;
	}

	return dEvaluate(*pvSolution);
}

double Evaluator::dEvaluate(const vector<int>& vSolution) const
{
	if (vSolution.size() != v_points.size())
	{
		return d_WRONG_VALUE;
	}

	return dEvaluate(vSolution.data());
}
