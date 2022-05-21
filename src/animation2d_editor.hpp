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

	static inline const string PREVIEW_QUAD3D_ID = "@@preview_quad3d";
	static inline const string ANIMATION2D_TITLE_ID = "animation2d_title";

	static inline const fvec3 PREVIEW_QUAD3D_POSITION = fvec3(0.0f, 0.0f, -0.75f);

	static inline const fvec2 ANIMATION2D_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 ANIMATION2D_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float CAMERA_YAW = 270.0f;

	vector<string> _loadedAnimation2dIds = {};

	string _currentAnimation2dId = "";
	string _hoveredAnimation2dId = "";

	bool _isPreviewTextureChosen = false;
};