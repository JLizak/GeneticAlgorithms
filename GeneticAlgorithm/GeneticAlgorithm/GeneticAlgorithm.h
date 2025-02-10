#pragma once

#include "IGeneticAlgorithm.h"
#include "Individual.h"
#include "Evaluator.h"

#include "SelectionStrategy.h"
#include "CrossoverStrategy.h"
#include "MutationStrategy.h"
#include "IIndividualFactory.h"
#include "PopulationPool.h"

#include <future>
#include <random>

using namespace std;

namespace GA {

	struct GeneticAlgorithmParameters {
		int populationSize;
		int mutationRate;
		int crossoverRate;
	};

	struct GeneticOperators {
		shared_ptr<SelectionStrategy> selection;
		shared_ptr<CrossoverStrategy> crossover;
		shared_ptr<MutationStrategy> mutation;
		shared_ptr<InitializationStrategy> initialization;
		shared_ptr<SurvivalStrategy> survival;
	};


	class GeneticAlgorithm : public IGeneticAlgorithm {
	protected:
		mt19937 randomEngine;
		int generationCount;
		shared_ptr<Evaluator> evaluator;
		shared_ptr<PopulationPool> population;
		GeneticAlgorithmParameters parameters;
		GeneticOperators operators;

	public:
		GeneticAlgorithm(shared_ptr<Evaluator> evaluator, mt19937 randomEngine,
			GeneticOperators GOperators, GeneticAlgorithmParameters GParams);

		~GeneticAlgorithm() override;

		virtual void runIteration() = 0;
		virtual void initialize() = 0;
		
		vector<Individual> select() override;
		vector<Individual> cross(Individual& parent1, Individual& parent2) override;
		void mutate(Individual& individual) override;

		double getBestFitness() { return population->getBestFitness(); }
	};
}