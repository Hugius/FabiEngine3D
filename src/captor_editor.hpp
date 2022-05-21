#pragma once

#include "base_editor.hpp"

class CaptorEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedCaptors();

	const vector<string> & getLoadedCaptorIds() const;

	const bool loadCaptorsFromFile();
	const bool saveCaptorsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateCaptorCreating();
	void _updateCaptorChoosing();
	void _updateCaptorDeleting();

	static inline const string CAPTOR_TITLE_ID = "captor_title";

	static inline const fvec3 DIRECTIONAL_LIGHTING_POSITION = fvec3(1000.0f);

	static inline const fvec2 CAPTOR_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 CAPTOR_TITLE_SIZE = fvec2(0.025f, 0.1f);

	vector<string> _loadedCaptorIds = {};

	string _currentCaptorId = "";
};