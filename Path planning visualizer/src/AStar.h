#pragma once
#include "Graph.h"
#include "Grid.h"
#include <queue>


class AStar {

public:
	AStar(Graph graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow);
	void drawpath(Grid& grid);

private:
	Graph graph;
	Location srcpos;
	Location targetpos;
	std::priority_queue<node> pq;
	bool targetreached = false;




};