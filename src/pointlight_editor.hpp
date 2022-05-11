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

	static inline const string POINTLIGHT_MODEL_ID = "@@pointlight";
	static inline const string POINTLIGHT_MODEL_PATH = "engine\\assets\\mesh\\lamp.obj";

	static inline const fvec3 POINTLIGHT_POSITION = fvec3(0.0f, 2.0f, 0.0f);

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 50.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.05f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float RADIUS_MULTIPLIER = 100.0f;
	static inline constexpr float COLOR_MULTIPLIER = 255.0f;
	static inline constexpr float INTENSITY_MULTIPLIER = 100.0f;

	static inline constexpr int GRID_REPEAT = 10;

	vector<string> _loadedPointlightIds = {};

	string _hoveredPointlightId = "";
	string _currentPointlightId = "";
};