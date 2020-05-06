#include "Game.h"
#include <thread>
#include <iostream>

Game::Game(int screenwidth, int screenheight, const std::string& title, int framerate)
	:createwindow(sf::VideoMode(screenwidth, screenheight), title),
	grid(screenwidth,screenheight,mouse,createwindow),
	graph(grid.getTileNums())
{
	if (!font.loadFromFile("fonts/Bebas-Regular.ttf")) { }
	text.setFont(font);
	text.setString(graphtype);
	text.setPosition(sf::Vector2f(5, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setCharacterSize(25);
}


void Game::render() {		//rendering
	grid.drawGrid();	
	grid.drawPath();
	createwindow.draw(text);
	createwindow.display();
}

void Game::update() {											//update game 

	if (!solve) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			grid.resetGrid();
			graph.resetGraph();
			graphtype = "BFS";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			grid.resetGrid();
			graph.resetGraph();
			graphtype = "DFS";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			grid.resetGrid();
			graph.resetGraph();
			graphtype = "Dijkstra";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			grid.resetGrid();
			graph.resetGraph();
			graphtype = "AStar";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			grid.resetGrid();
			graph.resetGraph();
			graphtype = "biBFS";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			grid.resetGrid();
			graph.resetGraph();
			graphtype = "biDFS";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			grid.resetGrid();
			graph.resetGraph();
			graphtype = "BestFS";
		}

		algo = std::move(AlgorithmFactory::generateAlgorithm(graphtype, graph));	//generate algorithm
		text.setString(graphtype);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	if (algo != nullptr) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {			//sets up obstacles for the grid.
			grid.setObstacle();
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {			//sets up obstacles for the grid.
			grid.setSource();
			grid.setTarget();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			solve = true;
		}
	}

	if (solve){
		Location srcpos = grid.getSrcPos();
		Location targetpos = grid.getTargetPos();
		std::vector<Location> Obstacles = grid.getObstacleLocation();
		algo->SolveAlgorithm(srcpos,targetpos,Obstacles,grid,createwindow);
		algo->constructPath(grid);
		solve = false;
		graphtype = graphtype + " solved!";
	}
	
	createwindow.clear();
}


bool Game::quit()			//call quit game

//DO NOT DELETE CONTENTS OF THIS FUNCTION TO PREVENT AN UNRESPONSIV SCREEN//
{
	while (createwindow.pollEvent(event)) {		//NON BLOCKING FUNCTION, WILL NOT GET STUCK IN WHILE LOOP.
		if (event.type == sf::Event::Closed) {
			createwindow.close();
			quitgame = true;
		}
	}
	return quitgame;

}

Game::~Game() {}