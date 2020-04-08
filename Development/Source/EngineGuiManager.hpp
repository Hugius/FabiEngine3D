#pragma once
#include "FabiEngine3D.hpp"

class EngineGuiManager
{
public:
	EngineGuiManager(FabiEngine3D& fe3d);

	void load();
	void update(float delta);
	void unload();

private:
	FabiEngine3D& FE3D;

	float _delta = 0.0f;
};