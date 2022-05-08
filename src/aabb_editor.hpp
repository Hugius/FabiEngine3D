#pragma once

#include "base_editor.hpp"

class AabbEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedAabbs();

	const vector<string> & getLoadedAabbIds() const;

	const bool loadAabbsFromFile();
	const bool saveAabbsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateAabbCreating();
	void _updateAabbChoosing();
	void _updateAabbDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

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

	vector<string> _loadedAabbIds = {};

	string _hoveredAabbId = "";
	string _currentAabbId = "";
};