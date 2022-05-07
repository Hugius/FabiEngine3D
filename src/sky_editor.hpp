#pragma once

#include "base_editor.hpp"

class SkyEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedSkies();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedSkyIds() const;

	const bool loadSkiesFromFile();
	const bool saveSkiesToFile() const;

private:
	void _load();
	void _unload();
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

	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;

	vector <string> _loadedSkyIds = {};

	string _currentSkyId = "";

	bool _isSkyHovered = false;
};