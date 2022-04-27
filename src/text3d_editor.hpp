#pragma once

#include "base_editor.hpp"

class Text3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedEntities();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedEntityIds() const;

	const bool loadEntitiesFromFile();
	const bool saveEntitiesToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateTextCreating();
	void _updateTextChoosing();
	void _updateTextDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string TEXT_CONTENT = "Text123";

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 0.001f;
	static inline constexpr float GRID_SIZE = 100.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.125f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;

	static inline constexpr int GRID_REPEAT = 25;

	vector<string> _loadedEntityIds = {};

	string _hoveredTextId = "";
	string _currentTextId = "";
};