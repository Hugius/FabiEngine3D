#pragma once

#include "base_editor.hpp"

class QuadEditor final : public BaseEditor
{
public:
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
	void _updateQuadCreating();
	void _updateQuadChoosing();
	void _updateQuadDeleting();
	void _updateMiscellaneous();

	static inline const string PREVIEW_BILLBOARD_ID = "@@preview_billboard";
	vector<string> _loadedQuadIDs;
	string _currentQuadID = "";
	string _hoveredQuadID = "";
	string _currentProjectID = "";

	static inline const fvec3 PREVIEW_BILLBOARD_POSITION = fvec3(0.0f, 0.0f, -0.75f);

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	bool _isCreatingQuad = false;
	bool _isChoosingQuad = false;
	bool _isDeletingQuad = false;
	bool _isEditorLoaded = false;
};