#pragma once
#include "Location.h"
#include <vector>

class Graph{
public:
	Graph(std::tuple<int,int> getNumTiles);		//construct the graph

private:

	struct node {
		node(int posx, int posy) :nodeloc({ posx,posy }) {}	//construct location

		Location nodeloc;		//posx, posy of the node in gridspace
		node* parent = nullptr;		//pointer to parent node
		bool isObstacle = false;	//is the node an obstacle?
		std::vector<node> neighbours;			//stor the vector of neigghbours for the node
		
	};

	std::vector<node> nodes;			//all nodes in the graph

};