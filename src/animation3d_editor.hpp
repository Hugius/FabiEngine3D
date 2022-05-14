#pragma once

#include "base_editor.hpp"
#include "animation3d.hpp"
#include "model_editor.hpp"

class Animation3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<ModelEditor> modelEditor);

	void update();
	void deleteLoadedAnimation3ds();

	const vector<string> & getLoadedAnimation3dIds() const;

	const bool loadAnimation3dsFromFile();
	const bool saveAnimation3dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateFrameMenu();
	void _updateAnimation3dCreating();
	void _updateAnimation3dChoosing();
	void _updateAnimation3dDeleting();
	void _updateModelChoosing();
	void _updatePartChoosing();
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
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;

	static inline constexpr int GRID_REPEAT = 10;
	static inline constexpr int MAX_FRAME_COUNT = 100;

	vector<string> _loadedAnimation3dIds = {};

	shared_ptr<ModelEditor> _modelEditor = nullptr;

	string _currentAnimation3dId = "";
	string _currentPartId = "";
	string _hoveredModelId = "";
	string _hoveredPartId = "";
	string _previewModelId = "";

	fvec3 _initialModelSize = fvec3(0.0f);

	float _originalPartOpacity = 0.0f;

	int _currentFrameIndex = 0;
	int _selectedPartHighlightDirection = 1;

	bool _mustUpdateCurrentFramePreview = true;
};