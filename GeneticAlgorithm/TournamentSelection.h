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
				enforceClusterConsistency(bestIndividual);

				selected.push_back(bestIndividual);
			}

			return selected;
		}

	private:
		int tournamentSize;
		mt19937 c_random_engine;

		void enforceClusterConsistency(Individual& individual) {
			unordered_map<int, int> clusterCounts;

			for (int gene : individual.getChromosome()) {
				clusterCounts[gene]++;
			}

			for (size_t i = 0; i < individual.getChromosome().size(); i++) {
				if (clusterCounts[individual.getChromosome()[i]] < 3) {  // Threshold for valid cluster size
					individual.getChromosome()[i] = rand() % tournamentSize;  // Reassign to a new cluster
				}
			}
		}
	};

}

#endif // !TORUNAMENTSELECTION_H
