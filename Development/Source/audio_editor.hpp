#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class AudioEditor final
{
public:
	AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	// Strings
	const vector<string> getAllAudioPathsFromFile();
	const vector<string>& getLoadedAudioIDs();

	// Booleans
	bool loadAudioEntitiesFromFile();
	bool saveAudioEntitiesToFile();
	bool isLoaded();

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateAudioCreating();
	void _updateAudioChoosing();
	void _updateAudioDeleting();
	void _updateMiscellaneous();

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	vector<string> _loadedAudioIDs;
	string _currentAudioID = "";
	string _hoveredAudioID = "";
	string _currentProjectID = "";

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// Booleans
	bool _isCreatingAudio = false;
	bool _isChoosingAudio = false;
	bool _isDeletingAudio = false;
	bool _isEditorLoaded = false;
};