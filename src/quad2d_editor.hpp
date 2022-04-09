#pragma once

#include "base_editor.hpp"

class Quad2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedEntities();

	const vector<string> getImagePathsFromFile() const;
	const vector<string> & getLoadedEntityIds() const;

	const bool loadEntitiesFromFile();
	const bool saveEntitiesToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateQuadCreating();
	void _updateQuadChoosing();
	void _updateQuadDeleting();
	void _updateMiscellaneous();

	static inline const fvec2 QUAD_SIZE = fvec2(0.75f);

	vector<string> _loadedEntityIds = {};

	string _currentQuadId = "";
	string _hoveredQuadId = "";
};