#pragma once

#include "IIndividualFactory.h"

namespace GA {
	class RandomIndividualFactory : public IIndividualFactory{
	public:

		Individual createIndividual(shared_ptr<Evaluator> evaluator, mt19937& randomEngine) override {
			uniform_int_distribution<int> geneDistribution(evaluator->iGetLowerBound(), evaluator->iGetUpperBound());

			vector<int> chromosome(evaluator->iGetNumberOfPoints());

			for (size_t i = 0; i < chromosome.size(); i++) {
				chromosome[i] = geneDistribution(randomEngine);
			}

			double fitness = evaluator->dEvaluate(chromosome);

			return Individual(chromosome, fitness);
		}
	};
}