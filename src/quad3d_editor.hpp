#pragma once

#include "base_editor.hpp"

class Quad3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedQuad3ds();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedQuad3dIds() const;

	const bool loadQuad3dsFromFile();
	const bool saveQuad3dsToFile() const;

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
	void _updateAabbMenu();
	void _updateQuad3dCreating();
	void _updateQuad3dChoosing();
	void _updateQuadDeleting();
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

	static inline constexpr int GRID_REPEAT = 10;

	vector<string> _loadedQuad3dIds = {};

	string _hoveredQuad3dId = "";
	string _currentQuad3dId = "";
};