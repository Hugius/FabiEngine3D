#pragma once

#include "base_editor.hpp"

class Text3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void setCurrentProjectID(const string& projectID);
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
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateText3dCreating();
	void _updateText3dChoosing();
	void _updateText3dDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string TEXT_CONTENT = "Text123";
	vector<string> _loadedTextIDs;
	string _hoveredTextID = "";
	string _currentTextID = "";
	string _currentProjectID = "";

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

	bool _isCreatingText3d = false;
	bool _isChoosingText3d = false;
	bool _isDeletingText3d = false;
	bool _isEditorLoaded = false;
};