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

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 1024.0f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 1.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float COLOR_MULTIPLIER = 255.0f;

	static inline constexpr int GRID_REPEAT = 205;

	vector <string> _loadedWaterIds = {};

	shared_ptr<SkyEditor> _skyEditor = nullptr;

	string _currentWaterId = "";

	bool _isWaterHovered = false;
	bool _isSkyHovered = false;
};