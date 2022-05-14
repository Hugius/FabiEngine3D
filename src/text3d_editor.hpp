#pragma once

#include "base_editor.hpp"

class Text3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedText3ds();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedText3dIds() const;

	const bool loadText3dsFromFile();
	const bool saveText3dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateAabbMenu();
	void _updateText3dCreating();
	void _updateText3dChoosing();
	void _updateText3dDeleting();
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
	static inline constexpr float GRID_SIZE = 50.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.05f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float COLOR_MULTIPLIER = 255.0f;

	static inline constexpr int GRID_REPEAT = 10;

	vector<string> _loadedText3dIds = {};

	string _hoveredText3dId = "";
	string _currentText3dId = "";
};