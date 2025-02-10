#ifndef GROUPING_EVALUATOR_H
#define GROUPING_EVALUATOR_H

#include "Point.h"

#include <vector>

using namespace std;

namespace GA
{
	class CGroupingEvaluator
	{
	public:
		CGroupingEvaluator(int iNumberOfGroups, const vector<CPoint>& vPoints);

		double dEvaluate(const int* piSolution) const;
		double dEvaluate(const vector<int>* pvSolution) const;
		double dEvaluate(const vector<int>& vSolution) const;

		const vector<CPoint>& vGetPoints() const { return v_points; }

		int iGetNumberOfPoints() const { return (int)v_points.size(); };

		int iGetLowerBound() const { return 1; };
		int iGetUpperBound() const { return i_number_of_groups; }

	private:
		const double d_WRONG_VALUE = -1;

		int i_number_of_groups;
		vector<CPoint> v_points;
	};
}

#endif