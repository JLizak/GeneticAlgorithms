#include "Individual.h"

using namespace GA;

Individual::Individual(const vector<int>& chromosome, double fitness) {
	this->chromosome = chromosome;
	this->fitness = fitness;
}

Individual::Individual() {
	this->chromosome = vector<int>(0);
	this->fitness = numeric_limits<double>::max();
}

bool Individual::operator<(const Individual& other) const {
	return fitness < other.fitness;
}

bool Individual::operator==(const Individual& other) {
	if (other.chromosome == chromosome) {
		return true;
	}
	return false;
}

int Individual::getChromosomeSize() {
	return chromosome.size();
}

double Individual::getFitness() {
	return fitness;
}

int Individual::getGene(int index) {
	return chromosome[index];
}

vector<int> Individual::getChromosome() {
	return chromosome;
}

void Individual::setChromosome(vector<int> chromosome) {
	this->chromosome = chromosome;
}

void Individual::setFitness(double fitness) {
	this->fitness = fitness;
}

Individual Individual::copy() {
	return Individual(chromosome, fitness);
}