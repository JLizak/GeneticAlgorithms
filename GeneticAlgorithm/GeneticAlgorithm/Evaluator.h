#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Point.h"
#include <vector>
#include <unordered_map>

namespace GA
{
    class Evaluator
    {
    public:
        Evaluator(int iNumberOfGroups, const std::vector<CPoint>& vPoints);

        double dEvaluate(const std::vector<int>& vSolution) const;
        double dEvaluatePartial(const std::vector<int>& vSolution, const std::unordered_map<int, std::vector<int>>& changedGroups);

        const std::vector<CPoint>& vGetPoints() const { return v_points; }

        int iGetNumberOfPoints() const { return static_cast<int>(v_points.size()); };
        int iGetLowerBound() const { return 1; };
        int iGetUpperBound() const { return i_number_of_groups; }

    private:
        int i_number_of_groups;
        std::vector<CPoint> v_points;

        std::vector<std::vector<double>> vv_distance_cache; // Cache dla odległości
        void vPrecomputeDistances();
        double dCalculateGroupDistance(const std::vector<int>& groupIndices) const;
    };
}

#endif
