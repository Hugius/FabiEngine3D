#pragma once

#include "base_editor.hpp"

class SoundEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

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

	static inline constexpr fvec3 ICON_QUAD_POSITION = fvec3(0.0f, 0.0f, -1.5f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;

	bool _isCreatingSound = false;
	bool _isChoosingSound = false;
	bool _isDeletingSound = false;
	bool _isEditorLoaded = false;
};