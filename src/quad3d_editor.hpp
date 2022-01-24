#pragma once

#include "base_editor.hpp"

class Quad3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void setCurrentProjectId(const string& projectId);
	void load();
	void unload();
	void update();

	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedIDs();

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
	void _updateQuad3dCreating();
	void _updateQuad3dChoosing();
	void _updateQuad3dDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	vector<string> _loadedQuadIds;
	string _hoveredQuadId = "";
	string _currentQuadId = "";
	string _currentProjectId = "";

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 0.001f;
	static inline constexpr float GRID_SIZE = 30.0f;
	static inline constexpr float GRID_REPEAT = 3.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.125f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;

	bool _isCreatingQuad3d = false;
	bool _isChoosingQuad3d = false;
	bool _isDeletingQuad3d = false;
	bool _isEditorLoaded = false;
};