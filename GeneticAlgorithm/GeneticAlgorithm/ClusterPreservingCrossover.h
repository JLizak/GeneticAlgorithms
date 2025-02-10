#ifndef CLUSTERPRESERVINGCROSSOVER_H
#define CLUSTERPRESERVINGCROSSOVER_H

#include "CrossoverStrategy.h"
#include <random>


namespace GA {
    class ClusterPreservingCrossover : public CrossoverStrategy {
    public:
        ClusterPreservingCrossover(mt19937 randomEngine, Evaluator& evaluator) : c_random_engine(randomEngine), evaluator(evaluator) {}

        vector<Individual> cross(Individual& parent1, Individual& parent2) {
            vector<int> child1Chromosome;
            vector<int> child2Chromosome;

            std::uniform_int_distribution<int> clusterDist(1, evaluator.iGetUpperBound());
            int clusterToSwap = clusterDist(c_random_engine);


            for (size_t i = 0; i < child1Chromosome.size(); i++) {
                if (parent1.getGene(i) == clusterToSwap) {
                    std::swap(child1Chromosome[i], child2Chromosome[i]);  // Swap full schema
                }
            }

            double fitness1 = evaluator.dEvaluate(child1Chromosome);
            double fitness2 = evaluator.dEvaluate(child2Chromosome);

            return {
                Individual(move(child1Chromosome), fitness1),
                Individual(move(child2Chromosome), fitness2)
            };
        }


    private:
        mt19937 c_random_engine;
        Evaluator& evaluator;

    };
}

#endif // !CLUSTERPRESERVINGCROSSOVER_H

