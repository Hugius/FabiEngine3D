#pragma once

#include "base_editor.hpp"

class Text2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedText2ds();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedText2dIds() const;

	const bool loadText2dsFromFile();
	const bool saveText2dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateText2dCreating();
	void _updateText2dChoosing();
	void _updateText2dDeleting();
	void _updateMiscellaneous();

	static inline const string TEXT2D_TITLE_ID = "text2d_title";

	static inline const fvec2 TEXT2D_SIZE = fvec2(1.0f, 0.2f);
	static inline const fvec2 TEXT2D_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 TEXT2D_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float COLOR_FACTOR = 255.0f;
	static inline constexpr float CAMERA_YAW = 270.0f;

	vector<string> _loadedText2dIds = {};

	string _currentText2dId = "";
	string _hoveredText2dId = "";
};