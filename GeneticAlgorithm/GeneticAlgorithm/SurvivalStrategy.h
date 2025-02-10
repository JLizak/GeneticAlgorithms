#pragma once

#include <vector>
#include "Individual.h"

namespace GA {
	class SurvivalStrategy {
	public:
		virtual vector<Individual> selectSurvivors(vector<Individual> population, vector<Individual> offspring) = 0;

		virtual ~SurvivalStrategy() = default;
	};
}