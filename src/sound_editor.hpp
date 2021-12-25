#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"

class SoundEditor final
{
public:
	SoundEditor(FabiEngine3D& fe3d, GuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	const vector<string> getAudioPathsFromFile() const;
	const vector<string>& getLoadedIDs();

	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSoundCreating();
	void _updateSoundChoosing();
	void _updateSoundDeleting();
	void _updateMiscellaneous();

	vector<string> _loadedSoundIDs;
	string _currentSoundID = "";
	string _hoveredSoundID = "";
	string _currentProjectID = "";

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	bool _isCreatingSound = false;
	bool _isChoosingSound = false;
	bool _isDeletingSound = false;
	bool _isEditorLoaded = false;

	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};