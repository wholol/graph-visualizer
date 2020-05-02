#pragma once
#include "Graph.h"
#include "Grid.h"
#include <queue>

class BFS {
public:
	BFS(Graph graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos,Grid &grid,sf::RenderWindow& createwindow);


private:
	Graph graph;
	std::queue<node> q;	//
	Location srcpos;
	Location targetpos;



};