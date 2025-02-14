#include "EvolutionSimulator.h"

using namespace GA;

CEvolutionSimulator::CEvolutionSimulator(Evaluator& cEvaluator)
    : c_evaluator(cEvaluator) {

    d_current_best_fitness = numeric_limits<double>::max();
    random_device rd;
    c_random_engine.seed(rd());

    int POPULATION_SIZE = 500;
    double CROSSOVER_RATE = 0.99;
    double MUTATION_RATE = 0.001;
    int TOURNAMENT_SIZE = 2;
    double ELITE_RATE = 0.01;
    int NUM_ISLANDS = 5;            // ✅ Ilość wysp
    int MIGRATION_INTERVAL = 10;    // ✅ Częstotliwość migracji
    int MIGRATION_SIZE = 1;         // ✅ Ilość migrujących osobników

    evaluator = make_shared<Evaluator>(cEvaluator.iGetUpperBound(), cEvaluator.vGetPoints());
    selection = make_shared<TournamentSelection>(TOURNAMENT_SIZE, c_random_engine);
    crossover = make_shared<UniformCrossover>(c_random_engine, evaluator);
    mutation = make_shared<AdaptiveMutation>(cEvaluator.iGetLowerBound(), cEvaluator.iGetUpperBound(), c_random_engine);
    initialization = make_shared<RandomInitialization>(evaluator, c_random_engine);
    survival = shared_ptr<SurvivalStrategy>(new ElitismSurvival(ELITE_RATE, c_random_engine));

    params.populationSize = POPULATION_SIZE;
    params.crossoverRate = CROSSOVER_RATE;
    params.mutationRate = MUTATION_RATE;

    operators.initialization = initialization;
    operators.selection = selection;
    operators.crossover = crossover;
    operators.mutation = mutation;
    operators.survival = survival;

    // ✅ Tworzymy IslandGA zamiast BasicGA
    islandGA = make_shared<IslandGA>(NUM_ISLANDS, MIGRATION_INTERVAL, MIGRATION_SIZE, evaluator, c_random_engine, operators, params);
}

void CEvolutionSimulator::vInitialize() {
    islandGA->initialize();  // ✅ Wywołujemy initialize dla IslandGA
}

void CEvolutionSimulator::vRunIteration() {
    islandGA->runIteration();  // ✅ Wywołujemy iterację dla IslandGA
    d_current_best_fitness = islandGA->getBestIslandFitness();  // ✅ Pobieramy najlepszą fitness z wysp
    cout << "Best Fitness: " << d_current_best_fitness << endl;
}
