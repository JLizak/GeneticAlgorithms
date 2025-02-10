#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "Individual.h"

namespace GA {
	class IGeneticAlgorithm {
	public:
		virtual void runIteration() = 0;

		virtual void initialize() = 0;
		virtual vector<Individual>  select() = 0;
		virtual vector<Individual> cross(Individual& parent1, Individual& parent2) = 0;
		virtual void mutate(Individual& individual) = 0;

		virtual ~IGeneticAlgorithm() = default;
	};
}


#endif // !GENETICALGORITHM_H
