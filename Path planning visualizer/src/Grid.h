#pragma once
#include <SFML\Graphics.hpp>
#include "Location.h"

//grid class
class Grid {
public:
	Grid(int screenwidth, int screenheight,const sf::Mouse& mouse, sf::RenderWindow& createwindow);
	void drawGrid();
	void setObstacle();
	void setTarget();
	void setSource();
	void ColourVisitedTile(const Location& loc);
	void ColourVisitingTile(const Location& loc);
	std::tuple<int, int> getTileNums() const;
	Location getTargetPos() const;
	Location getSrcPos() const;

private:
	std::vector<sf::RectangleShape> TileMap;
	
	const sf::Mouse& mouse;
	sf::RenderWindow& createwindow;
	
	static constexpr int TileDimension = 50;		//dimension of tile
	static constexpr int OutlineThickness = 2;
	
	const int screenwidth;
	const int screenheight;
	
	int NumTilesX;										//number of tiles in X direction
	int NumTilesY;										//number of tiles in Y direction
	
	Location srcpos;							//initialize src location
	Location targetpos;		//initialzie target position
	
	sf::Color openTileColour = sf::Color::White;
	sf::Color obstacleTileColour = sf::Color::Blue;
	sf::Color srcTileColour = sf::Color::Red;
	sf::Color targetTileColour = sf::Color::Cyan;
	sf::Color visitedTileColour = sf::Color::Magenta;
	sf::Color visitngTileColour = sf::Color::Green;

	
	bool changingSrcPos = false;
	bool changingTargetPos = false;

	/*helper methods*/
	void updateSrcPos(const Location& loc);			//update source position
	void updateTargetPos(const Location& loc);		//update target position
	sf::Color getTileColor(const Location& loc) const;
	void setTileColor(const Location& loc,const sf::Color& color);
	bool outofBounds(int x, int y);
};