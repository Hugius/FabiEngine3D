#pragma once

#include "base_editor.hpp"

class PointlightEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedPointlights();

	const vector<string> & getLoadedPointlightIds() const;

	const bool loadPointlightsFromFile();
	const bool savePointlightsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updatePointlightCreating();
	void _updatePointlightChoosing();
	void _updatePointlightDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string GRID_ID = "@@grid";
	static inline const string GRID_MESH_PATH = "engine\\assets\\mesh\\plane.obj";
	static inline const string GRID_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\grid.tga";
	static inline const string BOX_ID = "@@box";
	static inline const string BOX_MESH_PATH = "engine\\assets\\mesh\\box.obj";
	static inline const string BOX_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\box.tga";
	static inline const string LAMP_ID = "@@lamp";
	static inline const string LAMP_MESH_PATH = "engine\\assets\\mesh\\lamp.obj";
	static inline const string POINTLIGHT_TITLE_ID = "pointlight_title";

	static inline const fvec3 POINTLIGHT_POSITION = fvec3(0.0f, 2.0f, 0.0f);
	static inline const fvec3 LAMP_POSITION = fvec3(0.0f, 2.0f, 0.0f);
	static inline const fvec3 LAMP_SIZE = fvec3(0.5f);
	static inline const fvec3 DIRECTIONAL_LIGHTING_POSITION = fvec3(1000.0f);

	static inline const fvec2 POINTLIGHT_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 POINTLIGHT_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 50.0f;
	static inline constexpr float GRID_MIN_ALPHA = 0.1f;
	static inline constexpr float GRID_LIGHTNESS = 0.5f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.05f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float RADIUS_FACTOR = 100.0f;
	static inline constexpr float COLOR_FACTOR = 255.0f;
	static inline constexpr float INTENSITY_FACTOR = 100.0f;
	static inline constexpr float AMBIENT_LIGHTING_INTENSITY = 0.1f;
	static inline constexpr float DIRECTIONAL_LIGHTING_INTENSITY = 0.25f;
	static inline constexpr float SHADOW_LIGHTNESS = 0.25f;

	static inline constexpr int GRID_REPEAT = 10;
	static inline constexpr int ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline constexpr int SHADOW_QUALITY = 16384;

	vector<string> _loadedPointlightIds = {};

	string _currentPointlightId = "";
	string _hoveredPointlightId = "";
};