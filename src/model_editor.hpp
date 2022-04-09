#pragma once

#include "base_editor.hpp"
#include "reflection_type.hpp"

class ModelEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedEntities();

	const vector<string> getMeshPathsFromFile() const;
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
	void _updateCamera();
	void _updateMiscellaneous();

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 0.001f;
	static inline constexpr float GRID_SIZE = 100.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;

	static inline constexpr unsigned int GRID_REPEAT = 10;

	vector<string> _loadedEntityIds = {};

	string _currentModelId = "";
	string _currentPartId = "";
	string _currentAabbId = "";
	string _hoveredModelId = "";
	string _hoveredPartId = "";
	string _hoveredAabbId = "";

	float _originalPartOpacity = 0.0f;

	int _selectedPartHighlightDirection = 1;
};