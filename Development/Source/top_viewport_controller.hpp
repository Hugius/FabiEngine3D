#pragma once

#include "base_viewport_controller.hpp"
#include "environment_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "scene_editor.hpp"
#include "script_editor.hpp"
#include "audio_editor.hpp"
#include "settings_editor.hpp"

#define TVPC TopViewportController

class TopViewportController final : public BaseViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, 
		EnvironmentEditor& environmentEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor, 
		SceneEditor& sceneEditor, AnimationEditor& animationEditor, ScriptEditor& scriptEditor, 
		AudioEditor& audioEditor, SettingsEditor& settingsEditor);

	void initialize() override;
	void update() override;

	bool isScriptRunning();

	const string& getCurrentProjectName();

	static inline const Vec3 FRAME_COLOR = Vec3(0.25f);
	static inline const Vec3 BUTTON_COLOR = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 BUTTON_HOVER_COLOR = Vec3(0.0f, 0.5f, 0.0f);
	static inline const Vec3 TEXT_COLOR = Vec3(1.0f);
	static inline const Vec3 TEXT_HOVER_COLOR = Vec3(0.0f);

private:
	void _updateProjectScreenManagement();
	void _updateGameScreenManagement();
	void _updateMiscScreenManagement();
	void _updateMiscellaneous();
	void _updateProjectCreation();
	void _updateProjectLoading();
	void _updateProjectDeletion();
	void _prepareProjectLoading();
	void _saveCurrentProject();
	void _applyProjectChange();
	bool _isProjectCorrupted(const string& projectName);

	EnvironmentEditor& _environmentEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	AnimationEditor& _animationEditor;
	AudioEditor& _audioEditor;
	SceneEditor& _sceneEditor;
	ScriptEditor& _scriptEditor;
	SettingsEditor& _settingsEditor;

	shared_ptr<EngineGuiWindow> _projectWindow = nullptr;
	shared_ptr<EngineGuiWindow> _gameWindow = nullptr;
	shared_ptr<EngineGuiWindow> _miscWindow = nullptr;

	string _currentProjectID = "";

	bool _creatingProject = false;
	bool _loadingProject = false;
	bool _deletingProject = false;
};