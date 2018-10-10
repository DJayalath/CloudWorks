/* NOTES 
* Using Multithreaded Debug DLL for Debug mode only to avoid
* LNK2019 Vector error
*/

#include "Engine.h"

// REMOVE after Debugging
#include <iostream>

const sf::Uint32 WIDTH = 1280;
const sf::Uint32 HEIGHT = 720;

int main(int argc, char **argv)
{
	Engine engine(WIDTH, HEIGHT, "CS PROJECT");

	engine.Start();

	return 0;
}