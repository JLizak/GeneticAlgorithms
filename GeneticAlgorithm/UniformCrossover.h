#ifndef UNIFORMCROSSOVER
#define UNIFORMCROSSOVER

#include "CrossoverStrategy.h"
#include <random>
#include "SmartPtr.h"

namespace GA {
	class UniformCrossover : public CrossoverStrategy {
	public:
		UniformCrossover(mt19937 randomEngine, SmartPointer<Evaluator> evaluator) : evaluator(evaluator) {
            this->c_random_engine = mt19937(randomEngine);
        }

        vector<Individual> cross(Individual& parent1, Individual& parent2) {
            vector<int> child1Chromosome;
            vector<int> child2Chromosome;

            uniform_int_distribution<int> binaryDist(0, 1);

            for (int i = 0; i < parent1.getChromosomeSize(); i++) {
                if (binaryDist(c_random_engine) == 0) {
                    child1Chromosome.push_back(parent1.getGene(i));
                    child2Chromosome.push_back(parent2.getGene(i));
                }
                else {
                    child1Chromosome.push_back(parent2.getGene(i));
                    child2Chromosome.push_back(parent1.getGene(i));
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
        SmartPointer<Evaluator> evaluator;
	};
}

#endif // !UNIFORMCROSSOVER

