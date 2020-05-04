#pragma once
#include "Graph.h"
#include "Grid.h"
#include <unordered_set>
#include <list>

class AStar {

public:
	AStar(Graph &graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow);
	void drawpath(Grid& grid, const Location& targetpos);

private:
	Graph graph;
	Location srcpos;
	Location targetpos;
	bool targetreached = false;
	std::list<node*> pq;
	std::unordered_set<node*> openSet;
	double nodedistance(node* a, node* b);
	




};

