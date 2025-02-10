#include "Evaluator.h"
#include <cmath>
#include "Island.h" 
using namespace GA;

Evaluator::Evaluator(int iNumberOfGroups, const std::vector<CPoint>& vPoints)
    : i_number_of_groups(iNumberOfGroups), v_points(vPoints) {
    vPrecomputeDistances();
}

void Evaluator::vPrecomputeDistances() {
    size_t n = v_points.size();
    vv_distance_cache.resize(n, std::vector<double>(n, -1));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            vv_distance_cache[i][j] = vv_distance_cache[j][i] = v_points[i].dCalculateDistance(v_points[j]);
        }
    }
}

double Evaluator::dCalculateGroupDistance(const std::vector<int>& groupIndices) const {
    double dGroupDistance = 0.0;

    for (size_t i = 0; i < groupIndices.size(); ++i) {
        for (size_t j = i + 1; j < groupIndices.size(); ++j) {
            dGroupDistance += 2.0 * vv_distance_cache[groupIndices[i]][groupIndices[j]];
        }
    }

    return dGroupDistance;
}

double Evaluator::dEvaluate(const std::vector<int>& vSolution) const {
    std::unordered_map<int, std::vector<int>> groups;

    for (size_t i = 0; i < vSolution.size(); ++i) {
        groups[vSolution[i]].push_back(static_cast<int>(i));
    }

    double dTotalFitness = 0.0;

    for (const auto& group : groups) {
        dTotalFitness += dCalculateGroupDistance(group.second);
    }

    return dTotalFitness;
}

double Evaluator::dEvaluatePartial(const std::vector<int>& vSolution, const std::unordered_map<int, std::vector<int>>& changedGroups) {
    double deltaFitness = 0.0;

    for (const auto& group : changedGroups) {
        deltaFitness += dCalculateGroupDistance(group.second);
    }

    return deltaFitness;
}
