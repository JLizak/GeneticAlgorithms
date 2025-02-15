#pragma once
#include "GeneticAlgorithm.h"
#include "Island.h"
#include <vector>

namespace GA {
    class IslandGA : public GeneticAlgorithm {
    private:
        vector<Island> islands;
        int migrationInterval;
        int migrationSize;
        mt19937 randomEngine;

    public:
        IslandGA(int numIslands, int migrationInterval, int migrationSize,
            shared_ptr<Evaluator> evaluator, mt19937 randomEngine,
            GeneticOperators operators, GeneticAlgorithmParameters params);

        void runIteration() override;
        void initialize() override;
        void migrate();
        vector<int> getBestSolution() override;
        double getBestFitness() override;
    };
}
