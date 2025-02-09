#pragma once

#include "Individual.h"
#include "SmartPtr.h"
#include "Evaluator.h"

namespace GA {
	class IIndividualFactory {
	public:
		virtual ~IIndividualFactory() = default;
		virtual Individual createIndividual(SmartPointer<Evaluator> evaluator, mt19937& randomEngine) = 0;
	};
}