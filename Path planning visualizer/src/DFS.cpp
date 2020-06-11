#include "DFS.h"
#include <iostream>
#include <thread>

DFS::DFS(Graph& graph)
	:graph(graph)
{
	if (!font.loadFromFile("fonts/Bebas-Regular.ttf")) {}
	text.setFont(font);
	text.setString("Solving DFS..");
	text.setPosition(sf::Vector2f(5, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setCharacterSize(25);
}

void DFS::SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow)
{
	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	this->targetpos = targetpos;
	this->srcpos = srcpos;

	node* srcnode = &(graph.getNode(srcpos));
	stack.push(srcnode);			//push into queue.
	srcnode->Visited = true;

	while (!stack.empty() && !targetreached) {				

		node* curr = stack.top();
		stack.pop();
		grid.ColourVisitedTile(curr->nodeloc);

		grid.drawGrid();		
		createwindow.draw(text);
		createwindow.display();

		if (curr->nodeloc == targetpos) {
			targetreached = true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(40));
		
		for (auto &neighbour: curr->neighbours) {		
			
			Location neighbourloc = neighbour->nodeloc;

			if (neighbourloc == targetpos) {
				targetreached = true;
			}

			if (neighbour->Visited || neighbour->isObstacle) {
				continue;
			}

			else {
				neighbour->parent = curr;
				stack.push(neighbour);
				neighbour->Visited = true;
				grid.ColourVisitingTile(neighbourloc);
			}
		}
	}

	return;
}

void DFS::constructPath(Grid& grid)
{
	node* traverse = &(graph.getNode(targetpos));
	if (traverse != nullptr) {
		while (traverse->parent != nullptr) {
			grid.ColourPathTile(traverse->nodeloc, traverse->parent->nodeloc);
			traverse = traverse->parent;
		}
	}
}
