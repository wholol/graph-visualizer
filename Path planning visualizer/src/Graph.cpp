#include "Graph.h"
#include <tuple>
#include <iostream>
#include <assert.h>

Graph::Graph(std::tuple<int,int> getNumTile)
{
	auto[totalXTiles, totalYTiles] = getNumTile;
	this->totalXTiles = totalXTiles;
	this->totalYTiles = totalYTiles;

	for (int i = 0; i < totalXTiles; ++i) {
		for (int j = 0; j < totalYTiles; ++j) {
			nodes.emplace_back(i , j);
		}
	}

	assert(nodes.size() == totalXTiles * totalYTiles);

	for (int x = 0; x < totalXTiles; ++x) {
		for (int y = 0; y < totalYTiles; ++y) {		
			
			if (y > 0)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[x*totalXTiles + (y - 1)]);
			if (y < totalXTiles - 1)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[x*totalXTiles + (y + 1)]);
			if (x > 0)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[(x - 1)*totalXTiles + y]);
			if (x < totalXTiles - 1)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[(x + 1)*totalXTiles + y]);


			if (y > 0 && x > 0)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[(x - 1)*totalXTiles + (y - 1)]);
			if (y < totalXTiles -1 && x > 0)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[(x - 1)*totalXTiles + (y + 1)]);
			if (y > 0 && x < totalXTiles -1)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[(x + 1)*totalXTiles + (y - 1)]);
			if (y < totalXTiles - 1 && x < totalXTiles - 1)
				nodes[x*totalXTiles + y].neighbours.emplace_back(&nodes[(x + 1)*totalXTiles + (y + 1)]);
		}
	}
}

node& Graph::getNode(const Location& loc) 
{
	assert(loc.posx * totalXTiles + loc.posy < totalXTiles * totalYTiles);
	assert(loc.posx * totalXTiles + loc.posy >= 0);
	return nodes[loc.posx * totalXTiles + loc.posy];		//get desired node
}

void Graph::resetGraph()
{
	for (auto& node : nodes) {
		node.fCost = INFINITY;
		node.gCost = INFINITY;
		node.hCost = INFINITY;
		node.isObstacle = false;
		node.Visited = false;
		node.parent = nullptr;
	}
}



