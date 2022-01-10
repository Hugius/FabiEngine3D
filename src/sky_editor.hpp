#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"

class SkyEditor final
{
public:
	SkyEditor(EngineInterface& fe3d, GuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

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
	void _updateMiscellaneousMenu();
	void _updateSkyCreating();
	void _updateSkyChoosing();
	void _updateSkyDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	vector <string> _loadedSkyIDs;
	string _currentProjectID = "";
	string _currentSkyID = "";

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float CURSOR_SENSITIVITY = 0.025f;

	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isDeletingSky = false;
	bool _isEditorLoaded = false;

	EngineInterface& _fe3d;
	GuiManager& _gui;
};