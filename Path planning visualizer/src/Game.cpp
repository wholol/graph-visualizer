#include "Game.h"
#include <thread>
#include <iostream>

Game::Game(int screenwidth, int screenheight, const std::string& title, int framerate)
	:createwindow(sf::VideoMode(screenwidth, screenheight), title),
	grid(screenwidth,screenheight,mouse,createwindow),
	graph(grid.getTileNums()),
	dfs(graph),
	bfs(graph)
{}


void Game::render() {		//rendering

	grid.drawGrid();		
	createwindow.display();
}

void Game::main_menu()
{

}

void Game::update() {		//update game 

	
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {			//sets up obstacles for the grid.
		grid.setObstacle();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {			//sets up obstacles for the grid.
		grid.setSource();
		grid.setTarget();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		solve = true;
	}

	if (solve){
		Location srcpos = grid.getSrcPos();
		Location targetpos = grid.getTargetPos();
		std::vector<Location> Obstacles = grid.getObstacleLocation();
		std::cout << "solving.." << std::endl;
		bfs.SolveAlgorithm(srcpos,targetpos,Obstacles,grid,createwindow);
		bfs.drawpath(grid);
		solve = false;
	}
	std::cout << "solving.." << std::endl;
	

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