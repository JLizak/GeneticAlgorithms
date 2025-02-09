#ifndef ISLAND_H
#define ISLAND_H

#include "Individual.h"
#include "SelectionStrategy.h"
#include "CrossoverStrategy.h"
#include "Evaluator.h"
#include <vector>
#include <random>
#include "GroupingEvaluator.h"
#include "MutationStrategy.h"
#include <future>
#include "SmartPtr.h"
#include "GeneticAlgorithm.h"

namespace GA {
	class Island : GeneticAlgorithm {
	public:
		Island(SmartPointer<Evaluator> evaluator, mt19937 randomEngine,
			GeneticOperators GOperators, GeneticAlgorithmParameters GParams, SmartPointer<PopulationPool> population);

		void initialize() override;
		void runIteration() override;

		void receiveMigrants(const std::vector<Individual>& migrants);

	private:
		int islandID;
	};

}



#endif // ISLAND_H
