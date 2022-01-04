#pragma once

#include "base_viewport_controller.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "quad_editor.hpp"
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
						  SkyEditor& skyEditor,
						  TerrainEditor& terrainEditor,
						  WaterEditor& waterEditor,
						  ModelEditor& modelEditor,
						  BillboardEditor& billboardEditor,
						  QuadEditor& quadEditor,
						  Animation2dEditor& animation2dEditor,
						  Animation3dEditor& animation3dEditor,
						  SoundEditor& soundEditor,
						  WorldEditor& worldEditor,
						  ScriptEditor& scriptEditor);

	void initialize() override;
	void update() override;

	const bool isScriptStarted() const;
	const bool isScriptRunning() const;
	const bool isProjectCorrupted(const string& projectDirectoryPath) const;

	static inline const fvec3 BUTTON_COLOR = fvec3(0.0f, 0.1f, 0.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

private:
	void _updateProjectScreenManagement();
	void _updateGameScreenManagement();
	void _updateMiscScreenManagement();
	void _updateMiscellaneous();
	void _updateProjectCreating();
	void _updateProjectLoading();
	void _updateProjectDeleting();
	void _saveCurrentProject();
	void _applyProjectChange();

	const bool _prepareProjectChoosing(const string& title) const;

	string _currentProjectID = "";

	static inline const fvec3 FRAME_COLOR = fvec3(0.075f);

	bool _isCreatingProject = false;
	bool _isLoadingProject = false;
	bool _isDeletingProject = false;

	SkyEditor& _skyEditor;
	TerrainEditor& _terrainEditor;
	WaterEditor& _waterEditor;
	ModelEditor& _modelEditor;
	BillboardEditor& _billboardEditor;
	QuadEditor& _quadEditor;
	Animation2dEditor& _animation2dEditor;
	Animation3dEditor& _animation3dEditor;
	SoundEditor& _soundEditor;
	WorldEditor& _worldEditor;
	ScriptEditor& _scriptEditor;
};