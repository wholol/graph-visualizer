#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Grid.h"
#include <stack>

class DFS : public Algorithm {

public:
	DFS(Graph& graph);
	virtual void SolveAlgorithm(const Location& srcpos, const Location& targetpos,const std::vector<Location>& obstacles,Grid &grid,sf::RenderWindow& createwindow) override;
	virtual void constructPath(Grid& grid) override;

private:
	Graph& graph;
	Location srcpos;
	Location targetpos;
	sf::Text text;
	sf::Font font;
	std::stack<node*> stack;
	bool targetreached = false;
};
