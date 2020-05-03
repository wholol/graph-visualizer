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

		Location curr = std::move(deque.front());
		deque.pop_front();
			grid.ColourVisitedTile(graph.getNode(curr).nodeloc);
		
		grid.drawGrid();
		createwindow.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(25));

		for (auto &neighbour : graph.getNode(curr).neighbours) {

			if (neighbour.nodeloc == targetpos) {
				targetreached = true;
			}

			if (graph.getNode(neighbour.nodeloc).Visited) {
				continue;
			}

			else if (!graph.getNode(neighbour.nodeloc).Visited) {
				if (graph.getNode(neighbour.nodeloc).isObstacle) {

				}
				else {
					deque.emplace_back(neighbour.nodeloc);
					graph.getNode(neighbour.nodeloc).Visited = true;
					grid.ColourVisitingTile(neighbour.nodeloc);
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
