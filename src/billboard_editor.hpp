#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"

class BillboardEditor final
{
public:
	BillboardEditor(FabiEngine3D& fe3d, GuiManager& gui);

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
	void _updateTexturingMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateBillboardCreating();
	void _updateBillboardChoosing();
	void _updateBillboardDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	vector<string> _loadedBillboardIDs;
	string _hoveredBillboardID = "";
	string _currentBillboardID = "";
	string _currentProjectID = "";

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float CURSOR_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 0.001f;
	static inline const float GRID_SIZE = 30.0f;
	static inline const float GRID_UV = 3.0f;
	static inline const float MIN_CAMERA_DISTANCE = 0.5f;
	static inline const float CAMERA_DISTANCE_SPEED = 0.125f;
	static inline const float CAMERA_LOOKAT_SPEED = 0.025f;

	bool _isCreatingBillboard = false;
	bool _isChoosingBillboard = false;
	bool _isDeletingBillboard = false;
	bool _isEditorLoaded = false;

	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};