#include "Game.h"
#include <thread>

Game::Game(int screenwidth, int screenheight, const std::string& title, int framerate)
	:createwindow(sf::VideoMode(screenwidth, screenheight), title),
	grid(screenwidth,screenheight,mouse,createwindow),
	graph(grid.getTileNums())		
{}


void Game::render() {		//rendering

	grid.drawGrid();		
	createwindow.display();
}

void Game::main_menu()
{

}

void Game::update() {		//update game 

	
	std::this_thread::sleep_for(std::chrono::milliseconds(70));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {			//sets up obstacles for the grid.
		grid.setObstacle();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {			//sets up obstacles for the grid.
		grid.setSource();
		grid.setTarget();
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