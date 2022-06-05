#pragma once

#include "base_editor.hpp"
#include "sky_editor.hpp"

class WaterEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<SkyEditor> skyEditor);
	void update();
	void deleteLoadedWaters();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedWaterIds() const;

	const bool loadWatersFromFile();
	const bool saveWatersToFile() const;

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
	void _updateWaterCreating();
	void _updateWaterChoosing();
	void _updateWaterDeleting();
	void _updateSkyChoosing();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string GRID_ID = "@@grid";
	static inline const string GRID_MESH_PATH = "engine\\assets\\mesh\\plane.obj";
	static inline const string GRID_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\grid.tga";
	static inline const string BOX_ID = "@@box";
	static inline const string BOX_MESH_PATH = "engine\\assets\\mesh\\box.obj";
	static inline const string BOX_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\box.tga";
	static inline const string WATER_TITLE_ID = "water_title";

	static inline const fvec3 DIRECTIONAL_LIGHTING_POSITION = fvec3(1000.0f);

	static inline const fvec2 WATER_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 WATER_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 1024.0f;
	static inline constexpr float GRID_MIN_ALPHA = 0.1f;
	static inline constexpr float GRID_LIGHTNESS = 0.75f;
	static inline constexpr float BOX_LIGHTNESS = 1.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 1.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float COLOR_FACTOR = 255.0f;
	static inline constexpr float LIGHTNESS_FACTOR = 100.0f;
	static inline constexpr float RIPPLE_SPEED_FACTOR = 100000.0f;
	static inline constexpr float WAVE_SPEED_FACTOR = 100000.0f;
	static inline constexpr float WAVE_HEIGHT_FACTOR = 100.0f;
	static inline constexpr float SPECULAR_INTENSITY_FACTOR = 100.0f;
	static inline constexpr float DISTORTION_SIZE_FACTOR = 100.0f;
	static inline constexpr float DISTORTION_FACTOR_FACTOR = 100.0f;
	static inline constexpr float AMBIENT_LIGHTING_INTENSITY = 0.1f;
	static inline constexpr float DIRECTIONAL_LIGHTING_INTENSITY = 1.0f;
	static inline constexpr float SHADOW_LIGHTNESS = 0.25f;
	static inline constexpr float SHADOW_BIAS = 0.000001f;

	static inline constexpr int GRID_REPEAT = 205;
	static inline constexpr int ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline constexpr int SHADOW_QUALITY = 16384;
	static inline constexpr int SHADOW_PCF_COUNT = 1;
	static inline constexpr int PLANAR_REFLECTION_QUALITY = 1024;
	static inline constexpr int PLANAR_REFRACTION_QUALITY = 1024;

	vector <string> _loadedWaterIds = {};

	shared_ptr<SkyEditor> _skyEditor = nullptr;

	string _currentWaterId = "";

	bool _isWaterHovered = false;
	bool _isSkyHovered = false;
};