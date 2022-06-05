#pragma once

#include "base_editor.hpp"

class Quad3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedQuad3ds();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedQuad3dIds() const;

	const bool loadQuad3dsFromFile();
	const bool saveQuad3dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateTexturingMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateAabbMenu();
	void _updateQuad3dCreating();
	void _updateQuad3dChoosing();
	void _updateQuad3dDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string GRID_ID = "@@grid";
	static inline const string GRID_MESH_PATH = "engine\\assets\\mesh\\plane.obj";
	static inline const string GRID_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\grid.tga";
	static inline const string BOX_ID = "@@box";
	static inline const string BOX_MESH_PATH = "engine\\assets\\mesh\\box.obj";
	static inline const string BOX_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\box.tga";
	static inline const string QUAD3D_TITLE_ID = "quad3d_title";

	static inline const fvec3 DIRECTIONAL_LIGHTING_POSITION = fvec3(1000.0f);

	static inline const fvec2 QUAD3D_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 QUAD3D_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 50.0f;
	static inline constexpr float GRID_MIN_ALPHA = 0.1f;
	static inline constexpr float GRID_LIGHTNESS = 0.75f;
	static inline constexpr float BOX_LIGHTNESS = 1.5f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.05f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float COLOR_FACTOR = 255.0f;
	static inline constexpr float EMISSION_INTENSITY_FACTOR = 100.0f;
	static inline constexpr float LIGHTNESS_FACTOR = 100.0f;
	static inline constexpr float SIZE_FACTOR = 100.0f;
	static inline constexpr float OPACITY_FACTOR = 100.0f;
	static inline constexpr float MIN_ALPHA_FACTOR = 100.0f;
	static inline constexpr float AMBIENT_LIGHTING_INTENSITY = 0.1f;
	static inline constexpr float DIRECTIONAL_LIGHTING_INTENSITY = 1.0f;
	static inline constexpr float SHADOW_LIGHTNESS = 0.25f;
	static inline constexpr float SHADOW_BIAS = 0.000001f;
	static inline constexpr float BLOOM_INTENSITY = 1.0f;

	static inline constexpr int GRID_REPEAT = 10;
	static inline constexpr int ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline constexpr int SHADOW_QUALITY = 16384;
	static inline constexpr int SHADOW_PCF_COUNT = 1;
	static inline constexpr int BLOOM_BLUR_COUNT = 5;
	static inline constexpr int BLOOM_QUALITY = 5;

	static inline constexpr BloomType BLOOM_TYPE = BloomType::PARTS;

	vector<string> _loadedQuad3dIds = {};

	string _currentQuad3dId = "";
	string _hoveredQuad3dId = "";
};