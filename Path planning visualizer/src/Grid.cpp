#include "Grid.h"
#include <iostream>
#include <thread>

Grid::Grid(int screenwidth, int screenheight, const sf::Mouse& mouse, sf::RenderWindow& createwindow)
	:screenwidth(screenwidth),
	screenheight(screenheight),
	mouse(mouse),
	createwindow(createwindow)
{
	/*compute Number of Tiles*/
	NumTilesX = screenwidth / TileDimension;
	NumTilesY = screenheight / TileDimension;

	/* initialize default src and targ et pos*/
	srcpos = { 0 ,0 };
	targetpos = { NumTilesX - 1 , NumTilesY - 1 };

	for (int i = 0; i < NumTilesX * NumTilesY; ++i) {	//initialize all tile objects
		TileMap.emplace_back(sf::Vector2f(TileDimension, TileDimension));	//costruct dimensions
	}

	for (int x = 0; x < NumTilesX; ++x) {
		for (int y = 0; y < NumTilesY; ++y) {
			TileMap[x * NumTilesX + y].setPosition(sf::Vector2f(x * TileDimension, y * TileDimension));
			TileMap[x * NumTilesX + y].setFillColor(openTileColour);
			TileMap[x * NumTilesX + y].setOutlineColor(sf::Color::Black);
			TileMap[x * NumTilesX + y].setOutlineThickness(-OutlineThickness);
		}
	}

	/* colour src and target pos*/
	TileMap[srcpos.posx * NumTilesX + srcpos.posy].setFillColor(srcTileColour);
	TileMap[targetpos.posx * NumTilesX + targetpos.posy].setFillColor(targetTileColour);
}

void Grid::drawGrid()
{
	for (const auto& Tiles : TileMap) {
		createwindow.draw(Tiles);
	}		//draw tiles
}

void Grid::setObstacle()
{
	int mouseposx = mouse.getPosition(createwindow).x;
	int mouseposy = mouse.getPosition(createwindow).y;

	int x = (int)(mouseposx / TileDimension);		//scale mouse coodinates
	int y = (int)(mouseposy / TileDimension);		//scale mouse coordinats
	
	outofBounds(x, y);

	Location mouseloc = { x , y };	//cache mouse location of the grid

	//reset obstacle colour to open colour
	if (getTileColor(mouseloc) == obstacleTileColour) {
		setTileColor(mouseloc, openTileColour);
		return;
	}

	if (getTileColor(mouseloc) == srcTileColour) {		//do not set obstacle for src colour
		return;
	}

	if (getTileColor(mouseloc) == targetTileColour) {		//do not set obstacle for colourd tile
		return;
	}

	setTileColor(mouseloc, obstacleTileColour);		//set the tile colour 

}

void Grid::setTarget()
{
	int mouseposx = mouse.getPosition(createwindow).x;
	int mouseposy = mouse.getPosition(createwindow).y;
	int x = (int)(mouseposx / TileDimension);
	int y = (int)(mouseposy / TileDimension);

	outofBounds(x, y);

	Location prevTargetLoc;			//cache the previous Target location
	Location mouseLoc = { x , y };

	if (getTileColor(mouseLoc) == targetTileColour) {
		changingTargetPos = true;			//set putting source position to true
		prevTargetLoc = { x , y };
	}

	while (changingTargetPos) {			//while the user is tryig to change the position of the source.
		int mouseposx = mouse.getPosition(createwindow).x;	
		int mouseposy = mouse.getPosition(createwindow).y;
		int x = (int)(mouseposx / TileDimension);
		int y = (int)(mouseposy / TileDimension);

		Location newTargetLoc = { x , y };		//keep polling for new target location

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			if (getTileColor(newTargetLoc) == obstacleTileColour) {			//if tile is obstacle, continue
				continue;
			}

			if (getTileColor(newTargetLoc) == srcTileColour) {	//if user chooses target tile
				changingSrcPos = false;			//do not let changing target pos be true if user is trying to chang src pos.
				continue;
			}

			if (getTileColor(newTargetLoc) == openTileColour) {		//if the new target tile is open
				setTileColor(newTargetLoc, targetTileColour);		//set the tile colour 
				updateSrcPos(newTargetLoc);				//update the target position.
				setTileColor(prevTargetLoc, openTileColour);	//set the tile colour of the old target position to open
				changingTargetPos = false;
				break;
			}
		}
	}
}

void Grid::setSource()
{
	int mouseposx = mouse.getPosition(createwindow).x;
	int mouseposy = mouse.getPosition(createwindow).y;
	int x = (int)(mouseposx / TileDimension);
	int y = (int)(mouseposy / TileDimension);

	outofBounds(x, y);

	Location prevSrcLoc;			//cache the previous source location
	Location mouseLoc = { x , y };

	if (getTileColor(mouseLoc) == srcTileColour) {
		changingSrcPos = true;			//set putting source position to true
		prevSrcLoc = { x , y };
	}

	while (changingSrcPos) {			//while the user is tryig to change the position of the source.
		int mouseposx = mouse.getPosition(createwindow).x;
		int mouseposy = mouse.getPosition(createwindow).y;
		int x = (int)(mouseposx / TileDimension);
		int y = (int)(mouseposy / TileDimension);

		Location newSrcLoc = { x , y };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			if (getTileColor(newSrcLoc) == obstacleTileColour) {
				continue;
			}

			if (getTileColor(newSrcLoc) == targetTileColour) {	//if user chooses target tile
				changingTargetPos = false;			//do not let changing target pos be true if user is trying to chang src pos.
				continue;
			}

			if (getTileColor(newSrcLoc) == openTileColour) {		//if the new src tile is open
				setTileColor(newSrcLoc, srcTileColour);		//set the tile colour 
				updateSrcPos(newSrcLoc);				//update the source position.
				setTileColor(prevSrcLoc, openTileColour);	//set the tile colour of the old src position to open
				changingSrcPos = false;
				break;
			}
		}
	}
}

std::tuple<int, int> Grid::getTileNums() const
{
	return std::make_tuple(NumTilesX, NumTilesY);
}

void Grid::updateSrcPos(const Location& loc)
{
	srcpos.posx = loc.posx;
	srcpos.posy = loc.posy;
}

void Grid::updateTargetPos(const Location& loc)
{
	targetpos.posx = loc.posx;
	targetpos.posy = loc.posy;
}

sf::Color Grid::getTileColor(const Location& loc) const
{
	return TileMap[loc.posx * NumTilesX + loc.posy].getFillColor();
}

void Grid::setTileColor(const Location& loc ,const sf::Color& color)
{
	TileMap[loc.posx * NumTilesX + loc.posy].setFillColor(color);
}

bool Grid::outofBounds(int x, int y)
{
	if (x < 0 || y < 0 || x > screenwidth || y > screenheight) {		//bound check
		return true;
	}
	return false;
}
