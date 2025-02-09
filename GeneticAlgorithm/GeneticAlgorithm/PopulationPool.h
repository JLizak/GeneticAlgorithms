#pragma once

#include "Individual.h"
#include "RandomInitialization.h"
#include "SurvivalStrategy.h"

namespace GA {
	class PopulationPool {
	private:
		vector<Individual> population;
		int populationSize;

		Individual bestIndividual;
		double bestFitness;

		SmartPointer<InitializationStrategy> initialization;
		SmartPointer<SurvivalStrategy> survival;
		SmartPointer<Evaluator> evaluator;
		mt19937& randomEngine;

		
	public:
		PopulationPool(SmartPointer<InitializationStrategy> init, SmartPointer<SurvivalStrategy> surviv, int populationSize, SmartPointer<Evaluator> evaluator,
		mt19937& randomEngine): randomEngine(randomEngine) {
			population = vector<Individual>(populationSize);
			this->populationSize = populationSize;
			this->evaluator = evaluator;
			bestFitness = numeric_limits<double>::max();
			initialization = init;
			survival = surviv;
		}

		PopulationPool(SmartPointer<InitializationStrategy> init, SmartPointer<SurvivalStrategy> surviv, int populationSize, SmartPointer<Evaluator> evaluator,
			mt19937& randomEngine, vector<Individual> pop) : randomEngine(randomEngine) {
			population = vector<Individual>(populationSize);
			this->populationSize = populationSize;
			this->evaluator = evaluator;
			bestFitness = numeric_limits<double>::max();
			initialization = init;
			survival = surviv;
			population = pop;
		}



		void initializePopulation() {
			population.clear();

			population = initialization->initialize(populationSize);
			updateBestIndividual(initialization->getBestInitialIndividual());
		}

		double getBestFitness() { return population[0].getFitness(); }

		Individual getBestIndividual() { return population[0]; }

		void updatePopulation(vector<Individual> offspring) {
			population = survival->selectSurvivors(population, offspring);
		}

		void updateBestIndividual() {
			for (int i = 0; i < population.size(); i++) {
				if (population[i].getFitness() > bestFitness) {
					updateBestIndividual(population[i]);
				}
			}
		}

		void updateBestIndividual(Individual best) {
			bestIndividual = best;
			bestFitness = best.getFitness();
		}

		vector<Individual>& getPopulation() {
			return population;
		}

		int getPopulationSize() {
			return population.size();
		}

		SmartPointer<PopulationPool> getPopulationFragment(int begin, int end) {
			int newPopulationSize = end - begin;
			vector<Individual> newPopulation(newPopulationSize);

			for (int i = 0; i < newPopulationSize; i++) {
				newPopulation[i] = population[begin + i].copy();
			}

			return SmartPointer<PopulationPool>(new PopulationPool(initialization, survival, 
				newPopulationSize, evaluator, randomEngine, newPopulation));
		}

		void replaceIndividual(Individual individual, int index) {
			population[index] = individual;
			if (individual.getFitness() > bestFitness) {
				updateBestIndividual(individual);
			}
		}
	};
}