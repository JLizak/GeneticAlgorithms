#include "PyramidGA.h"
#include <algorithm> // for sort

using namespace GA;
using std::vector;
using std::shared_ptr;
using std::uniform_int_distribution;

PyramidGA::PyramidGA(int numberOfLevels,
    shared_ptr<Evaluator> evaluator,
    std::mt19937 randomEngine,
    GeneticOperators GOperators,
    GeneticAlgorithmParameters GParams)
    : GeneticAlgorithm(evaluator, randomEngine, GOperators, GParams),
    levels(numberOfLevels)
{
  

    int basePopSize = parameters.populationSize;
    if (levels <= 0) levels = 1;  

    
    for (int l = 0; l < levels; l++)
    {
       
        double fraction = double(l + 1) / double(levels);
        int popSizeForLevel = std::max(1, int(basePopSize * fraction));

    
        auto pop = std::make_shared<PopulationPool>(
            operators.initialization,
            operators.survival,
            popSizeForLevel,
            evaluator,
            randomEngine
        );
        pyramidPopulations.push_back(pop);
    }
}

void PyramidGA::initialize()
{
    // Initialize each level's population
    for (auto& levelPop : pyramidPopulations)
    {
        levelPop->initializePopulation();
    }
}

void PyramidGA::runIteration()
{
  
    for (int l = 0; l < levels; l++)
    {
        runOneLevelIteration(pyramidPopulations[l]);

       
        if (l < levels - 1)
        {
            migrateDown(l, l + 1);
        }
    }
}

void PyramidGA::runOneLevelIteration(shared_ptr<PopulationPool> pop)
{
   
    vector<Individual>& localPop = pop->getPopulation();
    vector<Individual> parents = operators.selection->select(localPop, localPop.size() / 2);

  
    vector<Individual> offspring;
    for (size_t i = 0; i + 1 < parents.size(); i += 2)
    {
        Individual& p1 = parents[i];
        Individual& p2 = parents[i + 1];
        vector<Individual> children = operators.crossover->cross(p1, p2);
        offspring.insert(offspring.end(), children.begin(), children.end());
    }

  
    for (auto& individual : localPop)
    {
        operators.mutation->mutate(individual, parameters.mutationRate);
    }
    for (auto& child : offspring)
    {
        operators.mutation->mutate(child, parameters.mutationRate);
    }

   
    pop->updatePopulation(offspring);
}

void PyramidGA::migrateDown(int fromLevel, int toLevel)
{
  

   
    vector<Individual> fromPop = pyramidPopulations[fromLevel]->getPopulation();
    std::sort(fromPop.begin(), fromPop.end(),
        [](const Individual& a, const Individual& b) {
            return a.getFitness() < b.getFitness();
        });

   
    int MIGRATE_COUNT = 10;
    MIGRATE_COUNT = std::min(MIGRATE_COUNT, (int)fromPop.size());

    vector<Individual> bestToSend;
    for (int i = 0; i < MIGRATE_COUNT; i++)
    {
        bestToSend.push_back(fromPop[i].copy());
    }

   
    pyramidPopulations[toLevel]->updatePopulation(bestToSend);
}

double PyramidGA::getBestFitness()
{
   
    double best = std::numeric_limits<double>::max();

    for (auto& pop : pyramidPopulations)
    {
        if (pop->getBestFitness() < best)
        {
            best = pop->getBestFitness();
        }
    }
    return best;
}

vector<int> PyramidGA::getBestSolution()
{
   
    double best = std::numeric_limits<double>::max();
    vector<int> bestChromosome;

    for (auto& pop : pyramidPopulations)
    {
        if (pop->getBestFitness() < best)
        {
            best = pop->getBestFitness();
            bestChromosome = pop->getBestIndividual().getChromosome();
        }
    }
    return bestChromosome;
}
