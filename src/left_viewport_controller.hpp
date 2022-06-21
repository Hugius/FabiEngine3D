#pragma once

#include "base_viewport_controller.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "quad3d_editor.hpp"
#include "quad2d_editor.hpp"
#include "text3d_editor.hpp"
#include "text2d_editor.hpp"

class LeftViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::inject;

	void inject(shared_ptr<SkyEditor> skyEditor);
	void inject(shared_ptr<TerrainEditor> terrainEditor);
	void inject(shared_ptr<WaterEditor> waterEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void inject(shared_ptr<Quad3dEditor> quad3dEditor);
	void inject(shared_ptr<Quad2dEditor> quad2dEditor);
	void inject(shared_ptr<Text3dEditor> text3dEditor);
	void inject(shared_ptr<Text2dEditor> text2dEditor);
	void initialize();
	void update();

private:
	static inline const fvec3 FRAME_COLOR = fvec3(0.5f);
	static inline const fvec3 BUTTON_COLOR = fvec3(0.4f, 0.4f, 1.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.8f, 0.8f, 1.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

	static inline constexpr float CW = 0.11f;
	static inline constexpr float CH = 0.085f;

	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Quad2dEditor> _quad2dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Text2dEditor> _text2dEditor = nullptr;
};