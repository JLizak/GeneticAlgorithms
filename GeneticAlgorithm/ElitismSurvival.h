#pragma once

#include "SurvivalStrategy.h"

namespace GA {
	class ElitismSurvival : public SurvivalStrategy {
	public:
		ElitismSurvival(double eliteRate, mt19937& randomEngine): randomEngine(randomEngine) {
			this->eliteRate = eliteRate;
		}

		vector<Individual> selectSurvivors(vector<Individual> population, vector<Individual> offspring) override {
			vector<Individual> entirePopulation = population;
			vector<Individual> survivors;
			uniform_int_distribution<int> dist(0, offspring.size() - 1);
			entirePopulation.insert(entirePopulation.end(), offspring.begin(), offspring.end());

			sort(entirePopulation.begin(), entirePopulation.end(), [](Individual& a, Individual& b) {
				return a.getFitness() < b.getFitness();
				});

			int eliteSize = eliteRate * population.size();

			for (int i = 0; i < eliteSize; i++) {
				survivors.push_back(entirePopulation[i]);
			}

			for (int i = eliteSize; i < population.size(); i++) {
				survivors.push_back(offspring[dist(randomEngine)]);
			}

			return survivors;
		}
	private:
		double eliteRate;
		mt19937& randomEngine;
	};
}