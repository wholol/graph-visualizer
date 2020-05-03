#pragma once
#include "Graph.h"
#include "Grid.h"
#include <set>
#include <list>

class AStar {

public:
	AStar(Graph graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow);
	//void drawpath(Grid& grid);
	

private:
	Graph graph;
	Location srcpos;
	Location targetpos;
	bool targetreached = false;
	std::list<node*> pq;
	std::set<std::pair<int , int>> openSet;
	double nodedistance(node& a, node& b);
	




};