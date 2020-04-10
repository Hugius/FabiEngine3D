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
	shared_ptr<EngineGuiManager> _gui;

	float _delta = 0.0f;

	bool _creatingProject = false;
	bool _loadingProject = false;

	void _updateGuiInteraction();
	void _updateProjectCreation();
	void _updateProjectLoading();
};