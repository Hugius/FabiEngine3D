#pragma once

#include "base_editor.hpp"

class SkyEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedIDs();

	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
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

	vector <string> _loadedSkyIDs;
	string _currentProjectID = "";
	string _currentSkyID = "";

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;

	bool _isCreatingSky = false;
	bool _isChoosingSky = false;
	bool _isDeletingSky = false;
	bool _isEditorLoaded = false;
};