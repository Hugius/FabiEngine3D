#pragma once

#include "base_editor.hpp"

class Quad2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedQuad2ds();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedQuad2dIds() const;

	const bool loadQuad2dsFromFile();
	const bool saveQuad2dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateQuad2dCreating();
	void _updateQuad2dChoosing();
	void _updateQuad2dDeleting();
	void _updateMiscellaneous();

	static inline const string QUAD2D_TITLE_ID = "quad2d_title";

	static inline const fvec2 QUAD2D_SIZE = fvec2(0.75f);
	static inline const fvec2 QUAD2D_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 QUAD2D_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float COLOR_MULTIPLIER = 255.0f;
	static inline constexpr float CAMERA_YAW = 270.0f;

	vector<string> _loadedQuad2dIds = {};

	string _currentQuad2dId = "";
	string _hoveredQuad2dId = "";
};