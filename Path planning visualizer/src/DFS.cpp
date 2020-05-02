#include "DFS.h"
#include <iostream>
#include <thread>

DFS::DFS(Graph graph)
	:graph(graph)
{}

void DFS::SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow)
{
	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	this->srcpos = srcpos;
	this->targetpos = targetpos;
	stack.push(srcpos);			//push into queue.

	while (!stack.empty() && !targetreached) {				

		Location curr = stack.top();
		stack.pop();
		std::cout << stack.size() << std::endl;
		if (!graph.getNode(curr).Visited) {
			graph.getNode(curr).Visited = true;
			grid.ColourVisitedTile(graph.getNode(curr).nodeloc);
		}

		grid.drawGrid();					
		createwindow.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
		
		for (auto &neighbour: graph.getNode(curr).neighbours) {		
			
			if (neighbour.nodeloc == targetpos) {
				targetreached = true;
			}

			if (!graph.getNode(neighbour.nodeloc).Visited){
				if (graph.getNode(neighbour.nodeloc).isObstacle) {

				}
				else {
					stack.push(neighbour.nodeloc);
					grid.ColourVisitingTile(neighbour.nodeloc);
				}
			}
		}
	}

	return;
}

void DFS::drawpath(Grid& grid)
{
	node* traverse = graph.getNode(targetpos).parent;
	while (traverse != nullptr) {
		grid.ColourPathTile(traverse->nodeloc);
		traverse = traverse->parent;
	}
}
