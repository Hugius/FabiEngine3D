#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"
#include "animation2d.hpp"

class Animation2dEditor final
{
public:
	Animation2dEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

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

	// STRING
	const vector<string> getAnimationIDs();

	// BOOL
	const bool isLoaded() const;
	const bool isAnimationExisting(const string& ID) const;
	const bool isAnimationStarted(const string& animationID, const string& modelID) const;
	const bool isAnimationPlaying(const string& animationID, const string& modelID) const;
	const bool isAnimationPaused(const string& animationID, const string& modelID) const;
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
	void _updateAnimationExecution();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);

	// MISCELLANEOUS
	shared_ptr<Animation2d> _getAnimation(const string& ID) const;

	// STRING
	static inline const string PREVIEW_BILLBOARD_ID = "@@preview_billboard";
	set<pair<string, string>> _animationsToStop;
	set<pair<string, string>> _animationsToStartAgain;
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
	map<pair<string, string>, Animation2d> _startedAnimations;
	vector<shared_ptr<Animation2d>> _animations;
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};