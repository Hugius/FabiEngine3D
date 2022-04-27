#pragma once

#include "base_editor.hpp"
#include "animation2d.hpp"

class Animation2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedAnimations();

	const vector<string> & getLoadedAnimationIds() const;

	const bool loadAnimationsFromFile();
	const bool saveAnimationsToFile() const;

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

	static inline const string PREVIEW_QUAD_ID = "@@preview_quad";

	static inline const fvec3 PREVIEW_QUAD_POSITION = fvec3(0.0f, 0.0f, -0.75f);

	vector<string> _loadedAnimation2dIds = {};

	string _hoveredAnimation2dId = "";
	string _currentAnimation2dId = "";

	bool _isPreviewTextureChosen = false;
};