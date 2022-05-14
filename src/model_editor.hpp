#pragma once

#include "base_editor.hpp"
#include "sky_editor.hpp"

class ModelEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<SkyEditor> skyEditor);
	void update();
	void deleteLoadedModels();

	const vector<string> getMeshPathsFromFile() const;
	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedModelIds() const;

	const bool loadModelsFromFile();
	const bool saveModelsToFile() const;

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
	void _updateMainAabbMenu();
	void _updateChoiceAabbMenu();
	void _updateModelCreating();
	void _updateModelChoosing();
	void _updateModelDeleting();
	void _updatePartChoosing();
	void _updateAabbCreating();
	void _updateAabbChoosing();
	void _updateAabbDeleting();
	void _updateSkyChoosing();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string GRID_ID = "@@grid";
	static inline const string GRID_MESH_PATH = "engine\\assets\\mesh\\plane.obj";
	static inline const string GRID_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\grid.tga";
	static inline const string BOX_ID = "@@box";
	static inline const string BOX_MESH_PATH = "engine\\assets\\mesh\\box.obj";
	static inline const string BOX_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\box.tga";
	static inline const string AABB_TEXT_ID = "@@aabb";

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 50.0f;
	static inline constexpr float GRID_MIN_TEXTURE_ALPHA = 0.1f;
	static inline constexpr float GRID_LIGHTNESS = 0.25f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.05f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float COLOR_MULTIPLIER = 255.0f;

	static inline constexpr int GRID_REPEAT = 10;

	vector<string> _loadedModelIds = {};

	shared_ptr<SkyEditor> _skyEditor = nullptr;

	string _currentModelId = "";
	string _currentPartId = "";
	string _currentAabbId = "";
	string _hoveredModelId = "";
	string _hoveredPartId = "";
	string _hoveredAabbId = "";

	float _originalPartOpacity = 0.0f;

	int _selectedPartHighlightDirection = 1;

	bool _isSkyHovered = false;
};