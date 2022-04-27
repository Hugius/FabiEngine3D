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
	void _updateQuad2dCreating();
	void _updateQuad2dChoosing();
	void _updateQuadDeleting();
	void _updateMiscellaneous();

	static inline const fvec2 QUAD2D_SIZE = fvec2(0.75f);

	vector<string> _loadedQuad2dIds = {};

	string _currentQuad2dId = "";
	string _hoveredQuad2dId = "";
};