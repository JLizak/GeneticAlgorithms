#ifndef GAUSSIAN_GROUPING_EVALUATOR_FACTORY_H
#define GAUSSIAN_GROUPING_EVALUATOR_FACTORY_H

#include "GroupingEvaluator.h"
#include "Point.h"

#include <random>
#include <vector>

using namespace std;

namespace GA
{
	class CDimension
	{
	public:
		CDimension(double dMeanMin, double dMeanMax, double dStandardDeviationMin, double dStandardDeviationMax, mt19937& cRandomEngine);

		double dGenerateRandomMean();
		double dGenerateRandomStandardDeviation();

	private:
		const double d_DEFAULT_STANDARD_DEVIATION_VALUE = 1.0;

		uniform_real_distribution<double> c_mean_uniform_distribution;
		uniform_real_distribution<double> c_standard_deviation_uniform_distribution;
		mt19937& c_random_engine;
	};

	class CUnivariateGaussianDistribution
	{
	public:
		CUnivariateGaussianDistribution(double dMean, double dStandardDeviation, mt19937& cRandomEngine);

		double dGenerateRandomNumber();

	private:
		normal_distribution<double> c_normal_distribution;
		mt19937& c_random_engine;
	};

	class CMultivariateGaussianDistribution
	{
	public:
		CMultivariateGaussianDistribution(vector<CDimension>& vDimensions, mt19937& cRandomEngine);

		CPoint cGenerateRandomPoint();

	private:
		vector<CUnivariateGaussianDistribution> v_univariate_gaussian_distributions;
	};

	class CGaussianGroupingEvaluatorFactory
	{
	public:
		CGaussianGroupingEvaluatorFactory(int iNumberOfGroups, int iNumberOfPoints, int iNumberOfMultivariateGaussianDistributions);

		CGaussianGroupingEvaluatorFactory& cAddDimension(double dMeanMin, double dMeanMax, double dStandardDeviationMin, double dStandardDeviationMax);

		CGroupingEvaluator* pcCreateEvaluator();
		CGroupingEvaluator* pcCreateEvaluator(unsigned int iSeed);

	private:
		const int i_NUMBER_OF_GROUPS_MIN_VALUE = 1;
		const int i_NUMBER_OF_POINTS_MIN_VALUE = 1;
		const int i_NUMBER_OF_MULTIVARIATE_GAUSSIAN_DISTRIBUTIONS_MIN_VALUE = 1;

		vector<CMultivariateGaussianDistribution>* pv_create_multivariate_gaussian_distributions();
		vector<CPoint>* pv_create_points(vector<CMultivariateGaussianDistribution>& vMultivariateGaussianDistributions);

		int i_number_of_groups;
		int i_number_of_points;
		int i_number_of_multivariate_gaussian_distributions;

		vector<CDimension> v_dimensions;
		mt19937 c_random_engine;
	};
}

#endif