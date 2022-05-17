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
	static inline const string CAPTOR_ID = "@@captor";
	static inline const string MODEL_TITLE_ID = "model_title";
	static inline const string AABB_TITLE_ID = "aabb_title";

	static inline const fvec3 CAPTOR_POSITION = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 DIRECTIONAL_LIGHTING_POSITION = fvec3(1000.0f);

	static inline const fvec2 MODEL_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 MODEL_TITLE_SIZE = fvec2(0.025f, 0.1f);
	static inline const fvec2 AABB_TITLE_POSITION = fvec2(0.0f, 0.75f);
	static inline const fvec2 AABB_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 50.0f;
	static inline constexpr float GRID_MIN_ALPHA = 0.1f;
	static inline constexpr float GRID_LIGHTNESS = 0.25f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.05f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr float COLOR_FACTOR = 255.0f;
	static inline constexpr float AMBIENT_LIGHTING_INTENSITY = 1.0f;
	static inline constexpr float DIRECTIONAL_LIGHTING_INTENSITY = 3.0f;
	static inline constexpr float SHADOW_LIGHTNESS = 0.25f;
	static inline constexpr float BLOOM_INTENSITY = 1.0f;
	static inline constexpr float POSITION_FACTOR = 100.0f;
	static inline constexpr float SIZE_FACTOR = 100.0f;
	static inline constexpr float SPECULAR_INTENSITY_FACTOR = 100.0f;
	static inline constexpr float REFLECTIVITY_FACTOR = 100.0f;
	static inline constexpr float REFRACTIVITY_FACTOR = 100.0f;
	static inline constexpr float EMISSION_INTENSITY_FACTOR = 100.0f;
	static inline constexpr float LIGHTNESS_FACTOR = 100.0f;
	static inline constexpr float OPACITY_FACTOR = 100.0f;
	static inline constexpr float MIN_ALPHA_FACTOR = 100.0f;

	static inline constexpr int GRID_REPEAT = 10;
	static inline constexpr int ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline constexpr int SHADOW_QUALITY = 16384;
	static inline constexpr int BLOOM_BLUR_COUNT = 5;
	static inline constexpr int BLOOM_QUALITY = 5;
	static inline constexpr int CUBE_REFLECTION_QUALITY = 1024;
	static inline constexpr int CUBE_REFRACTION_QUALITY = 1024;
	static inline constexpr int PLANAR_REFLECTION_QUALITY = 1024;
	static inline constexpr int PLANAR_REFRACTION_QUALITY = 1024;

	static inline constexpr BloomType BLOOM_TYPE = BloomType::PARTS;

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