/* NOTES 
* Using Multithreaded Debug DLL for Debug mode only to avoid
* LNK2019 Vector error
*/

#include "Engine.h"

// REMOVE after Debugging
#include <iostream>

// Define the width and height of the game
const sf::Uint32 WIDTH = 1280;
const sf::Uint32 HEIGHT = 720;

int main(int argc, char **argv)
{
	// Create an 'Engine' object for managing the game engine
	Engine engine(WIDTH, HEIGHT, "CS PROJECT");

	/* Initialise 'clock' and 'dt' for counting and tracking
	time between frames */
	sf::Clock clock;
	double dt;

	/* Start the game by loading the game state. This will be
	the main menu once this has been defined. */
	engine.ChangeState(STATE_MAINMENU);

	/* Start the game loop with the stopping condition of
	the engine's IsRunning flag */
	while (engine.IsRunning())
	{
		// Get time elapsed between frames
		dt = clock.restart().asSeconds();

		// Call procedures in game loop
		engine.HandleEvents();
		engine.Update(dt);
		engine.Draw();
	}

	return 0;
}