#pragma once

#include "base_editor.hpp"

class SkyEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();

	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedIds();

	const bool loadFromFile();
	const bool saveToFile() const;

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

	vector <string> _loadedSkyIds;
	string _currentSkyId = "";

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;

	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isDeletingSky = false;
};