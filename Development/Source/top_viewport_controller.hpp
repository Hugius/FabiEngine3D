#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"
#include "environment_editor.hpp"
#include "billboard_editor.hpp"
#include "scene_editor.hpp"
#include "script_editor.hpp"

#define TVPC TopViewportController

class TopViewportController final : public ViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, 
		ModelEditor& modelEditor, EnvironmentEditor& environmentEditor, BillboardEditor& billboardEditor, SceneEditor& sceneEditor, ScriptEditor& scriptEditor);
	~TopViewportController() = default;

	void initialize() override;
	void update() override;

	bool isScriptRunning();

	static inline const vec3 frameColor = vec3(0.25f);
	static inline const vec3 buttonColor = vec3(0.0f, 0.25f, 0.0f);
	static inline const vec3 buttonHoverColor = vec3(0.0f, 0.5f, 0.0f);
	static inline const vec3 textColor = vec3(1.0f);
	static inline const vec3 textHoverColor = vec3(0.0f);

private:
	void _updateProjectManagement();
	void _updateGameManagement();
	void _updateMiscellaneous();
	void _updateProjectCreation();
	void _updateProjectLoading();
	void _updateProjectDeletion();
	void _prepareProjectChoosing();
	void _saveCurrentProject();
	void _updateCurrentProject();

	ModelEditor& _modelEditor;
	EnvironmentEditor& _environmentEditor;
	BillboardEditor& _billboardEditor;
	SceneEditor& _sceneEditor;
	ScriptEditor& _scriptEditor;

	shared_ptr<EngineGuiWindow> _projectWindow = nullptr;
	shared_ptr<EngineGuiWindow> _gameWindow = nullptr;

	string _currentProjectName = "";

	bool _creatingProject = false;
	bool _loadingProject = false;
	bool _deletingProject = false;
};