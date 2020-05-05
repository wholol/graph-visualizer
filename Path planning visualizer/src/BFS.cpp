#include "BFS.h"
#include <iostream>
#include <thread>

BFS::BFS(Graph &graph)
	:graph(graph)
{}

void BFS::SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow)
{
	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	this->targetpos = targetpos;
	this->srcpos = srcpos;

	node* srcnode = &(graph.getNode(srcpos));
	deque.emplace_back(srcnode);			//push into queue.
	srcnode->Visited = true;

	while (!deque.empty() && !targetreached) {

		node* curr = std::move(deque.front());		//get the current location
		deque.pop_front();
		grid.ColourVisitedTile(curr->nodeloc);		//colour current location

		grid.drawGrid();
		createwindow.display();

		if (curr->nodeloc == targetpos) {
			targetreached = true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		for (auto &neighbour : curr->neighbours) {
			 if (!neighbour->Visited) {
				if (neighbour->isObstacle) {

				}

				else {
					neighbour->parent = curr;
					deque.emplace_back(neighbour);
					neighbour->Visited = true;
					grid.ColourVisitingTile(neighbour->nodeloc);
				}
			}
		}
	}
	return;
}

void BFS::constructPath(Grid& grid)
{
	node* traverse = &(graph.getNode(targetpos));

	if (traverse != nullptr) {
		while (traverse->parent != nullptr) {
			grid.ColourPathTile(traverse->nodeloc, traverse->parent->nodeloc);
			traverse = traverse->parent;
		}
	}
}
