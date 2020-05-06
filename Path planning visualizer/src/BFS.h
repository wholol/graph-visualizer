#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Grid.h"
#include <deque>

class BFS : public Algorithm {

public:
	BFS(Graph &graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow) override;
	void constructPath(Grid& grid) override;

private:
	Graph &graph;
	sf::Text text;
	sf::Font font;
	Location srcpos;
	Location targetpos;
	std::deque<node*> deque;
	bool targetreached = false;
};