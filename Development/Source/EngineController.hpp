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

	string _currentProject = "";

	void _updateGuiInteraction();

	void _updateTopViewport();
	void _updateLeftViewport();
	void _updateRightViewport();
	void _updateBottomViewport();

	// Top viewport
	bool _creatingProject = false;
	bool _loadingProject = false;
	bool _savingProject = false;
	bool _openingDocs = false;
	bool _quittingEngine = false;
	void _updateProjectCreation();
	void _updateProjectLoading();
	void _updateProjectSaving();
	void _updateDocsOpening();
	void _updateEngineQuitting();
	
	// Left viewport
	bool _modelEditorEnabled = false;
	bool _worldlEditorEnabled = false;
	bool _placingEditorEnabled = false;
	bool _lightingEditorEnabled = false;
	bool _scriptEditorEnabled = false;
	void _updateModelEditor();
	void _updateWorldEditor();
	void _updatePlacingEditor();
	void _updateLightingEditor();
	void _updateScriptEditor();

	// Right viewport

	// Bottom viewport
};