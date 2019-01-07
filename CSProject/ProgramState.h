#pragma once

#include <iostream>

class Engine;

class ProgramState
{
public:

	virtual void Init() {}
	virtual void Cleanup() {}

	virtual void Pause() {}
	virtual void Resume() {}

	virtual void HandleEvents(Engine* engine) {}
	virtual void Update(Engine* engine, double dt) {}
	virtual void Draw(Engine* engine) {}
};

