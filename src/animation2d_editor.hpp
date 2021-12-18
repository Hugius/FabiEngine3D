#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"
#include "animation2d.hpp"

class Animation2dEditor final
{
public:
	Animation2dEditor(FabiEngine3D& fe3d, GuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void startBillboardAnimation(const string& animationID, const string& billboardID, int timesToPlay);
	void pauseBillboardAnimation(const string& animationID, const string& billboardID);
	void resumeBillboardAnimation(const string& animationID, const string& billboardID);
	void stopBillboardAnimation(const string& animationID, const string& billboardID);
	void stopBillboardAnimations();
	void setBillboardAnimationFramestep(const string& animationID, const string& billboardID, unsigned int framestep);
	void startImageAnimation(const string& animationID, const string& imageID, int timesToPlay);
	void pauseImageAnimation(const string& animationID, const string& imageID);
	void resumeImageAnimation(const string& animationID, const string& imageID);
	void stopImageAnimation(const string& animationID, const string& imageID);
	void stopImageAnimations();
	void setImageAnimationFramestep(const string& animationID, const string& imageID, unsigned int framestep);

	// STRING
	const vector<string> getAnimationIDs();
	const vector<string> getStartedBillboardAnimationIDs() const;
	const vector<string> getStartedImageAnimationIDs() const;
	const vector<string> getStartedBillboardAnimationIDs(const string& billboardID) const;
	const vector<string> getStartedImageAnimationIDs(const string& billboardID) const;

	// UNSIGNED INT
	const unsigned int getBillboardAnimationRowCount(const string& animationID, const string& billboardID) const;
	const unsigned int getBillboardAnimationColumnCount(const string& animationID, const string& billboardID) const;
	const unsigned int getBillboardAnimationFramestep(const string& animationID, const string& billboardID) const;
	const unsigned int getImageAnimationRowCount(const string& animationID, const string& imageID) const;
	const unsigned int getImageAnimationColumnCount(const string& animationID, const string& imageID) const;
	const unsigned int getImageAnimationFramestep(const string& animationID, const string& imageID) const;

	// BOOL
	const bool isLoaded() const;
	const bool isAnimationExisting(const string& ID) const;
	const bool isBillboardAnimationStarted(const string& animationID, const string& billboardID) const;
	const bool isBillboardAnimationPlaying(const string& animationID, const string& billboardID) const;
	const bool isBillboardAnimationPaused(const string& animationID, const string& billboardID) const;
	const bool isImageAnimationStarted(const string& animationID, const string& imageID) const;
	const bool isImageAnimationPlaying(const string& animationID, const string& imageID) const;
	const bool isImageAnimationPaused(const string& animationID, const string& imageID) const;
	const bool loadFromFile(bool mustCheckPreviewTexture);
	const bool saveToFile() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateAnimationCreating();
	void _updateAnimationChoosing();
	void _updateAnimationDeleting();
	void _updateBillboardAnimationExecution();
	void _updateImageAnimationExecution();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);

	// MISCELLANEOUS
	shared_ptr<Animation2d> _getAnimation(const string& ID) const;

	// STRING
	static inline const string PREVIEW_BILLBOARD_ID = "@@preview_billboard";
	set<pair<string, string>> _billboardAnimationsToStop;
	set<pair<string, string>> _billboardAnimationsToStart;
	set<pair<string, string>> _imageAnimationsToStop;
	set<pair<string, string>> _imageAnimationsToStart;
	string _hoveredAnimationID = "";
	string _currentAnimationID = "";
	string _currentProjectID = "";

	// FVEC3
	static inline const fvec3 PREVIEW_BILLBOARD_POSITION = fvec3(0.0f, -0.5f, -0.75f);

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// BOOL
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	map<pair<string, string>, Animation2d> _startedBillboardAnimations;
	map<pair<string, string>, Animation2d> _startedImageAnimations;
	vector<shared_ptr<Animation2d>> _animations;
	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};