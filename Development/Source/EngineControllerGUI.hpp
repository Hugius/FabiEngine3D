#pragma once
#include "FabiEngine3D.hpp"
#include "EngineGuiManager.hpp"

class EngineControllerGUI final : public FabiEngine3D
{
public:
	EngineControllerGUI();
	~EngineControllerGUI();

	void FE3D_CONTROLLER_INIT();
	void FE3D_CONTROLLER_UPDATE(float delta);
	void FE3D_CONTROLLER_DESTROY();

private:
	EngineGuiManager _guiManager;
};