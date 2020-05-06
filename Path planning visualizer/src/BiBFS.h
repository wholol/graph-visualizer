#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Grid.h"
#include <deque>
#include <unordered_set>
class biBFS : public Algorithm {

public:
	biBFS(Graph &graph);
	void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow) override;
	void constructPath(Grid& grid) override;

private:
	Graph &graph;
	Location srcpos;
	Location targetpos;
	node* intersectnode;
	node* otherparent;
	sf::Text text;
	sf::Font font;
	std::deque<node*> srcStack;
	std::deque<node*> targetStack;
	std::unordered_set<node*> srcSet;
	std::unordered_set<node*> targetSet;
	bool intersect = false;
};