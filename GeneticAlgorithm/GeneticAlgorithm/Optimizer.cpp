#include "Optimizer.h"


using namespace GA;

COptimizer::COptimizer(CGroupingEvaluator& cEvaluator)
	: c_evaluator(cEvaluator) {


	d_current_best_fitness = numeric_limits<int>::max();

	random_device rd;
	c_random_engine.seed(rd());

	int POPULATION_SIZE = 800;
	double CROSSOVER_RATE = 0.8;
	double MUTATION_RATE = 0.01;
	int TOURNAMENT_SIZE = 2;
	double ELITE_RATE = 0.01;

	evaluator = SmartPointer<Evaluator>(new Evaluator(c_evaluator.iGetUpperBound(), c_evaluator.vGetPoints()));
	selection = SmartPointer<SelectionStrategy>(new TournamentSelection(TOURNAMENT_SIZE, c_random_engine));
	crossover = SmartPointer<CrossoverStrategy>(new UniformCrossover(c_random_engine, evaluator));
	mutation = SmartPointer<MutationStrategy>(new AdaptiveMutation(cEvaluator.iGetLowerBound(), 
		cEvaluator.iGetUpperBound(), c_random_engine));
	initialization = SmartPointer<InitializationStrategy>(new RandomInitialization(evaluator, c_random_engine));
	survival = SmartPointer<SurvivalStrategy>(new ElitismSurvival(ELITE_RATE, c_random_engine));

	params.populationSize = POPULATION_SIZE;
	params.crossoverRate = CROSSOVER_RATE;
	params.mutationRate = MUTATION_RATE;

	operators.initialization = initialization;
	operators.selection = selection;
	operators.crossover = crossover;
	operators.mutation = mutation;
	operators.survival = survival;

	geneticAlgorithm = new BasicGA(evaluator, c_random_engine, operators, params);
}

void COptimizer::vInitialize()
{
	geneticAlgorithm->initialize();
}

void COptimizer::vRunIteration() {
	geneticAlgorithm->runIteration();
	d_current_best_fitness = geneticAlgorithm->getBestFitness();
	cout << d_current_best_fitness << endl;
}