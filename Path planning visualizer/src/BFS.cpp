#include "BFS.h"
#include <iostream>
#include <thread>

BFS::BFS(Graph graph)
	:graph(graph)
{}

void BFS::SolveAlgorithm(const Location& srcpos, const Location& targetpos,Grid &grid,sf::RenderWindow& createwindow)
{

	this->srcpos = srcpos;
	this->targetpos = targetpos;

	node start = graph.getNode(srcpos);
	q.push(start);	//push start into queue

	while (!q.empty()) {
		node curr = q.front();		//get current node
		q.pop();
		if (!graph.getNode(curr.nodeloc).Visited) {
			graph.getNode(curr.nodeloc).Visited = true;
			grid.ColourVisitedTile(graph.getNode(curr.nodeloc).nodeloc);
		}

		//grid.drawGrid();
		createwindow.display();

		for (auto &neighbour : graph.getNode(curr.nodeloc).neighbours) {
			if (!neighbour.Visited) {
				q.push(neighbour);
				grid.ColourVisitingTile(neighbour.nodeloc);
			}
			else {
				grid.ColourVisitedTile(graph.getNode(curr.nodeloc).nodeloc);
			}
		}
	
	}
}
