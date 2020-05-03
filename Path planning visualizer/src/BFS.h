#pragma once
#include "Graph.h"
#include "Grid.h"
#include <deque>

class BFS {

public:
	BFS(Graph graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow);
	void drawpath(Grid& grid);

private:
	Graph graph;
	Location srcpos;
	Location targetpos;
	std::deque<Location> deque;
	bool targetreached = false;




};