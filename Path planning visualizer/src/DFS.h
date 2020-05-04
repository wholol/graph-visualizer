#pragma once
#include "Graph.h"
#include "Grid.h"
#include <stack>

class DFS {

public:
	DFS(Graph& graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos,const std::vector<Location>& obstacles,Grid &grid,sf::RenderWindow& createwindow);
	void constructPath(Grid& grid);

private:
	Graph& graph;
	Location srcpos;
	Location targetpos;
	std::stack<node*> stack;
	bool targetreached = false;
};
