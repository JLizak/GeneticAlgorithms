#ifndef UNIFORMCROSSOVER
#define UNIFORMCROSSOVER

#include "CrossoverStrategy.h"
#include <random>

namespace GA {
	class UniformCrossover : public CrossoverStrategy {
	public:
		UniformCrossover(mt19937 randomEngine, shared_ptr<Evaluator> evaluator) : evaluator(evaluator) {
            this->c_random_engine = mt19937(randomEngine);
        }

        vector<Individual> cross(Individual& parent1, Individual& parent2) {
            int chromosomeSize = parent1.getChromosomeSize();

            vector<int> child1Chromosome;
            vector<int> child2Chromosome;
            child1Chromosome.reserve(chromosomeSize);
            child2Chromosome.reserve(chromosomeSize);

            uniform_int_distribution<int> binaryDist(0, 1);

            for (int i = 0; i < chromosomeSize; i++) {

                int gene1 = parent1.getGene(i);
                int gene2 = parent2.getGene(i);

                if (binaryDist(c_random_engine) == 0) {
                    child1Chromosome.push_back(gene1);
                    child2Chromosome.push_back(gene2);
                }
                else {
                    child1Chromosome.push_back(gene2);
                    child2Chromosome.push_back(gene1);
                }
            }

            double fitness1 = evaluator->dEvaluate(child1Chromosome);
            double fitness2 = evaluator->dEvaluate(child2Chromosome);

            return {
                Individual(move(child1Chromosome), fitness1),
                Individual(move(child2Chromosome), fitness2)
            };
        }


	private:
		mt19937 c_random_engine;
        shared_ptr<Evaluator> evaluator;
	};
}

#endif // !UNIFORMCROSSOVER

