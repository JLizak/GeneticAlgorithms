#pragma once

#include "GeneticAlgorithm.h"

namespace GA {
	class BasicGA : public GeneticAlgorithm {
	private:
		
	public:
		BasicGA(SmartPointer<Evaluator> evaluator, mt19937 randomEngine,
			GeneticOperators GOperators, GeneticAlgorithmParameters GParams);
		
		void runIteration() override;

		void initialize() override;

		bool isOffspring(Individual individual, vector<Individual> offspring);
	};
}