#pragma once
#include "Graph.h"
#include "Grid.h"
#include <stack>
#include <unordered_set>

class biDFS {

public:
	biDFS(Graph &graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow);
	void constructPath(Grid& grid);

private:
	Graph &graph;
	Location srcpos;
	Location targetpos;
	node* intersectnode;
	node* otherparent;
	std::stack<node*> srcStack;
	std::stack<node*> targetStack;
	std::unordered_set<node*> srcSet;
	std::unordered_set<node*> targetSet;
	bool intersect = false;
};