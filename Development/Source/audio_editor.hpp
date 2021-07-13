#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class AudioEditor final
{
public:
	AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();
	bool loadAudioEntitiesFromFile();
	bool saveAudioEntitiesToFile();

	bool isLoaded();

	const vector<string> getAllAudioPathsFromFile();
	const vector<string>& getLoadedAudioIDs();

private:
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateAudioCreation();
	void _updateAudioChoosing();
	void _updateAudioEditing();
	void _updateAudioRemoval();
	void _updateMiscellaneous();

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Audio
	vector<string> _loadedAudioIDs;
	string _currentAudioID = "";
	string _hoveredAudioID = "";
	bool _isCreatingAudio = false;
	bool _isChoosingAudio = false;
	bool _isEditingAudio = false;
	bool _isRemovingAudio = false;

	// Miscellaneous
	string _currentProjectID = "";
	bool _isEditorLoaded = false;
};