//main.cpp

#include <iostream>
#include "Game.h"

int main()
{

	Game creategame(900, 900, "game", 120);

	while (!creategame.quit()) {
		creategame.update();
		creategame.render();
	}
}


