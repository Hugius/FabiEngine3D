#pragma once

#include "base_editor.hpp"

class SoundEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedSounds();

	const vector<string> getAudioPathsFromFile() const;
	const vector<string> & getLoadedSoundIds() const;

	const bool loadSoundsFromFile();
	const bool saveSoundsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSoundCreating();
	void _updateSoundChoosing();
	void _updateSoundDeleting();
	void _updateMiscellaneous();

	static inline const fvec3 STATUS_QUAD3D_POSITION = fvec3(0.0f, 0.0f, -1.5f);

	vector<string> _loadedSoundIds = {};

	string _currentSoundId = "";
	string _hoveredSoundId = "";
};