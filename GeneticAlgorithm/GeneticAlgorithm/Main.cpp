#include "GaussianGroupingEvaluatorFactory.h"
#include "EvolutionSimulator.h"
#include "raylib.h"
#include "GUI.h"


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
<<<<<<< Updated upstream
		


=======
>>>>>>> Stashed changes

	Evaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

	CEvolutionSimulator c_evolution_sim(*pc_evaluator);

	c_evolution_sim.vInitialize();
<<<<<<< Updated upstream
	/*GUI gui(pc_evaluator->iGetUpperBound(), pc_evaluator->vGetPoints());*/
=======
	//GUI gui(pc_evaluator->iGetUpperBound(), pc_evaluator->vGetPoints());
>>>>>>> Stashed changes

	for (int i = 0; i < 1000; i++)
	{
		c_evolution_sim.vRunIteration();
<<<<<<< Updated upstream
		/*gui.render(*c_evolution_sim.pvGetCurrentBest());*/
=======
		//gui.render(*c_evolution_sim.pvGetCurrentBest());
>>>>>>> Stashed changes
	}

	delete pc_evaluator;

	return 0;
}






