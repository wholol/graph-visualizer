#pragma once
#include <SFML\Graphics.hpp>
#include "Grid.h"
#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
#include "AStar.h"
#include "Dijkstra.h"

class Game {			//game class. should have render, update/events, quit and initialize.

public:
	Game(int screenwidth, int screenheight, const std::string& title, int framerate);	//game constructor
	Game &operator=(Game &other) = delete;				//prevent assigning game object
	Game(const Game& other) = delete;					//no deep copying a game object
	Game(Game &&other) = delete;						//no moving game object
	~Game();

	void main_menu();
	void update();					//update logic
	void render();					//rende r
	bool quit();					//quit the window


private:
	bool quitgame = false;			//quit game
	bool MainMenu = true;
	Grid grid;
	Graph graph;
	DFS dfs;
	BFS bfs;
	AStar aStar;
	Dijkstra dij;
	sf::Mouse mouse;
	sf::Event event;					//events class
	sf::RenderWindow createwindow;		//windows class
	bool GameOver = false;				//gameover boolean
	bool solve = false;


};