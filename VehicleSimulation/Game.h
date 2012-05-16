#ifndef GAME_H
#define GAME_H

#include "main.h"

enum gameState{ Pause , On , Over , Start };

class Game
{

public:
	Game();
	bool Initialize();
	bool update(double passtime);
    bool draw();
	bool loadContent();
	bool unloadContent();
	bool handleInput();

private:
	gameState state;

};

#endif 
