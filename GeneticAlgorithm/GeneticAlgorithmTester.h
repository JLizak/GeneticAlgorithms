#pragma once

#include "GeneticAlgorithm.h"
#include <vector>

using namespace std;

namespace GA {
	class GeneticAlgorithmTester
	{
	public:
		GeneticAlgorithmTester(GeneticAlgorithm geneticAlgorithm);
		void runTest();
		void getBestCombination();
		
	private:
		GeneticAlgorithm* geneticAlgorithm;
		double bestFitness;
		vector<int> numIslandsTests;
		vector<int> migrationIntervalTests;
		vector<int> migrationSizeTets;
		vector<int> populationSizeTests;
		vector<int> mutationRateTests;
		vector<int> tournamentSizeTests;
	};
}

