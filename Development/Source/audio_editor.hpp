#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class AudioEditor final
{
public:
	AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);
	~AudioEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(const string& projectName);

	bool isLoaded();

private:
	void _updateMainMenu();
	void _updateAudioCreation();
	void _updateAudioChoosing();
	void _updateAudioEditing();
	void _updateAudioRemoval();

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Audio
	vector<string> _audioNames;
	string _currentAudioID = "";
	string _hoveredAudioID = "";
	bool _isCreatingAudio = false;
	bool _isChoosingAudio = false;
	bool _isEditingAudio = false;
	bool _isRemovingAudio = false;

	// Miscellaneous
	string _currentProjectName = "";
	bool _isLoaded = false;
};