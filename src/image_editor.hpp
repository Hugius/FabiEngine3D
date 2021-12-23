#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"

class ImageEditor final
{
public:
	ImageEditor(FabiEngine3D& fe3d, GuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	// STRING
	const vector<string> getTexturePathsFromFile() const;
	const vector<string>& getLoadedIDs();

	// BOOL
	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateImageCreating();
	void _updateImageChoosing();
	void _updateImageDeleting();

	// STRING
	static inline const string PREVIEW_BILLBOARD_ID = "@@preview_billboard";
	vector<string> _loadedImageIDs;
	string _currentImageID = "";
	string _hoveredImageID = "";
	string _currentProjectID = "";

	// FVEC3
	static inline const fvec3 PREVIEW_BILLBOARD_POSITION = fvec3(0.0f, -0.5f, -0.75f);

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// BOOL
	bool _isCreatingImage = false;
	bool _isChoosingImage = false;
	bool _isDeletingImage = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};