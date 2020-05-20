#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"
#include "world_editor.hpp"

class TopViewportController final : public ViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, ModelEditor& modelEditor, WorldEditor& worldEditor);
	~TopViewportController() = default;

	void initialize() override;
	void update(float delta) override;

private:
	void _initializeProjectCreation();
	void _initializeProjectLoading();
	void _saveCurrentProject();
	void _updateProjectCreation();
	void _updateProjectLoading();

	ModelEditor& _modelEditor;
	WorldEditor& _worldEditor;

	string _currentProjectName = "";

	bool _creatingProject = false;
	bool _loadingProject = false;
	bool _savingProject = false;
	bool _openingDocs = false;
	bool _quittingEngine = false;
};