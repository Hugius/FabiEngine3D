#pragma once

#include "base_editor.hpp"

class SkyEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedEntities();

	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedEntityIds() const;

	const bool loadEntitiesFromFile();
	const bool saveEntitiesToFile() const;

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

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;

	vector <string> _loadedEntityIds = {};

	string _currentSkyId = "";

	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isDeletingSky = false;
};