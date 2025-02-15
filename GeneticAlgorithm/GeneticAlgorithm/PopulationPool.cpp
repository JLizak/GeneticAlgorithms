#include "PopulationPool.h"
#include <chrono>
#include <iostream>

using namespace GA;

PopulationPool::PopulationPool(shared_ptr<InitializationStrategy> init, shared_ptr<SurvivalStrategy> surviv, int populationSize, shared_ptr<Evaluator> evaluator,
	mt19937& randomEngine) : randomEngine(randomEngine) {
	population = vector<Individual>(populationSize);
	this->populationSize = populationSize;
	this->evaluator = evaluator;
	bestFitness = numeric_limits<double>::max();
	initialization = init;
	survival = surviv;
}

PopulationPool::PopulationPool(shared_ptr<InitializationStrategy> init, shared_ptr<SurvivalStrategy> surviv, int populationSize, shared_ptr<Evaluator> evaluator,
	mt19937& randomEngine, vector<Individual> pop) : randomEngine(randomEngine) {
	population = vector<Individual>(populationSize);
	this->populationSize = populationSize;
	this->evaluator = evaluator;
	bestFitness = numeric_limits<double>::max();
	initialization = init;
	survival = surviv;
	population = pop;
}

void PopulationPool::initializePopulation() {
	population.clear();

	population = initialization->initialize(populationSize);
	updateBestIndividual(initialization->getBestInitialIndividual());
}

void PopulationPool::updatePopulation(vector<Individual> offspring) {
	auto start = chrono::high_resolution_clock::now();
	population = survival->selectSurvivors(population, offspring);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> elapsed = end - start;
	cout << "Time of survival: " << elapsed.count() << " milliseconds" << endl;

	updateBestIndividual();
}

void PopulationPool::updateBestIndividual() {
	for (int i = 0; i < population.size(); i++) {
		if (population[i] < bestIndividual) {
			updateBestIndividual(population[i]);
		}
	}
}

void PopulationPool::updateBestIndividual(Individual best) {
	bestIndividual = best;
	bestFitness = best.getFitness();
}

shared_ptr<PopulationPool> PopulationPool:: getPopulationFragment(int begin, int end) {
	int newPopulationSize = end - begin;
	vector<Individual> newPopulation(newPopulationSize);

	for (int i = 0; i < newPopulationSize; i++) {
		newPopulation[i] = population[begin + i].copy();
	}

	return shared_ptr<PopulationPool>(new PopulationPool(initialization, survival,
		newPopulationSize, evaluator, randomEngine, newPopulation));
}

void PopulationPool::replaceIndividual(Individual individual, int index) {
	population[index] = individual;
	if (individual.getFitness() > bestFitness) {
		updateBestIndividual(individual);
	}
}