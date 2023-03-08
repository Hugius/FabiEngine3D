#pragma once

#include "base_editor.hpp"

class SkyEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void deleteLoadedSkies();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedSkyIds() const;

	const bool loadSkiesFromFile();
	const bool saveSkiesToFile() const;

private:
	void _load();
	void _update();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateTexturingMenu();
	void _updateGraphicsMenu();
	void _updateMiscellaneousMenu();
	void _updateSkyCreating();
	void _updateSkyChoosing();
	void _updateSkyDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline const string SKY_TITLE_ID = "sky_title";

	static inline const fvec2 SKY_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 SKY_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float CURSOR_SENSITIVITY = 0.05f;
	static inline constexpr float COLOR_FACTOR = 255.0f;
	static inline constexpr float LIGHTNESS_FACTOR = 100.0f;

	vector <string> _loadedSkyIds = {};

	string _currentSkyId = "";

	bool _isSkyHovered = false;
};