#include "EngineGuiManager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	FE3D(fe3d)
{

}

void EngineGuiManager::load()
{

}

void EngineGuiManager::update(float delta)
{
	_delta = delta;
}

void EngineGuiManager::unload()
{

}