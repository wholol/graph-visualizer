#include "Graph.h"
#include <tuple>
#include <iostream>
#include <assert.h>

Graph::Graph(std::tuple<int,int> getNumTile)
{
	int totalXTiles = std::get<0>(getNumTile);
	int totalYTiles = std::get<1>(getNumTile);

	for (int i = 0; i < totalXTiles; ++i) {
		for (int j = 0; j < totalYTiles; ++j) {
			nodes.emplace_back(i , j);
		}
	}

	assert(nodes.size() == totalXTiles * totalYTiles);

	for (int x = 0; x < totalXTiles; ++x) {
		for (int y = 0; y < totalYTiles; ++y) {		
			if (x == 0 && y == 0) {			//top right corner case
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y + 1);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y + 1);
			}

			else if (x == totalXTiles - 1 && y == 0) {			//top left corner case
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y + 1);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y - 1);
			}

			else if (y == totalYTiles - 1 && x == 0)				//bottom left corner
			{
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y + 1);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y - 1);
			}

			else if (y == totalYTiles - 1 && x == totalXTiles - 1)				//bottom left corner
			{
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1 ,y);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x , y - 1);
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y - 1);
			}

			else if (y == 0) {					//top row case (should have 5 neighbours)
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y + 1);	//node below
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y + 1);	//diagonal node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y - 1);	//diagnonal node
			}

			else if (y == totalYTiles - 1) {					//top row case (should have 5 neighbours)
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y - 1);		//node above
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y - 1);	//diagnoal node			
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y - 1);	//diagnonal node
			}

			else if (x == 0) {
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y + 1);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y - 1);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y);		//node above
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y - 1);	//diagnoal node			
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y + 1);	//diagnonal node
			}

			else if (x == totalXTiles - 1) {
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y + 1);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y - 1);		//adjacent node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y);		//node above
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y - 1);	//diagnoal node			
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y + 1);	//diagnonal node
			}

			else {
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y + 1);		//node below
				nodes[x * totalXTiles + y].neighbours.emplace_back(x, y - 1);		//node above
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y + 1);	//bottom right node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y + 1);		//bottom left node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y);		//node to the right
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y);	//node to the left
				nodes[x * totalXTiles + y].neighbours.emplace_back(x - 1, y - 1);	//top left node
				nodes[x * totalXTiles + y].neighbours.emplace_back(x + 1, y - 1);		//top right node
			}
		}
	}




	
}
