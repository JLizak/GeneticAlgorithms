#include "GeneticAlgorithm.h"

using namespace GA;


GeneticAlgorithm::~GeneticAlgorithm() {
}

GeneticAlgorithm::GeneticAlgorithm(SmartPointer<Evaluator> evaluator, mt19937 randomEngine,
	GeneticOperators GOperators, GeneticAlgorithmParameters GParams) :
     evaluator(evaluator), randomEngine (randomEngine) {
	operators = GOperators;
	parameters = GParams;
	population = SmartPointer<PopulationPool>(new PopulationPool(operators.initialization, operators.survival,
		parameters.populationSize, evaluator, randomEngine));

}

vector<Individual> GeneticAlgorithm::select() {
	return operators.selection->select(population->getPopulation(), parameters.populationSize / 2);
}

vector<Individual> GeneticAlgorithm::cross(Individual& parent1, Individual& parent2) {
	return operators.crossover->cross(parent1, parent2);
}

void GeneticAlgorithm::mutate(Individual& individual) {
	operators.mutation->mutate(individual, parameters.mutationRate);
}
