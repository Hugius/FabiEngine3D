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

class LeftViewportController final : public BaseViewportController
{
public:
	void initialize() override;
	void update() override;

	const shared_ptr<SkyEditor> getSkyEditor() const;
	const shared_ptr<TerrainEditor> getTerrainEditor() const;
	const shared_ptr<WaterEditor> getWaterEditor() const;
	const shared_ptr<ModelEditor> getModelEditor() const;
	const shared_ptr<BillboardEditor> getBillboardEditor() const;
	const shared_ptr<QuadEditor> getQuadEditor() const;
	const shared_ptr<Animation2dEditor> getAnimation2dEditor() const;
	const shared_ptr<Animation3dEditor> getAnimation3dEditor() const;
	const shared_ptr<SoundEditor> getSoundEditor() const;
	const shared_ptr<WorldEditor> getWorldEditor() const;
	const shared_ptr<ScriptEditor> getScriptEditor() const;

	static inline const fvec3 SCROLLING_LIST_COLOR = fvec3(0.25f);
	static inline const fvec3 BUTTON_COLOR = fvec3(0.1f, 0.1f, 1.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.5f, 0.5f, 1.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

private:
	string _lastActiveEditorScreen = "";

	static inline const fvec3 FRAME_COLOR = fvec3(0.175f);

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	shared_ptr<SkyEditor> _skyEditor;
	shared_ptr<TerrainEditor> _terrainEditor;
	shared_ptr<WaterEditor> _waterEditor;
	shared_ptr<ModelEditor> _modelEditor;
	shared_ptr<BillboardEditor> _billboardEditor;
	shared_ptr<QuadEditor> _quadEditor;
	shared_ptr<Animation2dEditor> _animation2dEditor;
	shared_ptr<Animation3dEditor> _animation3dEditor;
	shared_ptr<SoundEditor> _soundEditor;
	shared_ptr<WorldEditor> _worldEditor;
	shared_ptr<ScriptEditor> _scriptEditor;
};