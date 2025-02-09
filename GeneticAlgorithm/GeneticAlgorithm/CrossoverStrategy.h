#ifndef CROSSOVERSTRATEGY_H
#define CROSSOVERSTRATEGY_H

#include "Individual.h"
#include "Evaluator.h"

namespace GA {
	class CrossoverStrategy {
	public:
		virtual ~CrossoverStrategy() {};
		virtual vector<Individual> cross(Individual& parent1, Individual& parent2) = 0;
	};
}

#endif // !CROSSOVERSTRATEGY_H
