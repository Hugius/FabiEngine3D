#pragma once

#include "base_editor.hpp"

class Sound3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedSound3ds();

	const vector<string> getAudioPathsFromFile() const;
	const vector<string> & getLoadedSound3dIds() const;

	const bool loadSound3dsFromFile();
	const bool saveSound3dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSound3dCreating();
	void _updateSound3dChoosing();
	void _updateSound3dDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string SOUND3D_MODEL_ID = "@@sound3d";
	static inline const string SOUND3D_MODEL_PATH = "engine\\assets\\mesh\\speaker.obj";

	static inline const fvec3 SOUND3D_POSITION = fvec3(0.0f, 2.0f, 0.0f);

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_SIZE = 50.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.05f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float VOLUME_MULTIPLIER = 100.0f;
	static inline constexpr float DISTANCE_MULTIPLIER = 100.0f;

	static inline constexpr int GRID_REPEAT = 10;

	vector<string> _loadedSound3dIds = {};

	string _hoveredSound3dId = "";
	string _currentSound3dId = "";
};