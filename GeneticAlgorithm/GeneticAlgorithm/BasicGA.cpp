#include "BasicGA.h"
#include <iostream>
using namespace GA;

BasicGA::BasicGA(shared_ptr<Evaluator> evaluator, mt19937 randomEngine,
	GeneticOperators GOperators, GeneticAlgorithmParameters GParams) :
	GeneticAlgorithm(evaluator, randomEngine, GOperators, GParams) {
}

void BasicGA::runIteration() {
	
	vector<Individual> parents = measureAndDoFunction<vector<Individual>>(
		[this]() { return select(); }, "Selection"
	);

	vector<Individual> offspring = measureAndDoFunction<vector<Individual>>(
		[this, &parents]() { return performCrossover(parents); }, "Crossover"
	);

	measureAndDoFunction(
		[this]() {return performMutation(); }, "Mutation"
	);

	measureAndDoFunction(
		[this, &offspring]() { return population->updatePopulation(offspring); }, "Survival"
	);
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

vector<Individual> BasicGA::performCrossover(vector<Individual> parents) {
	vector<Individual> offspring;

	for (size_t i = 0; i < parents.size(); i += 2) {
		Individual parent1 = parents[i];
		Individual parent2 = (i + 1 < parents.size()) ? parents[i + 1] : parents[i];

		vector<Individual> children = cross(parent1, parent2);

		offspring.insert(offspring.end(), children.begin(), children.end());
	}

	return offspring;
}

void BasicGA::performMutation() {
	for (auto& individual : population->getPopulation()) {
		mutate(individual);
	}
}