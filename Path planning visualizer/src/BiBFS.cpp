#include "BiBFS.h"
#include <thread>

biBFS::biBFS(Graph & graph)
	:graph(graph)
{
	if (!font.loadFromFile("fonts/Bebas-Regular.ttf")) {}
	text.setFont(font);
	text.setString("Solving biBFS..");
	text.setPosition(sf::Vector2f(5, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setCharacterSize(25);
}

void biBFS::SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid& grid, sf::RenderWindow& createwindow)
{
	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	this->targetpos = targetpos;
	this->srcpos = srcpos;

	node* srcnode = &(graph.getNode(srcpos));
	node* targetnode = &(graph.getNode(targetpos));
	srcStack.emplace_back(srcnode);			//push into queue.
	srcnode->Visited = true;
	targetStack.emplace_back(targetnode);			//push into queue.
	targetnode->Visited = true;

	while (!srcStack.empty() && !targetStack.empty() && !intersect) {

		if (!srcStack.empty()) {
			node* srccurr = srcStack.front();		//get the current location
			srcStack.pop_front();
			
			grid.ColourVisitedTile(srccurr->nodeloc);
			grid.drawGrid();
			createwindow.draw(text);
			createwindow.display();

			for (auto &neighbour : srccurr->neighbours) {
				if (!neighbour->Visited) {
					if (neighbour->isObstacle) {

					}
					else {
						neighbour->parent = srccurr;
						srcStack.emplace_back(neighbour);
						neighbour->Visited = true;
						srcSet.insert(srccurr);
						grid.ColourVisitingTile(neighbour->nodeloc);
					}
				}
				else {		//if visited
					auto findFromSrc = targetSet.find(neighbour); //check if neighbour is in the target set
					if (findFromSrc != targetSet.end()) {			//if the crrent node from soucre is found in tRget set
						grid.ColourVisitedTile(neighbour->nodeloc);		
						intersectnode = neighbour;
						otherparent = srccurr;
						intersect = true;
					}
				}
			}
		}

		if (!targetStack.empty()) {
			node* targetcurr = std::move(targetStack.front());	//get the current location
			targetStack.pop_front();
			
			grid.ColourVisitedTile(targetcurr->nodeloc);		//colour current location
			grid.drawGrid();
			createwindow.draw(text);
			createwindow.display();

			for (auto &neighbour : targetcurr->neighbours) {
				if (!neighbour->Visited) {
					if (neighbour->isObstacle) {

					}

					else {
						neighbour->parent = targetcurr;
						targetStack.emplace_back(neighbour);
						neighbour->Visited = true;
						targetSet.insert(neighbour);
						grid.ColourVisitingTile(neighbour->nodeloc);		//(in queue)
					}
				}

				else {		//if visited, i.e. in queue already
					auto findFromSrc = srcSet.find(neighbour); //check if neighbour is in the src set
					if (findFromSrc != srcSet.end()) {			//if the crrent node from soucre is found in src set
						grid.ColourVisitedTile(neighbour->nodeloc);
						intersectnode = neighbour;
						otherparent = targetcurr;
						intersect = true;
					}
				}
			}
		}
	}
	return;
}

void biBFS::constructPath(Grid & grid)
{
	node* traverse = intersectnode;			//get the interesection node
		while (traverse->parent != nullptr) {
			grid.ColourPathTile(traverse->nodeloc, traverse->parent->nodeloc);
			traverse = traverse->parent;
		}

		intersectnode->parent = otherparent;
		traverse = intersectnode;
		
		while (traverse->parent != nullptr) {
			grid.ColourPathTile(traverse->nodeloc, traverse->parent->nodeloc);
			traverse = traverse->parent;
		}

}

