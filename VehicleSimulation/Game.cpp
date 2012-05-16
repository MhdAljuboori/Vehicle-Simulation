#include "GAME.h"

//////// Costructor /////////
Game::Game()
{
	state = Start ;

}

///////  initialize for first time  //////////
bool Game::Initialize()
{
	state = Start;

	return 1;
}

/////// load everything here //////////
bool Game::loadContent()
{
	
	return 1;
}

////// unload anything  here //////////
bool Game::unloadContent()
{

	return 1;
}

//////// update gamelogic and physics ////////
bool Game::update(double passtime)
{
    /////////  update game when it's start  ///////////////
	if(state == Start)
	{
	
	}

    /////////  update game when it's on  ///////////////
	if(state == On)
	{

	}

	/////////  update game when it's over  ///////////////
	if(state == Over)
	{

	}

	/////////  update game when it's pause  ///////////////
	if(state == Pause)
	{

	}
	return 1;
}

///////// draw game ////////////////
bool Game::draw()
{
	return 1;

}

///////  handle input //////////////
bool Game::handleInput()
{

	return 1;
}