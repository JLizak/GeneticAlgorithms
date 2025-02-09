//#pragma once
//
//#include "GeneticAlgorithm.h"
//#include "Island.h"
//
//namespace GA {
//
//	struct IslandsGAparameters : GeneticAlgorithmParameters {
//		int numIslands;
//		int migrationInterval;
//		int migrationSize;
//		int islandPopulationSize;
//	};
//
//
//	class IslandsGA : public GeneticAlgorithm
//	{
//	public:
//		IslandsGA(SmartPointer<Evaluator> evaluator, mt19937 randomEngine,
//			GeneticOperators GOperators, IslandsGAparameters GParams);
//
//		void runIteration() override;
//		void initialize() override;
//		
//	private:
//		int TOURNAMNET_SIZE;
//		vector<Island> islands;
//		IslandsGAparameters parameters;
//
//		void migrate();
//		void initializeIslands();
//	};
//}
//
//
