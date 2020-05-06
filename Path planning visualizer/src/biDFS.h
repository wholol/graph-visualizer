#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Grid.h"
#include <stack>
#include <unordered_set>

class biDFS : public Algorithm {

public:
	biDFS(Graph &graph);
	virtual void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow) override;
	virtual void constructPath(Grid& grid) override;

private:
	Graph &graph;
	Location srcpos;
	Location targetpos;
	sf::Text text;
	sf::Font font;
	node* intersectnode;
	node* otherparent;
	std::stack<node*> srcStack;
	std::stack<node*> targetStack;
	std::unordered_set<node*> srcSet;
	std::unordered_set<node*> targetSet;
	bool intersect = false;
};