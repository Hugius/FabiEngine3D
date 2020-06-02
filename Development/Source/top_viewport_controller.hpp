#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"
#include "world_editor.hpp"
#include "billboard_editor.hpp"

class TopViewportController final : public ViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, 
		ModelEditor& modelEditor, WorldEditor& worldEditor, BillboardEditor& billboardEditor);
	~TopViewportController() = default;

	void initialize() override;
	void update() override;

private:
	void _initializeProjectLoading();
	void _saveCurrentProject();
	void _updateProjectCreation();
	void _updateProjectLoading();

	ModelEditor& _modelEditor;
	WorldEditor& _worldEditor;
	BillboardEditor& _billboardEditor;

	string _currentProjectName = "";

	bool _creatingProject = false;
	bool _loadingProject = false;
};