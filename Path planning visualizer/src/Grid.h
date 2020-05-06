#pragma once
#include <SFML\Graphics.hpp>
#include "Location.h"

//grid class
class Grid {
public:
	Grid(int screenwidth, int screenheight,const sf::Mouse& mouse, sf::RenderWindow& createwindow);
	void drawGrid();
	void drawPath();
	void setObstacle();
	void setTarget();
	void setSource();
	void ColourVisitedTile(const Location& loc);
	void ColourVisitingTile(const Location& loc);
	void ColourPathTile(const Location& loc_1, const Location& loc_2);
	void resetGrid();			//reset grid to default state
	std::vector<Location> getObstacleLocation() const;
	std::tuple<int, int> getTileNums() const;
	Location getTargetPos() const;
	Location getSrcPos() const;

private:
	std::vector<sf::RectangleShape> TileMap;
	std::vector<Location> Obstacles;		//store obstacle locations
	
	const sf::Mouse& mouse;
	sf::RenderWindow& createwindow;
	
	static constexpr int TileDimension = 30;		//dimension of tile
	static constexpr int OutlineThickness = 2;
	
	const int screenwidth;
	const int screenheight;
	
	int NumTilesX;										//number of tiles in X direction
	int NumTilesY;										//number of tiles in Y direction
	
	Location srcpos;							//initialize src location
	Location targetpos;		//initialzie target position
	
	sf::Color openTileColour = sf::Color::White;
	sf::Color obstacleTileColour = sf::Color::Black;
	sf::Color srcTileColour = sf::Color::Red;
	sf::Color targetTileColour = sf::Color(255,69,0);		//orange colour 
	sf::Color visitedTileColour = sf::Color::Blue;
	sf::Color visitngTileColour = sf::Color::Cyan;


	std::vector<sf::Vertex> vertices;

	bool changingSrcPos = false;
	bool changingTargetPos = false;

	/*helper methods*/
	void updateSrcPos(const Location& loc);			//update source position
	void updateTargetPos(const Location& loc);		//update target position
	sf::Color getTileColor(const Location& loc) const;
	void setTileColor(const Location& loc,const sf::Color& color);
	bool outofBounds(int x, int y);
};