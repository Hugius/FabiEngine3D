#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"

class AudioEditor final
{
public:
	AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	// STRING
	const vector<string> getAllAudioPathsFromFile() const;
	const vector<string>& getLoadedAudioIDs();

	// BOOL
	const bool loadAudioEntitiesFromFile();
	const bool saveAudioEntitiesToFile() const;
	const bool isLoaded() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateAudioCreating();
	void _updateAudioChoosing();
	void _updateAudioDeleting();
	void _updateMiscellaneous();

	// STRING
	vector<string> _loadedAudioIDs;
	string _currentAudioID = "";
	string _hoveredAudioID = "";
	string _currentProjectID = "";

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// BOOL
	bool _isCreatingAudio = false;
	bool _isChoosingAudio = false;
	bool _isDeletingAudio = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};