#include "IslandGA.h"
#include <algorithm>
#include <iostream>

using namespace GA;

IslandGA::IslandGA(int numIslands, int migrationInterval, int migrationSize,
    shared_ptr<Evaluator> evaluator, mt19937 randomEngine, GeneticOperators operators, GeneticAlgorithmParameters params)
    : GeneticAlgorithm(evaluator, randomEngine, operators, params), 
    migrationInterval(migrationInterval),
    migrationSize(migrationSize),
    randomEngine(randomEngine) {

    for (int i = 0; i < numIslands; i++) {
        islands.emplace_back(i, evaluator, randomEngine, operators, params);
    }
}

void IslandGA::initialize() {
    for (auto& island : islands) {
        island.initialize();
    }
}

void IslandGA::runIteration() {
    for (auto& island : islands) {
        island.runIteration();
    }

    static int iterationCount = 0;
    if (++iterationCount % migrationInterval == 0) {
        migrate();
    }
}

void IslandGA::migrate() {
    std::uniform_int_distribution<int> islandDist(0, islands.size() - 1);
    std::uniform_int_distribution<int> individualDist(0, islands[0].getPopulation().size() - 1);

    for (int i = 0; i < islands.size(); i++) {
        int targetIsland = islandDist(randomEngine);
        if (targetIsland == i) continue; 

        vector<Individual> selectedForMigration;
        vector<Individual> population = islands[i].getPopulation();

        for (int j = 0; j < migrationSize; j++) {
            int index = individualDist(randomEngine);
            selectedForMigration.push_back(population[index]);
        }

        for (auto& individual : selectedForMigration) {
            islands[targetIsland].geneticAlgorithm->mutate(individual);
        }
    }

    std::cout << "Migration completed!" << std::endl;
}


double IslandGA::getBestFitness() {
    double bestFitness = numeric_limits<double>::max();
    for (auto& island : islands) {
        bestFitness = std::min(bestFitness, island.getBestFitness());
    }
    return bestFitness;
}

vector<int> IslandGA::getBestSolution() {
    double bestFitness = numeric_limits<double>::max();
    vector<int> bestSolution;
    for (auto& island : islands) {
        if (island.geneticAlgorithm->getBestFitness() < bestFitness) {
            bestFitness = island.geneticAlgorithm->getBestFitness();
            bestSolution = island.geneticAlgorithm->getBestSolution();
        }
    }
    return bestSolution;
}