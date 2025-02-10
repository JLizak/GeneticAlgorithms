#include "Island.h"
#include <algorithm>
#include <iostream>

using namespace GA;

Island::Island(SmartPointer<Evaluator> evaluator, mt19937 randomEngine,
    GeneticOperators GOperators, GeneticAlgorithmParameters GParams, SmartPointer<PopulationPool> population) :
    GeneticAlgorithm(evaluator, randomEngine, GOperators, GParams) {
    this->population = population;
}


void Island::initialize() {
    population->updateBestIndividual();
}

void Island::runIteration() {

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
        mutate(child);
    }
}


void Island::receiveMigrants(const std::vector<Individual>& migrants) {

    sort(population->getPopulation().begin(), population->getPopulation().end(), [](Individual& a, Individual& b) {
        return a.getFitness() < b.getFitness();
        });

    for (int i = 1; i <= migrants.size(); i ++) {
        population->replaceIndividual(migrants[i], population->getPopulationSize() - i);
    }
}