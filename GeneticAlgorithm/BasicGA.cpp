#include "BasicGA.h"

using namespace GA;

BasicGA::BasicGA(SmartPointer<Evaluator> evaluator, mt19937 randomEngine,
	GeneticOperators GOperators, GeneticAlgorithmParameters GParams) :
	GeneticAlgorithm(evaluator, randomEngine, GOperators, GParams) {
}

void BasicGA::runIteration() {
	vector<Individual> parents = select();
	vector<Individual> offspring;

	for (size_t i = 0; i < parents.size(); i += 2) {
		Individual parent1 = parents[i];
		Individual parent2 = (i + 1 < parents.size()) ? parents[i + 1] : parents[i];

		vector<Individual> children = cross(parent1, parent2);

		offspring.insert(offspring.end(), children.begin(), children.end());
	}

	population->updatePopulation(offspring);

	for (auto& child : population->getPopulation()) {
		if (!isOffspring(child, offspring)) {
			mutate(child);
		}

	}
}

bool BasicGA::isOffspring(Individual individual, vector<Individual> offspring) {
	for (int i = 0; i < offspring.size(); i++) {
		if (offspring[i] == individual) {
			return true;
		}
	}
	return false;
}

void BasicGA::initialize() {
	population->initializePopulation();
}