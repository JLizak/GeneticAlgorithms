#include "GUI.h"

GUI::GUI(int numberOfClusters, const vector<CPoint>& points) : points(points) {
    colors = vector<Color>(numberOfClusters);
	for (int i = 0; i < numberOfClusters; i++) {
        colors[i] = ColorFromHSV((360.0f / numberOfClusters)* i, 0.8f, 0.9f);
	}

    InitWindow(800, 600, "Genetic Algorithm Visualization");
}

void GUI::render(vector<int> solution) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (size_t i = 0; i < points.size(); i++) {

        Color color = colors[solution[i] - 1];
        DrawCircle(
            (points[i].vGetCoordinates()[0]),
            (points[i].vGetCoordinates()[1]),
            5, color);
    }
    EndDrawing();
}