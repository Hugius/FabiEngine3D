#pragma once

#include "base_viewport_controller.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "image_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "sound_editor.hpp"
#include "world_editor.hpp"
#include "script_editor.hpp"

class LeftViewportController final : public BaseViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, GuiManager& gui);

	// VOID
	void initialize() override;
	void update() override;

	// MISCELLANEOUS
	SkyEditor& getSkyEditor();
	TerrainEditor& getTerrainEditor();
	WaterEditor& getWaterEditor();
	ModelEditor& getModelEditor();
	BillboardEditor& getBillboardEditor();
	ImageEditor& getImageEditor();
	Animation2dEditor& getAnimation2dEditor();
	Animation3dEditor& getAnimation3dEditor();
	SoundEditor& getSoundEditor();
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
	SkyEditor _skyEditor;
	TerrainEditor _terrainEditor;
	WaterEditor _waterEditor;
	ModelEditor _modelEditor;
	BillboardEditor _billboardEditor;
	ImageEditor _imageEditor;
	Animation2dEditor _animation2dEditor;
	Animation3dEditor _animation3dEditor;
	SoundEditor _soundEditor;
	WorldEditor _worldEditor;
	ScriptEditor _scriptEditor;
};