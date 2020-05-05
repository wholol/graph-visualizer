#include "BiBFS.h"
#include <thread>

biBFS::biBFS(Graph & graph)
	:graph(graph)
{}

void biBFS::SolveAlgorithm(const Location & srcpos, const Location & targetpos, const std::vector<Location>& obstacles, Grid & grid, sf::RenderWindow & createwindow)
{
	for (const auto& obs : obstacles) {	//set obstacles
		graph.getNode(obs).isObstacle = true;
	}

	this->targetpos = targetpos;
	this->srcpos = srcpos;

	node* srcnode = &(graph.getNode(srcpos));
	node* targetnode = &(graph.getNode(targetpos));
	srcDeque.emplace_back(srcnode);			//push into queue.
	srcnode->Visited = true;
	targetDeque.emplace_back(targetnode);			//push into queue.
	targetnode->Visited = true;

	while (!srcDeque.empty() && !targetDeque.empty() && !intersect) {

		if (!srcDeque.empty()) {
			node* srccurr = std::move(srcDeque.front());		//get the current location
			srcDeque.pop_front();
			grid.ColourVisitedTile(srccurr->nodeloc);
			
			grid.drawGrid();
			createwindow.display();

			for (auto &neighbour : srccurr->neighbours) {
				if (!neighbour->Visited) {
					if (neighbour->isObstacle) {

					}
					else {
						neighbour->parent = srccurr;
						srcDeque.emplace_back(neighbour);
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

		if (!targetDeque.empty()) {
			node* targetcurr = std::move(targetDeque.front());	//get the current location
			targetDeque.pop_front();
			grid.ColourVisitedTile(targetcurr->nodeloc);		//colour current location

			grid.drawGrid();
			createwindow.display();

			for (auto &neighbour : targetcurr->neighbours) {
				if (!neighbour->Visited) {
					if (neighbour->isObstacle) {

					}

					else {
						neighbour->parent = targetcurr;
						targetDeque.emplace_back(neighbour);
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

