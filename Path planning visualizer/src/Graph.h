#pragma once
#include "Location.h"
#include <vector>

/*node struct*/
struct node {
	node(int posx, int posy) :nodeloc({ posx,posy }) {}	//construct location

	Location nodeloc;		//posx, posy of the node in gridspace
	bool Visited = false;
	node* parent = nullptr;		//pointer to parent node
	bool isObstacle = false;	//is the node an obstacle?
	double hCost = INFINITY;				//heuristics for node (distance from current node to target).
	double gCost = INFINITY;				//heuristics for node (distance from start to curent node).
	double fCost;						//fCost
	std::vector<node*> neighbours;			//store the vector of neigghbours for the node
};

/* graph class*/
class Graph{

private:
	std::vector<node> nodes;			//all nodes in the graph
	int totalXTiles;
	int totalYTiles;

public:
	Graph(std::tuple<int,int> getNumTiles);		//construct the graph
	node& getNode(const Location& loc);
	void resetGraph();
};