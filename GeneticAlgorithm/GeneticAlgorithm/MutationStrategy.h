#ifndef MUTATIONSTRATEGY_H
#define MUTATIONSTRATEGY_H

#include "Individual.h"

namespace GA {
	class MutationStrategy {
	public:
		virtual ~MutationStrategy() {};
		virtual void mutate(Individual& individual, double mutationRate) = 0;
	};
}

#endif // !MUTATIONSTRATEGY_H

