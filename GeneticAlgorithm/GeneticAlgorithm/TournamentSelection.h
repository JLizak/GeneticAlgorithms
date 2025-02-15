#ifndef TORUNAMENTSELECTION_H
#define TOURNAMENTSELECTION

#include "SelectionStrategy.h"
#include <random>
#include <unordered_map>

namespace GA {
	class TournamentSelection : public SelectionStrategy {
	public:
		TournamentSelection(int tournamentSize, mt19937 randomEngine) : tournamentSize(tournamentSize), c_random_engine(randomEngine) {}

		vector<Individual> select(vector<Individual>& population, int nToSelect) {
			vector<Individual> selected;
			uniform_int_distribution<int> indexDist(0, population.size() - 1);

			for (int i = 0; i < nToSelect; i++) {
				vector<Individual> tournamentPool;

				for (int j = 0; j < tournamentSize; j++) {
					int randomIndex = indexDist(c_random_engine);
					tournamentPool.push_back(population[randomIndex]);
				}

				Individual bestIndividual = tournamentPool[0];

				for (size_t j = 1; j < tournamentPool.size(); j++) {
					if (tournamentPool[j] < bestIndividual) {
						bestIndividual = tournamentPool[j];
					}
				}
				selected.push_back(bestIndividual);
			}

			return selected;
		}

	private:
		int tournamentSize;
		mt19937 c_random_engine;
	};
}

#endif // !TORUNAMENTSELECTION_H