#pragma once

#include "InitializationStrategy.h"
#include "SmartPtr.h"
#include "RandomIndividualFactory.h"

namespace GA {
	class RandomInitialization : public InitializationStrategy {
    private:
        SmartPointer<RandomIndividualFactory> individualFactory;
        SmartPointer<Evaluator> evaluator;
        mt19937& randomEngine;
        double bestFitness;
        Individual bestIndividual;

	public:
		RandomInitialization(SmartPointer<Evaluator> evaluator, mt19937& randomEngine) : 
        randomEngine(randomEngine) {
            this->evaluator = evaluator;
            individualFactory = SmartPointer<RandomIndividualFactory>(new RandomIndividualFactory);
            bestFitness = numeric_limits<double>::max();
		}

		vector<Individual> initialize(int populationSize) override {
            vector<Individual> population2;

            for (int i = 0; i < populationSize; i++) {
                Individual newIndividual = individualFactory->createIndividual(evaluator, randomEngine);

                population2.push_back(newIndividual);

                if (newIndividual < bestIndividual) {
                    bestFitness = newIndividual.getFitness();
                    bestIndividual = newIndividual;
                }
            }

            return population2;
		}

        Individual getBestInitialIndividual() override {
            return bestIndividual;
        }
	};
}