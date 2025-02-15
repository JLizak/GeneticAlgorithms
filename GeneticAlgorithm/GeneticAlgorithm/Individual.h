#pragma once
#include <vector>
#include <random>

using namespace std;

namespace GA {
	class Individual
	{
	private:
		vector<int> chromosome;
		double fitness;

	public:
		Individual(const vector<int>& chromosome, double fitness);
		Individual();

		bool operator<(const Individual& other) const;
		bool operator== (const Individual& other);
		vector<int> getChromosome();
		void setChromosome(vector<int> chromosome);
		int getChromosomeSize();
		double getFitness() const;
		void setFitness(double fitness);
		int getGene(int index);
		Individual copy();

	};
}