#pragma once

#include "GeneticAlgorithm.h"
#include "raylib.h"

using namespace GA;

class GUI {
public:
	GUI(int numberOfClusters, const vector<CPoint>& points);
	void render(vector<int> points);
private:
	vector<Color> colors;
	const vector<CPoint>& points;
};