#pragma once
#include "Location.h"
#include <vector>

struct node {
	node(int posx, int posy) :nodeloc({ posx,posy }) {}	//construct location

	Location nodeloc;		//posx, posy of the node in gridspace
	bool Visited = false;
	node* parent = nullptr;		//pointer to parent node
	bool isObstacle = false;	//is the node an obstacle?
	std::vector<node> neighbours;			//stor the vector of neigghbours for the node
};

class Graph{

private:
	std::vector<node> nodes;			//all nodes in the graph
	int totalXTiles;
	int totalYTiles;

public:
	Graph(std::tuple<int,int> getNumTiles);		//construct the graph
	node& getNode(const Location& loc);
	std::vector<node> getallnodes() const;



};