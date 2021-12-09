#pragma once

#include "base_viewport_controller.hpp"
#include "settings_editor.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "mesh_animation_editor.hpp"
#include "sprite_animation_editor.hpp"
#include "audio_editor.hpp"
#include "world_editor.hpp"
#include "script_editor.hpp"

class LeftViewportController final : public BaseViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// VOID
	void initialize() override;
	void update() override;

	// MISCELLANEOUS
	SettingsEditor& getSettingsEditor();
	SkyEditor& getSkyEditor();
	TerrainEditor& getTerrainEditor();
	WaterEditor& getWaterEditor();
	ModelEditor& getModelEditor();
	BillboardEditor& getBillboardEditor();
	MeshAnimationEditor& getMeshAnimationEditor();
	SpriteAnimationEditor& getSpriteAnimationEditor();
	AudioEditor& getAudioEditor();
	WorldEditor& getWorldEditor();
	ScriptEditor& getScriptEditor();

	// FVEC3
	static inline const fvec3 SCROLLING_LIST_COLOR = fvec3(0.25f);
	static inline const fvec3 BUTTON_COLOR = fvec3(0.1f, 0.1f, 1.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.5f, 0.5f, 1.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

private:
	// STRING
	string _lastActiveEditorScreen = "";

	// FVEC3
	static inline const fvec3 FRAME_COLOR = fvec3(0.175f);

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// MISCELLANEOUS
	SettingsEditor _settingsEditor;
	SkyEditor _skyEditor;
	TerrainEditor _terrainEditor;
	WaterEditor _waterEditor;
	ModelEditor _modelEditor;
	BillboardEditor _billboardEditor;
	MeshAnimationEditor _meshAnimationEditor;
	SpriteAnimationEditor _spriteAnimationEditor;
	AudioEditor _audioEditor;
	WorldEditor _worldEditor;
	ScriptEditor _scriptEditor;
};