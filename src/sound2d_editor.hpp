#pragma once

#include "base_editor.hpp"

class Sound2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedSound2ds();

	const vector<string> getAudioPathsFromFile() const;
	const vector<string> & getLoadedSound2dIds() const;

	const bool loadSound2dsFromFile();
	const bool saveSound2dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSound2dCreating();
	void _updateSound2dChoosing();
	void _updateSound2dDeleting();
	void _updateMiscellaneous();

	static inline const fvec3 STATUS_QUAD3D_POSITION = fvec3(0.0f, 0.0f, -1.5f);

	vector<string> _loadedSound2dIds = {};

	string _currentSound2dId = "";
	string _hoveredSound2dId = "";
};