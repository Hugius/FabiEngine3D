#pragma once

#include "base_editor.hpp"

class TextEditor final : public BaseEditor
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
	void _updateTextCreating();
	void _updateTextChoosing();
	void _updateTextDeleting();
	void _updateMiscellaneous();

	vector<string> _loadedTextIDs;
	string _currentTextID = "";
	string _hoveredTextID = "";
	string _currentProjectID = "";

	static inline const fvec2 TEXT_SIZE = fvec2(0.7f, 0.1f);

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	bool _isCreatingText = false;
	bool _isChoosingText = false;
	bool _isDeletingText = false;
};