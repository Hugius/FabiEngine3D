#pragma once

#include "base_editor.hpp"
#include "reflection_type.hpp"

class ModelEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void setCurrentProjectId(const string& projectId);
	void load();
	void unload();
	void update();

	const vector<string> getMeshPathsFromFile() const;
	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedIds();

	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
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

	vector<string> _loadedModelIds;
	string _currentModelId = "";
	string _currentPartId = "";
	string _currentAabbId = "";
	string _hoveredModelId = "";
	string _hoveredPartId = "";
	string _hoveredAabbId = "";

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 0.001f;
	static inline constexpr float GRID_SIZE = 60.0f;
	static inline constexpr float GRID_REPEAT = 6.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;
	float _originalPartOpacity = 0.0f;

	int _selectedPartHighlightDirection = 1;

	bool _isCreatingModel = false;
	bool _isChoosingModel = false;
	bool _isDeletingModel = false;
	bool _isChoosingPart = false;
	bool _isCreatingAabb = false;
	bool _isChoosingAabb = false;
	bool _isDeletingAabb = false;
};