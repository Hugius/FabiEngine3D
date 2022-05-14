#pragma once

#include "base_editor.hpp"

class TerrainEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedTerrains();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedTerrainIds() const;

	const bool loadTerrainsFromFile();
	const bool saveTerrainsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateDiffuseMapMenu();
	void _updateBlendMapMenu();
	void _updateNormalMapMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateTerrainCreating();
	void _updateTerrainChoosing();
	void _updateTerrainDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string GRID_ID = "@@grid";
	static inline const string GRID_MESH_PATH = "engine\\assets\\mesh\\plane.obj";
	static inline const string GRID_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\grid.tga";
	static inline const string BOX_ID = "@@box";
	static inline const string BOX_MESH_PATH = "engine\\assets\\mesh\\box.obj";
	static inline const string BOX_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\box.tga";

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 1024.0f;
	static inline constexpr float GRID_MIN_TEXTURE_ALPHA = 0.1f;
	static inline constexpr float GRID_LIGHTNESS = 0.25f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 1.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float COLOR_MULTIPLIER = 255.0f;

	static inline constexpr int GRID_REPEAT = 205;

	vector <string> _loadedTerrainIds = {};

	string _currentTerrainId = "";

	bool _isTerrainHovered = false;
};