//#include "IslandsGA.h"
//#include <iostream>
//#include <random>
//#include "TournamentSelection.h"
//#include "UniformCrossover.h"
//#include "MutationStrategy.h"
//#include "Island.h"
//#include "AdaptiveMutation.h"
//
//
//using namespace GA;
//
//IslandsGA::IslandsGA(SmartPointer<Evaluator> evaluator, mt19937 randomEngine,
//	GeneticOperators GOperators, IslandsGAparameters GParams)
//	: GeneticAlgorithm(evaluator, randomEngine, GOperators, GParams) {
//
//}
//
//void IslandsGA::initialize() {
//
//	initializeIslands();
//}
//
//void IslandsGA::runIteration() {
//	generationCount++;
//	vector<thread> threads;
//
//	for (auto& island : islands) {
//		threads.emplace_back([&island]() {
//			island.runIteration();
//			});
//	}
//
//	for (auto& t : threads) {
//		t.join();
//	}
//
//	if (generationCount % parameters.migrationInterval == 0) {
//		migrate();
//	}
//
//	updateBestIndividual();
//}
//
//void IslandsGA::updateBestIndividual() {
//	for (auto& island : islands) {
//		Individual best = island.getBestIndividual();
//		if (best.fitness < bestFitness) {
//			bestFitness = best.fitness;
//			bestIndividual = best;
//		}
//	}
//}
//
//void IslandsGA::migrate() {
//
//	std::vector<Individual> migrationPool;
//	for (auto& island : islands) {
//		std::vector<Individual> topIndividuals = island.vGetTopIndividuals(migrationSize);
//		migrationPool.insert(migrationPool.end(), topIndividuals.begin(), topIndividuals.end());
//	}
//
//	std::vector<Individual> strongMigrants;
//	for (auto& migrant : migrationPool) {
//		if (migrant.fitness < bestFitness) {
//			strongMigrants.push_back(migrant);
//		}
//	}
//
//	
//	std::shuffle(strongMigrants.begin(), strongMigrants.end(), randomEngine);
//
//	for (auto& island : islands) {
//		island.vReceiveMigrants(strongMigrants);
//	}
//}
//
//void IslandsGA::initializeIslands() {
//	islands.clear();
//
//	for (int i = 0; i < numIslands; i++) {
//
//
//		SmartPointer<SelectionStrategy> islandSelection = SmartPointer<SelectionStrategy>(
//			new TournamentSelection(TOURNAMNET_SIZE, randomEngine));
//
//		SmartPointer<CrossoverStrategy> islandCrossover = SmartPointer<CrossoverStrategy>(
//			new UniformCrossover(randomEngine, evaluator));
//
//		SmartPointer<MutationStrategy> islandMutation = SmartPointer<MutationStrategy>(
//			new AdaptiveMutation(evaluator->iGetLowerBound(),
//				evaluator->iGetUpperBound(), randomEngine));
//
//
//
//		std::mt19937 islandRng(randomEngine());
//		islands.emplace_back(i, islandPopulationSize, evaluator, islandSelection, islandCrossover, islandMutation, islandRng);
//
//	}
//
//	shuffle(population.begin(), population.end(), randomEngine);
//
//	auto it = population.begin();
//	for (auto& island : islands) {
//		size_t remaining = std::distance(it, population.end());
//		size_t sizeToAssign = std::min(remaining, static_cast<size_t>(islandPopulationSize));
//
//		std::vector<Individual> islandPopulation(it, it + sizeToAssign);
//		island.vInitialize(islandPopulation);
//		it += sizeToAssign;
//	}
//
//	updateBestIndividual();
//}
//
//
