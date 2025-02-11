#ifndef EvolutionSimulator_H
#define EvolutionSimulator_H

#include "Individual.h"
#include "Evaluator.h"
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "TournamentSelection.h"
#include "UniformCrossover.h"
#include "MutationStrategy.h"
#include "AdaptiveMutation.h"
#include "RandomResettingMutation.h"
#include <thread>
#include "GeneticAlgorithm.h"
#include "ElitismSurvival.h"
#include "BasicGA.h"
#include "IslandGA.h"

using namespace std;

namespace GA
{
	class CEvolutionSimulator
	{
	public:
		

		CEvolutionSimulator(Evaluator& cEvaluator);
		shared_ptr<IslandGA> islandGA;
		void vInitialize();
		void vRunIteration();

		vector<int>* pvGetCurrentBest() { return &v_current_best; }

	private:
		mt19937 c_random_engine;
	    Evaluator& c_evaluator; 
		double d_current_best_fitness;
		vector<int> v_current_best;

		shared_ptr<Evaluator> evaluator;

		shared_ptr<SelectionStrategy> selection;
		shared_ptr<CrossoverStrategy> crossover;
		shared_ptr<MutationStrategy> mutation;
		shared_ptr<InitializationStrategy> initialization;
		shared_ptr<SurvivalStrategy> survival;

		GeneticAlgorithmParameters params;
		GeneticOperators operators;


		GeneticAlgorithm* geneticAlgorithm;
		
	};
}

#endif