#pragma once

#include <iostream>

// Forward declaration of 'Engine' class
class Engine;
class ProgramState
{
public:
	// For initialisation since child classes
	// must use a default constructor
	virtual void Init() {}
	// For deallocating memory without using
	// a destructor
	virtual void Cleanup() {}

	// May be used to 'freeze' a class' update
	// functions and resume them on command
	virtual void Pause() {}
	virtual void Resume() {}

	// Standard game loop functions
	virtual void HandleEvents(Engine* engine) {}
	virtual void Update(Engine* engine, float dt) {}
	virtual void Draw(Engine* engine) {}
};