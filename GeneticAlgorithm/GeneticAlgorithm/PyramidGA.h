#pragma once

#include "GeneticAlgorithm.h"
#include "PopulationPool.h"
#include <memory>
#include <vector>

namespace GA {

    class PyramidGA : public GeneticAlgorithm
    {
    public:
        PyramidGA(int numberOfLevels,
            shared_ptr<Evaluator> evaluator,
            std::mt19937 randomEngine,
            GeneticOperators GOperators,
            GeneticAlgorithmParameters GParams);

        
        void initialize() override;

        void runIteration() override;

      
        double getBestFitness() override;
        vector<int> getBestSolution() override;

    private:
        int levels;

       
        vector<shared_ptr<PopulationPool>> pyramidPopulations;

       
        void runOneLevelIteration(shared_ptr<PopulationPool> pop);

      
        void migrateDown(int fromLevel, int toLevel);

    };

} // namespace GA
