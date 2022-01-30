#pragma once

#include "base_editor.hpp"

class Text2dEditor final : public BaseEditor
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
	void _updateTextCreating();
	void _updateTextChoosing();
	void _updateTextDeleting();
	void _updateMiscellaneous();

	vector<string> _loadedTextIds;
	string _currentTextId = "";
	string _hoveredTextId = "";

	static inline const string TEXT_CONTENT = "Text123";

	static inline const fvec2 TEXT_SIZE = fvec2(1.0f, 0.2f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;

	bool _isCreatingText = false;
	bool _isChoosingText = false;
	bool _isDeletingText = false;
};