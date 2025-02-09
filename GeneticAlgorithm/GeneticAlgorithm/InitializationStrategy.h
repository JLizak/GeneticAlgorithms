#pragma once
#include "Individual.h"

namespace GA {
	class InitializationStrategy {
	public:
		virtual ~InitializationStrategy() = default;

		virtual vector<Individual> initialize(int populationSize) = 0;
		virtual Individual getBestInitialIndividual() = 0;
	};
}