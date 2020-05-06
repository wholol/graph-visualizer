#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Grid.h"
#include <unordered_set>
#include <list>

class Dijkstra : public Algorithm {

public:
	Dijkstra(Graph &graph);
	virtual void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow) override;
	virtual void constructPath(Grid& grid) override;

private:
	Graph &graph;
	Location srcpos;
	Location targetpos;
	sf::Text text;
	sf::Font font;
	bool targetreached = false;
	std::list<node*> pq;
	std::unordered_set<node*> openSet;
	double nodedistance(node* a, node* b);
};