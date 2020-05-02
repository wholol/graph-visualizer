#pragma once
#include "Graph.h"
#include "Grid.h"
#include <queue>
#include <stack>
#include <memory>
#include <list>

class DFS {

public:
	DFS(Graph graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos,const std::vector<Location>& obstacles,Grid &grid,sf::RenderWindow& createwindow);
	void drawpath(Grid& grid);

private:
	Graph graph;
	Location srcpos;
	Location targetpos;
	std::stack<Location> stack;
	bool targetreached = false;
	



};