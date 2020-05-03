#include "AStar.h"

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

	this->srcpos = srcpos;
	this->targetpos = targetpos;
	//deque.emplace_back(srcpos);			//push into queue.

	//while (!deque.empty() && !targetreached) {

}
