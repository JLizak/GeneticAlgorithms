#pragma once

#include "Individual.h"
#include "RandomInitialization.h"
#include "SurvivalStrategy.h"
#include <memory>


namespace GA {
	class PopulationPool {
	private:
		vector<Individual> population;
		int populationSize;

		Individual bestIndividual;
		double bestFitness;

		shared_ptr<InitializationStrategy> initialization;
		shared_ptr<SurvivalStrategy> survival;
		shared_ptr<Evaluator> evaluator;
		mt19937& randomEngine;

		
	public:
		PopulationPool(shared_ptr<InitializationStrategy> init, shared_ptr<SurvivalStrategy> surviv, int populationSize, shared_ptr<Evaluator> evaluator,
			mt19937& randomEngine);

		PopulationPool(shared_ptr<InitializationStrategy> init, shared_ptr<SurvivalStrategy> surviv, int populationSize, shared_ptr<Evaluator> evaluator,
			mt19937& randomEngine, vector<Individual> pop);

		void initializePopulation();

		void updatePopulation(vector<Individual> offspring);

		void updateBestIndividual();

		void updateBestIndividual(Individual best);

		vector<Individual>& getPopulation() {
			return population;
		}

		int getPopulationSize() {
			return population.size();
		}

		Individual getBestIndividual() {
			return bestIndividual;
		}

		double getBestFitness() { return bestFitness; }

		shared_ptr<PopulationPool> getPopulationFragment(int begin, int end);

		void replaceIndividual(Individual individual, int index);
	};
}