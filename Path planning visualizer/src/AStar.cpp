#include "AStar.h"
#include <iostream>
AStar::AStar(Graph graph)
	:graph(graph)
{

	
}

void AStar::SolveAlgorithm(const Location & srcpos, const Location & targetpos, const std::vector<Location>& obstacles, Grid & grid, sf::RenderWindow & createwindow)
{
	this->srcpos = srcpos;
	this->targetpos = targetpos;

	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	auto fCostcomparator = [](node *leftnode, node *rightnode)
	{
		return leftnode->fCost < rightnode->fCost;
	};
	
	node &srcNode = graph.getNode(srcpos);
	srcNode.gCost = 0;
	node targetNode = graph.getNode(targetpos);
	srcNode.hCost = nodedistance(srcNode,targetNode);
	pq.emplace_back(&srcNode);					//push node into queue.


	while (!pq.empty() && !targetreached) {		//while priority queue is not empty
		pq.sort(fCostcomparator);
		node* curr = pq.front();
		pq.pop_front();								//pop from queue.
		graph.getNode(curr->nodeloc).Visited = true;
		grid.ColourVisitedTile(curr->nodeloc);

		if (curr->nodeloc == targetpos) {		//set target reached to true
			targetreached = true;
		}

		grid.drawGrid();
		createwindow.display();

		for (auto &neighbour : graph.getNode(curr->nodeloc).neighbours) {

			if (graph.getNode(neighbour.nodeloc).Visited) {
				continue;
			}
		
			else {
				double estimatedgCost = curr->gCost + nodedistance(*curr, neighbour);
				if (estimatedgCost < graph.getNode(neighbour.nodeloc).gCost) {			//if estiamted gcost is lesser, means there is a more optimal path from origin to th neighbour
					graph.getNode(neighbour.nodeloc).parent = &(graph.getNode(curr->nodeloc));
					graph.getNode(neighbour.nodeloc).gCost = estimatedgCost;
					graph.getNode(neighbour.nodeloc).hCost = nodedistance(neighbour, graph.getNode(targetpos));
					graph.getNode(neighbour.nodeloc).fCost = graph.getNode(neighbour.nodeloc).gCost + graph.getNode(neighbour.nodeloc).hCost;
					auto find = openSet.find(std::pair<int, int>(neighbour.nodeloc.posx, neighbour.nodeloc.posy));
					if (find == openSet.end()) {
						grid.ColourVisitingTile(neighbour.nodeloc);
						std::cout << "not in open" << std::endl;
						pq.emplace_back(&(graph.getNode(neighbour.nodeloc)));
						openSet.insert(std::pair<int, int>(neighbour.nodeloc.posx, neighbour.nodeloc.posy));
					}
					else {
						std::cout << "found pair " << std::endl;
					}
				}
			}
			
		}

	}


}

double AStar::nodedistance(node& a, node& b)
{
	int dx = (a.nodeloc.posx - b.nodeloc.posx);
	int dy= (a.nodeloc.posy - b.nodeloc.posy);
	return sqrt((dx * dx) + (dy * dy));			//sqrt(dx^2 - dy^2) for Euclidean
		
}
