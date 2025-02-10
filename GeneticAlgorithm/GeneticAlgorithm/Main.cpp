#include "GaussianGroupingEvaluatorFactory.h"
#include "EvolutionSimulator.h"

using namespace GA;

int main()
{
	CGaussianGroupingEvaluatorFactory c_evaluator_factory(5, 100, 5);

	c_evaluator_factory
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0);

	Evaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

	COptimizer c_optimizer(*pc_evaluator);

	c_optimizer.vInitialize();

	for (int i = 0; i < 1000; i++)
	{
		c_optimizer.vRunIteration();
	}

	delete pc_evaluator;

	return 0;
}
