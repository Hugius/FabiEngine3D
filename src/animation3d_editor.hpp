#pragma once

#include "base_editor.hpp"
#include "animation3d.hpp"
#include "model_editor.hpp"

class Animation3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<ModelEditor> modelEditor);
	void deleteLoadedAnimation3ds();

	const vector<string> & getLoadedAnimation3dIds() const;

	const bool loadAnimation3dsFromFile();
	const bool saveAnimation3dsToFile() const;

private:
	void _load();
	void _update();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateFrameMenu();
	void _updateAnimation3dCreating();
	void _updateAnimation3dChoosing();
	void _updateAnimation3dDeleting();
	void _updatePartCreating();
	void _updatePartChoosing();
	void _updateModelChoosing();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string GRID_ID = "@@grid";
	static inline const string GRID_MESH_PATH = "engine\\assets\\mesh\\plane.obj";
	static inline const string GRID_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\grid.tga";
	static inline const string BOX_ID = "@@box";
	static inline const string BOX_MESH_PATH = "engine\\assets\\mesh\\box.obj";
	static inline const string BOX_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\box.tga";
	static inline const string CAPTOR_ID = "@@captor";
	static inline const string ANIMATION3D_TITLE_ID = "animation3d_title";
	static inline const string FRAME_TITLE_ID = "frame_title";

	static inline const fvec3 CAPTOR_POSITION = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 DIRECTIONAL_LIGHTING_POSITION = fvec3(1000.0f);

	static inline const fvec2 ANIMATION3D_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 ANIMATION3D_TITLE_SIZE = fvec2(0.025f, 0.1f);
	static inline const fvec2 FRAME_TITLE_POSITION = fvec2(0.0f, 0.75f);
	static inline const fvec2 FRAME_TITLE_SIZE = fvec2(0.025f, 0.1f);

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
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float AMBIENT_LIGHTING_INTENSITY = 0.1f;
	static inline constexpr float DIRECTIONAL_LIGHTING_INTENSITY = 1.0f;
	static inline constexpr float SHADOW_LIGHTNESS = 0.25f;
	static inline constexpr float SHADOW_BIAS = 0.000001f;
	static inline constexpr float BLOOM_INTENSITY = 1.0f;
	static inline constexpr float SPEED_FACTOR = 10000.0f;
	static inline constexpr float ROTATION_ORIGIN_FACTOR = 100.0f;
	static inline constexpr float MOVEMENT_FACTOR = 100.0f;
	static inline constexpr float ROTATION_FACTOR = 1.0f;
	static inline constexpr float SCALING_FACTOR = 100.0f;

	static inline constexpr int GRID_REPEAT = 10;
	static inline constexpr int MAX_FRAME_COUNT = 100;
	static inline constexpr int ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline constexpr int SHADOW_QUALITY = 16384;
	static inline constexpr int SHADOW_PCF_COUNT = 1;
	static inline constexpr int BLOOM_BLUR_COUNT = 5;
	static inline constexpr int BLOOM_QUALITY = 5;
	static inline constexpr int PLANAR_REFLECTION_QUALITY = 1024;
	static inline constexpr int PLANAR_REFRACTION_QUALITY = 1024;

	static inline constexpr BloomType BLOOM_TYPE = BloomType::PARTS;

	vector<string> _loadedAnimation3dIds = {};

	shared_ptr<ModelEditor> _modelEditor = nullptr;

	string _currentAnimation3dId = "";
	string _currentPartId = "";
	string _hoveredModelId = "";
	string _hoveredPartId = "";
	string _previewModelId = "";

	fvec3 _originalModelSize = fvec3(0.0f);

	float _originalPartOpacity = 0.0f;

	int _currentFrameIndex = 0;
	int _selectedPartHighlightDirection = 1;

	bool _mustUpdateCurrentFramePreview = true;
};