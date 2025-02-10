#pragma once

#include "IGeneticAlgorithm.h"
#include "Individual.h"
#include "Evaluator.h"
#include "SmartPtr.h"
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
		SmartPointer<SelectionStrategy> selection;
		SmartPointer<CrossoverStrategy> crossover;
		SmartPointer<MutationStrategy> mutation;
		SmartPointer<InitializationStrategy> initialization;
		SmartPointer<SurvivalStrategy> survival;
	};


	class GeneticAlgorithm : public IGeneticAlgorithm {
	protected:
		mt19937 randomEngine;
		int generationCount;
		SmartPointer<Evaluator> evaluator;
		SmartPointer<PopulationPool> population;
		GeneticAlgorithmParameters parameters;
		GeneticOperators operators;

	public:
		GeneticAlgorithm(SmartPointer<Evaluator> evaluator, mt19937 randomEngine, 
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