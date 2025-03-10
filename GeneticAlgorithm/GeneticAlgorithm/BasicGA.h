#pragma once

#include "GeneticAlgorithm.h"

namespace GA {
	class BasicGA : public GeneticAlgorithm {
	private:
		
	public:
		BasicGA(shared_ptr<Evaluator> evaluator, mt19937 randomEngine,
			GeneticOperators GOperators, GeneticAlgorithmParameters GParams);
		
		void runIteration() override;

		void initialize() override;

		bool isOffspring(Individual individual, vector<Individual> offspring);

		vector<Individual> performCrossover(vector<Individual> parents);
		void performMutation();
	};
}