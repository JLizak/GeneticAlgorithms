#ifndef RANDOMRESETTINGMUTATION_H
#define RANDOMRESETTINGMUTATION_H

#include "MutationStrategy.h"
#include <random>

namespace GA {
	class RandomResettingMutation : public MutationStrategy {
	public:
		RandomResettingMutation(int minGroup, int maxGroup, mt19937 rng)
			: minGroup(minGroup), maxGroup(maxGroup), c_random_engine(rng) {
		}

		void mutate(Individual& individual, double mutationRate) override {
			uniform_real_distribution<double> mutationChance(0, 1);
			uniform_int_distribution<int> groupDist(minGroup, maxGroup);

			for (size_t i = 0; i < individual.getChromosomeSize(); i++) {
				if (mutationChance(c_random_engine) < mutationRate) {
					individual.getChromosome()[i] = groupDist(c_random_engine);
				}
			}
		}

	private:
		int minGroup;
		int maxGroup;
		std::mt19937 c_random_engine;
	};
}

#endif // RANDOMRESETTINGMUTATION_H
