#pragma once
#include "FabiEngine3D.hpp"
#include "EngineGuiManager.hpp"

class EngineController final : public FabiEngine3D
{
public:
	EngineController();
	~EngineController();

	void FE3D_CONTROLLER_INIT();
	void FE3D_CONTROLLER_UPDATE(float delta);
	void FE3D_CONTROLLER_DESTROY();

private:
	EngineGuiManager _guiManager;
};