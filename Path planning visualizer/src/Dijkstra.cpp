#include "Dijkstra.h"
#include <iostream>
#include <thread>

Dijkstra::Dijkstra(Graph &graph)
	:graph(graph)
{
	if (!font.loadFromFile("fonts/Bebas-Regular.ttf")) {}
	text.setFont(font);
	text.setString("Solving Dijsktra..");
	text.setPosition(sf::Vector2f(5, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setCharacterSize(25);
}

void Dijkstra::SolveAlgorithm(const Location & srcpos, const Location & targetpos, const std::vector<Location>& obstacles, Grid & grid, sf::RenderWindow & createwindow)
{
	this->srcpos = srcpos;
	this->targetpos = targetpos;

	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	auto gCostcomparator = [](node *leftnode, node *rightnode)
	{
		return leftnode->gCost < rightnode->gCost;
	};

	node *srcNode = &(graph.getNode(srcpos));
	srcNode->gCost = 0;
	node* targetNode = &(graph.getNode(targetpos));
	pq.emplace_back(srcNode);					//push node into queue.

	while (!pq.empty() && !targetreached) {		//while priority queue is not empty
		pq.sort(gCostcomparator);
		node* curr = pq.front();
		pq.pop_front();								//pop from queue.
		curr->Visited = true;
		grid.ColourVisitedTile(curr->nodeloc);

		if (curr->nodeloc == targetpos) {		//set target reached to true
			targetreached = true;
		}

		grid.drawGrid();
		createwindow.draw(text);
		createwindow.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		for (auto &neighbour : curr->neighbours) {

			if (neighbour->Visited || neighbour->isObstacle) {
				continue;	//if visited, it means it has been popped from the prio queue (already the possible shortest vertex).
			}

			else {
				double estimatedgCost = curr->gCost + nodedistance(curr, neighbour);
				if (estimatedgCost < neighbour->gCost) {			//if estiamted gcost is lesser, means there is a more optimal path from origin to th neighbour
					neighbour->parent = curr;
					neighbour->gCost = estimatedgCost;
					auto find = openSet.find(neighbour);
					if (find == openSet.end()) {		//set is used to check if it is in the priority queue
						grid.ColourVisitingTile(neighbour->nodeloc);
						pq.emplace_back(neighbour);
						openSet.insert(neighbour);
					}
				}
			}
		}
	}
	return;
}

void Dijkstra::constructPath(Grid& grid)
{
	node* traverse = &graph.getNode(targetpos);
	if (traverse != nullptr) {
		while (traverse->parent != nullptr) {
			grid.ColourPathTile(traverse->nodeloc, traverse->parent->nodeloc);
			traverse = traverse->parent;
		}
	}
}

double Dijkstra::nodedistance(node* a, node* b)
{
	int dx = (a->nodeloc.posx - b->nodeloc.posx);
	int dy = (a->nodeloc.posy - b->nodeloc.posy);
	return sqrt((dx * dx) + (dy * dy));			//sqrt(dx^2 - dy^2) for Euclidean	
}
