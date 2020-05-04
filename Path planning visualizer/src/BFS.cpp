#include "BFS.h"
#include <iostream>
#include <thread>

BFS::BFS(Graph graph)
	:graph(graph)
{}

void BFS::SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow)
{
	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs)->isObstacle = true;
	}

	node* srcnode = (graph.getNode(srcpos));
	deque.emplace_back(srcnode);			//push into queue.

	while (!deque.empty() && !targetreached) {

		node* curr = std::move(deque.front());		//get the current location
		deque.pop_front();
		grid.ColourVisitedTile(curr->nodeloc);		//colour current location

		grid.drawGrid();
		createwindow.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(40));

		for (auto &neighbour : curr->neighbours) {
			Location neighbourloc = neighbour->nodeloc;
			if (neighbour->nodeloc == targetpos) {
				targetreached = true;
			}

			else if (!neighbour->Visited) {
				if (neighbour->isObstacle) {

				}

				else {
					deque.emplace_back(neighbour);
					neighbour->Visited = true;
					grid.ColourVisitingTile(neighbourloc);
				}
			}
		}
	}

	return;
}

void BFS::drawpath(Grid& grid, Location& targetpos)
{
	node* traverse = graph.getNode(targetpos)->parent;
	while (traverse != nullptr) {
		grid.ColourPathTile(traverse->nodeloc);
		traverse = traverse->parent;
	}
}
