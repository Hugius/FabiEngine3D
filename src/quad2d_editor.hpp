#pragma once

#include "base_editor.hpp"

class Quad2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void setCurrentProjectId(const string& projectId);
	void load();
	void update();
	void unload();

	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedIDs();

	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateQuadCreating();
	void _updateQuadChoosing();
	void _updateQuadDeleting();
	void _updateMiscellaneous();

	vector<string> _loadedQuadIds;
	string _currentQuadId = "";
	string _hoveredQuadId = "";
	string _currentProjectId = "";

	static inline const fvec2 QUAD_SIZE = fvec2(0.75f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;

	bool _isCreatingQuad = false;
	bool _isChoosingQuad = false;
	bool _isDeletingQuad = false;
};