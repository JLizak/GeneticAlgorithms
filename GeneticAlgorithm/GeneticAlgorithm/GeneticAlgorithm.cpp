#include "GeneticAlgorithm.h"
#include <chrono>
#include <iostream>

using namespace GA;


GeneticAlgorithm::~GeneticAlgorithm() {
}

GeneticAlgorithm::GeneticAlgorithm(shared_ptr<Evaluator> evaluator, mt19937 randomEngine,
	GeneticOperators GOperators, GeneticAlgorithmParameters GParams) :
     evaluator(evaluator), randomEngine (randomEngine) {
	operators = GOperators;
	parameters = GParams;
	population = shared_ptr<PopulationPool>(new PopulationPool(operators.initialization, operators.survival,
		parameters.populationSize, evaluator, randomEngine));

}

vector<Individual> GeneticAlgorithm::select() {
	return operators.selection->select(population->getPopulation(), parameters.populationSize / 2);
}

vector<Individual> GeneticAlgorithm::cross(Individual& parent1, Individual& parent2) {
	vector<Individual> result  =  operators.crossover->cross(parent1, parent2);

	return result;
}

void GeneticAlgorithm::mutate(Individual& individual) {
	operators.mutation->mutate(individual, parameters.mutationRate);
}

