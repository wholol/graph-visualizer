#pragma once
#include "Location.h"
#include <vector>
#include "Grid.h"
//base class for all algorithms. useful for factory pattern.
class Algorithm {
public:
	virtual void SolveAlgorithm(const Location& srcpos, const Location& targetpos, const std::vector<Location>& obstacles, Grid &grid, sf::RenderWindow& createwindow) = 0;
	virtual void constructPath(Grid& grid) = 0;
};