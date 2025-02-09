#include "GaussianGroupingEvaluatorFactory.h"

using namespace GA;

CDimension::CDimension(double dMeanMin, double dMeanMax, double dStandardDeviationMin, double dStandardDeviationMax, mt19937 &cRandomEngine)
	: c_mean_uniform_distribution(min(dMeanMin, dMeanMax), max(dMeanMin, dMeanMax)), 
	c_standard_deviation_uniform_distribution(min(dStandardDeviationMin, dStandardDeviationMax), max(dStandardDeviationMin, dStandardDeviationMax)),
	c_random_engine(cRandomEngine)
{

}

double CDimension::dGenerateRandomMean()
{
	return c_mean_uniform_distribution(c_random_engine);
}

double CDimension::dGenerateRandomStandardDeviation()
{
	double d_standard_deviation = c_standard_deviation_uniform_distribution(c_random_engine);

	if (d_standard_deviation <= 0)
	{
		d_standard_deviation = d_DEFAULT_STANDARD_DEVIATION_VALUE;
	}

	return d_standard_deviation;
}

CUnivariateGaussianDistribution::CUnivariateGaussianDistribution(double dMean, double dStandardDeviation, mt19937& cRandomEngine)
	: c_normal_distribution(dMean, dStandardDeviation), c_random_engine(cRandomEngine)
{

}

double CUnivariateGaussianDistribution::dGenerateRandomNumber()
{
	return c_normal_distribution(c_random_engine);
}

CMultivariateGaussianDistribution::CMultivariateGaussianDistribution(vector<CDimension>& vDimensions, mt19937& cRandomEngine)
{
	v_univariate_gaussian_distributions.reserve(vDimensions.size());

	for (size_t i = 0; i < vDimensions.size(); i++)
	{
		v_univariate_gaussian_distributions.push_back(CUnivariateGaussianDistribution(vDimensions[i].dGenerateRandomMean(), vDimensions[i].dGenerateRandomStandardDeviation(), cRandomEngine));
	}
}

CPoint CMultivariateGaussianDistribution::cGenerateRandomPoint()
{
	CPoint c_point;

	for (size_t i = 0; i < v_univariate_gaussian_distributions.size(); i++)
	{
		c_point.vAddCoordinate(v_univariate_gaussian_distributions[i].dGenerateRandomNumber());
	}

	return c_point;
}

CGaussianGroupingEvaluatorFactory::CGaussianGroupingEvaluatorFactory(int iNumberOfGroups, int iNumberOfPoints, int iNumberOfMultivariateGaussianDistributions)
	: i_number_of_groups(max(iNumberOfGroups, i_NUMBER_OF_GROUPS_MIN_VALUE)), 
	i_number_of_points(max(iNumberOfPoints, i_NUMBER_OF_GROUPS_MIN_VALUE)), 
	i_number_of_multivariate_gaussian_distributions(max(iNumberOfMultivariateGaussianDistributions, i_NUMBER_OF_MULTIVARIATE_GAUSSIAN_DISTRIBUTIONS_MIN_VALUE))
{

}

CGaussianGroupingEvaluatorFactory& CGaussianGroupingEvaluatorFactory::cAddDimension(double dMeanMin, double dMeanMax, double dStandardDeviationMin, double dStandardDeviationMax)
{
	v_dimensions.push_back(CDimension(dMeanMin, dMeanMax, dStandardDeviationMin, dStandardDeviationMax, c_random_engine));

	return *this;
}

CGroupingEvaluator* CGaussianGroupingEvaluatorFactory::pcCreateEvaluator()
{
	random_device c_seed_generator;

	return pcCreateEvaluator(c_seed_generator());
}

CGroupingEvaluator* CGaussianGroupingEvaluatorFactory::pcCreateEvaluator(unsigned int iSeed)
{
	c_random_engine.seed(iSeed);

	vector<CMultivariateGaussianDistribution>* pv_multivariate_gaussian_distributions = pv_create_multivariate_gaussian_distributions();
	vector<CPoint>* pv_points = pv_create_points(*pv_multivariate_gaussian_distributions);

	CGroupingEvaluator* pc_evaluator = new CGroupingEvaluator(i_number_of_groups, *pv_points);

	delete pv_multivariate_gaussian_distributions;
	delete pv_points;

	return pc_evaluator;
}

vector<CMultivariateGaussianDistribution>* CGaussianGroupingEvaluatorFactory::pv_create_multivariate_gaussian_distributions()
{
	vector<CMultivariateGaussianDistribution>* pv_multivariate_gaussian_distributions = new vector<CMultivariateGaussianDistribution>();

	pv_multivariate_gaussian_distributions->reserve(i_number_of_multivariate_gaussian_distributions);

	for (int i = 0; i < i_number_of_multivariate_gaussian_distributions; i++)
	{
		pv_multivariate_gaussian_distributions->push_back(CMultivariateGaussianDistribution(v_dimensions, c_random_engine));
	}

	return pv_multivariate_gaussian_distributions;
}

vector<CPoint>* CGaussianGroupingEvaluatorFactory::pv_create_points(vector<CMultivariateGaussianDistribution>& vMultivariateGaussianDistributions)
{
	vector<CPoint>* pv_points = new vector<CPoint>();

	pv_points->reserve(i_number_of_points);

	uniform_int_distribution<size_t> c_multivariate_gaussian_selection_uniform_distribution(0, vMultivariateGaussianDistributions.size() - 1);

	for (int i = 0; i < i_number_of_points; i++)
	{
		size_t i_multivariate_gaussian_distribution_index = c_multivariate_gaussian_selection_uniform_distribution(c_random_engine);

		pv_points->push_back(vMultivariateGaussianDistributions[i_multivariate_gaussian_distribution_index].cGenerateRandomPoint());
	}

	return pv_points;
}