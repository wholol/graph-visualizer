#include "Graph.h"
#include <tuple>
#include <iostream>

Graph::Graph(std::tuple<int,int> getNumTile)
{
	int totalXTiles = std::get<0>(getNumTile);
	int totalYTiles = std::get<1>(getNumTile);

	for (int i = 0; i < totalXTiles; ++i) {
		for (int j = 0; j < totalYTiles; ++j) {
			nodes.emplace_back(i , j);
		}
	}

	std::cout << nodes.size() << std::endl;

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
		}
	}




	
}
