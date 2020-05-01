#pragma once
#include <SFML\Graphics.hpp>

//grid class
class Grid {
public:
	Grid(int screenwidth, int screenheight);
	void drawGrid();
	void setObstacle();

private:
	sf::RectangleShape grid;
	static constexpr int TileDimension = 20;		//dimension of tile
	int NumTilesX;			//number of tiles in X direction
	int NumTilesY;			//number of tiles in Y direction
};