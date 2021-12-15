#pragma once

#include "base_viewport_controller.hpp"
#include "settings_editor.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "sound_editor.hpp"
#include "world_editor.hpp"
#include "script_editor.hpp"

class TopViewportController final : public BaseViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d,
						  GuiManager& gui,
						  SettingsEditor& settingsEditor,
						  SkyEditor& skyEditor,
						  TerrainEditor& terrainEditor,
						  WaterEditor& waterEditor,
						  ModelEditor& modelEditor,
						  BillboardEditor& billboardEditor,
						  Animation3dEditor& animation3dEditor,
						  Animation2dEditor& animation2dEditor,
						  SoundEditor& soundEditor,
						  WorldEditor& worldEditor,
						  ScriptEditor& scriptEditor);

	// VOID
	void initialize() override;
	void update() override;

	// BOOL
	const bool isScriptStarted() const;
	const bool isScriptRunning() const;
	const bool isProjectCorrupted(const string& projectDirectoryPath) const;

	// FVEC3
	static inline const fvec3 BUTTON_COLOR = fvec3(0.0f, 0.1f, 0.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

private:
	// VOID
	void _updateProjectScreenManagement();
	void _updateGameScreenManagement();
	void _updateMiscScreenManagement();
	void _updateMiscellaneous();
	void _updateProjectCreating();
	void _updateProjectLoading();
	void _updateProjectDeleting();
	void _saveCurrentProject();
	void _applyProjectChange();

	// BOOL
	const bool _prepareProjectChoosing(const string& title) const;

	// STRING
	string _currentProjectID = "";

	// FVEC3
	static inline const fvec3 FRAME_COLOR = fvec3(0.075f);

	// BOOL
	bool _isCreatingProject = false;
	bool _isLoadingProject = false;
	bool _isDeletingProject = false;

	// MISCELLANEOUS
	SettingsEditor& _settingsEditor;
	SkyEditor& _skyEditor;
	TerrainEditor& _terrainEditor;
	WaterEditor& _waterEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	Animation3dEditor& _animation3dEditor;
	Animation2dEditor& _animation2dEditor;
	SoundEditor& _soundEditor;
	WorldEditor& _worldEditor;
	ScriptEditor& _scriptEditor;
};