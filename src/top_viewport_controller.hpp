#pragma once

#include "base_viewport_controller.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "audio_editor.hpp"
#include "world_editor.hpp"
#include "script_editor.hpp"
#include "settings_editor.hpp"

class TopViewportController final : public BaseViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui,
						  SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor,
						  AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor,
						  WorldEditor& worldEditor, ScriptEditor& scriptEditor, SettingsEditor& settingsEditor);

	// Voids
	void initialize() override;
	void update() override;

	// Booleans
	const bool isScriptStarted() const;
	const bool isScriptRunning() const;
	const bool isProjectCorrupted(const string& projectDirectoryPath) const;

	// Vectors
	static inline const Vec3 BUTTON_COLOR = Vec3(0.0f, 0.1f, 0.0f);
	static inline const Vec3 BUTTON_HOVER_COLOR = Vec3(0.0f, 1.0f, 0.0f);
	static inline const Vec3 TEXT_COLOR = Vec3(1.0f);
	static inline const Vec3 TEXT_HOVER_COLOR = Vec3(0.0f);

private:
	// Voids
	void _updateProjectScreenManagement();
	void _updateGameScreenManagement();
	void _updateMiscScreenManagement();
	void _updateMiscellaneous();
	void _updateProjectCreating();
	void _updateProjectLoading();
	void _updateProjectDeleting();
	void _saveCurrentProject();
	void _applyProjectChange();

	// Booleans
	const bool _prepareProjectChoosing(const string& title) const;

	// Strings
	string _currentProjectID = "";

	// Vectors
	static inline const Vec3 FRAME_COLOR = Vec3(0.075f);

	// Booleans
	bool _isCreatingProject = false;
	bool _isLoadingProject = false;
	bool _isDeletingProject = false;

	// Miscellaneous
	SkyEditor& _skyEditor;
	TerrainEditor& _terrainEditor;
	WaterEditor& _waterEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	AnimationEditor& _animationEditor;
	AudioEditor& _audioEditor;
	WorldEditor& _worldEditor;
	ScriptEditor& _scriptEditor;
	SettingsEditor& _settingsEditor;
	shared_ptr<EngineGuiWindow> _projectWindow = nullptr;
	shared_ptr<EngineGuiWindow> _gameWindow = nullptr;
	shared_ptr<EngineGuiWindow> _miscWindow = nullptr;
};