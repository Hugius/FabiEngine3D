#pragma once
#include "FabiEngine3D.hpp"
#include "EngineGuiManager.hpp"
#include "TopViewportController.hpp"
#include "LeftViewportController.hpp"
#include "RightViewportController.hpp"
#include "BottomViewportController.hpp"

class EngineController final : public FabiEngine3D
{
public:
	EngineController();
	~EngineController();

	void FE3D_CONTROLLER_INIT();
	void FE3D_CONTROLLER_UPDATE(float delta);
	void FE3D_CONTROLLER_DESTROY();

private:
	shared_ptr<EngineGuiManager> _gui;

	float _delta = 0.0f;

	string _currentProject = "";
	
	TopViewportController _topViewportController;
	LeftViewportController _leftViewportController;
	RightViewportController _rightViewportController;
	BottomViewportController _bottomViewportController;
};