#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"

class SoundEditor final
{
public:
	SoundEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	// STRING
	const vector<string> getAllAudioPathsFromFile() const;
	const vector<string>& getLoadedIDs();

	// BOOL
	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSoundCreating();
	void _updateSoundChoosing();
	void _updateSoundDeleting();
	void _updateMiscellaneous();

	// STRING
	vector<string> _loadedSoundIDs;
	string _currentSoundID = "";
	string _hoveredSoundID = "";
	string _currentProjectID = "";

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// BOOL
	bool _isCreatingSound = false;
	bool _isChoosingSound = false;
	bool _isDeletingSound = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};