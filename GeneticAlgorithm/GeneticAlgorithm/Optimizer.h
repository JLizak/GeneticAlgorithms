#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "GroupingEvaluator.h"
#include "Individual.h"
#include "Evaluator.h"
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "TournamentSelection.h"
#include "UniformCrossover.h"
#include "MutationStrategy.h"
#include "Island.h"
#include "AdaptiveMutation.h"
#include "RandomResettingMutation.h"
#include <thread>
#include "GeneticAlgorithm.h"
#include "IslandsGA.h"
#include "ElitismSurvival.h"
#include "BasicGA.h"

using namespace std;

namespace GA
{
	class COptimizer
	{
	public:
		

		COptimizer(Evaluator& cEvaluator);

		void vInitialize();
		void vRunIteration();

		vector<int>* pvGetCurrentBest() { return &v_current_best; }

	private:
		mt19937 c_random_engine;
	    Evaluator& c_evaluator; 
		double d_current_best_fitness;
		vector<int> v_current_best;

		SmartPointer<Evaluator> evaluator;

		SmartPointer<SelectionStrategy> selection;
		SmartPointer<CrossoverStrategy> crossover;
		SmartPointer<MutationStrategy> mutation;
		SmartPointer<InitializationStrategy> initialization;
		SmartPointer<SurvivalStrategy> survival;

		GeneticAlgorithmParameters params;
		GeneticOperators operators;


		GeneticAlgorithm* geneticAlgorithm;
		
	};
}

#endif