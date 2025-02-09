#ifndef ADAPTIVEMUTATION_H
#define ADAPTIVEMUTATION_H

#include "MutationStrategy.h"
#include "RandomResettingMutation.h"
#include <random>
#include <iostream>

namespace GA {
	class AdaptiveMutation : public MutationStrategy {
	public:
		AdaptiveMutation(int minGroup, int maxGroup, std::mt19937& rng)
			: minGroup(minGroup), maxGroup(maxGroup), c_random_engine(rng), stagnationCount(0) {
		}

        void mutate(Individual& individual, double mutationRate) override {
            double oldFitness = individual.getFitness();
            double adjustedRate = mutationRate;

			//if (individual.fitness > averageFitness) {
			//	adjustedRate *= 1.5;
			//}
			//else {
			//	adjustedRate *= 0.5;
			//}
			adjustedRate = std::min(adjustedRate, 0.3);

            RandomResettingMutation resetter(minGroup, maxGroup, c_random_engine);
            resetter.mutate(individual, adjustedRate);

            if (individual.getFitness() < oldFitness) {
                stagnationCount = 0;
            }
            else {
                stagnationCount++;
            }
        }

	private:
		int minGroup, maxGroup;
		int stagnationCount;
		std::mt19937& c_random_engine;
	};
}

#endif // ADAPTIVEMUTATION_H
