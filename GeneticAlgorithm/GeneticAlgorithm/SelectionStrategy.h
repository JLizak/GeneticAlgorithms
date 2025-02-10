#ifndef SELECTIONSTRATEGY_H
#define SELECTIONSTRATEGY_H

#include <vector>
#include "Individual.h"
#include "PopulationPool.h"

namespace GA {
    class SelectionStrategy {
    public:
        virtual ~SelectionStrategy() {}
        virtual vector<Individual> select(vector<Individual>& population, int nToSelect) = 0;
    };
}



#endif // SELECTIONSTRATEGY_H
