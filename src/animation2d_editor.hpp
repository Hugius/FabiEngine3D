#pragma once

#include "base_editor.hpp"
#include "animation2d.hpp"

class Animation2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedAnimation2ds();

	const vector<string> & getLoadedAnimation2dIds() const;

	const bool loadAnimation2dsFromFile();
	const bool saveAnimation2dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateAnimation2dCreating();
	void _updateAnimation2dChoosing();
	void _updateAnimation2dDeleting();
	void _updateImageChoosing();
	void _updateMiscellaneous();

	static inline const string PREVIEW_QUAD2D_ID = "@@preview_quad2d";

	static inline const fvec3 PREVIEW_QUAD2D_POSITION = fvec3(0.0f, 0.0f, -0.75f);

	vector<string> _loadedAnimation2dIds = {};

	string _hoveredAnimation2dId = "";
	string _currentAnimation2dId = "";

	bool _isPreviewTextureChosen = false;
};