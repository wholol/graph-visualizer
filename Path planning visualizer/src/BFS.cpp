#include "BFS.h"
#include <iostream>
#include <thread>

BFS::BFS(Graph graph)
	:graph(graph)
{}

void BFS::SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow)
{
	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	this->srcpos = srcpos;
	this->targetpos = targetpos;
	deque.emplace_back(srcpos);			//push into queue.

	while (!deque.empty() && !targetreached) {

		Location curr = std::move(deque.front());		//get the current location
		deque.pop_front();
		grid.ColourVisitedTile(curr);		//colour current location
		
		grid.drawGrid();
		createwindow.display();


		for (auto &neighbour : graph.getNode(curr).neighbours) {
			Location &neighbourloc = neighbour.nodeloc;
			if (neighbourloc == targetpos) {
				targetreached = true;
			}

			if (graph.getNode(neighbourloc).Visited) {
				continue;
			}

			else if (!graph.getNode(neighbourloc).Visited) {
				if (graph.getNode(neighbourloc).isObstacle) {

				}
				else {
					deque.emplace_back(neighbourloc);
					graph.getNode(neighbourloc).Visited = true;
					grid.ColourVisitingTile(neighbourloc);
				}
			}
		}
	}

	return;
}

void BFS::drawpath(Grid& grid)
{
	node* traverse = graph.getNode(targetpos).parent;
	while (traverse != nullptr) {
		grid.ColourPathTile(traverse->nodeloc);
		traverse = traverse->parent;
	}
}
