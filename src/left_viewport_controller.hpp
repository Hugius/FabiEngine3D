#pragma once

#include "base_viewport_controller.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "world_editor.hpp"
#include "animation_editor.hpp"
#include "script_editor.hpp"
#include "audio_editor.hpp"
#include "settings_editor.hpp"

class LeftViewportController final : public BaseViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	void initialize() override;
	void update() override;

	// Miscellaneous
	SkyEditor& getSkyEditor();
	TerrainEditor& getTerrainEditor();
	WaterEditor& getWaterEditor();
	ModelEditor& getModelEditor();
	AnimationEditor& getAnimationEditor();
	BillboardEditor& getBillboardEditor();
	AudioEditor& getAudioEditor();
	WorldEditor& getWorldEditor();
	ScriptEditor& getScriptEditor();
	SettingsEditor& getSettingsEditor();

	// Vectors
	static inline const fvec3 SCROLLING_LIST_COLOR = fvec3(0.25f);
	static inline const fvec3 BUTTON_COLOR = fvec3(0.1f, 0.1f, 1.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.5f, 0.5f, 1.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

private:
	// Strings
	string _lastActiveEditorScreen = "";

	// Vectors
	static inline const fvec3 FRAME_COLOR = fvec3(0.175f);

	// Decimals
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// Miscellaneous
	SkyEditor _skyEditor;
	TerrainEditor _terrainEditor;
	WaterEditor _waterEditor;
	ModelEditor _modelEditor;
	AnimationEditor _animationEditor;
	BillboardEditor _billboardEditor;
	AudioEditor _audioEditor;
	WorldEditor _worldEditor;
	ScriptEditor _scriptEditor;
	SettingsEditor _settingsEditor;
};