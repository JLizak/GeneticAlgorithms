#pragma once
#include "BasicGA.h"
#include <iostream>

namespace GA {
    struct Island {
        shared_ptr<BasicGA> geneticAlgorithm;
        int id;

        Island(int id, shared_ptr<Evaluator> evaluator, mt19937 randomEngine, GeneticOperators operators, GeneticAlgorithmParameters params)
            : id(id) {
            geneticAlgorithm = make_shared<BasicGA>(evaluator, randomEngine, operators, params);
        }

        void runIteration() {
            cout << "Island " << id << endl;
            geneticAlgorithm->runIteration();
        }

        void initialize() {
            geneticAlgorithm->initialize();
        }

        vector<Individual> getPopulation() {
            return geneticAlgorithm->select();
        }

        double getBestFitness() {
            return geneticAlgorithm->getBestFitness();
        }
    };
}
