#pragma once

#include "Individual.h"
#include "Evaluator.h"

namespace GA {
	class IIndividualFactory {
	public:
		virtual ~IIndividualFactory() = default;
		virtual Individual createIndividual(shared_ptr<Evaluator> evaluator, mt19937& randomEngine) = 0;
	};
}