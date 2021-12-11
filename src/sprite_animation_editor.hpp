#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"
#include "sprite_animation.hpp"

class SpriteAnimationEditor final
{
public:
	SpriteAnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void startAnimation(const string& animationID, const string& billboardID, int loops);
	void pauseAnimation(const string& animationID, const string& billboardID);
	void resumeAnimation(const string& animationID, const string& billboardID);
	void stopAnimation(const string& animationID, const string& billboardID);
	void stopAllAnimations();

	// STRING
	const vector<string> getAllAnimationIDs();

	// BOOL
	const bool isLoaded() const;
	const bool loadAnimationsFromFile(bool mustCheckPreviewTexture);
	const bool saveAnimationsToFile() const;

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
	shared_ptr<SpriteAnimation> _getAnimation(const string& ID) const;

	// STRING
	static inline const string PREVIEW_BILLBOARD_ID = "@@preview_image";
	string _hoveredAnimationID = "";
	string _currentAnimationID = "";
	string _currentProjectID = "";

	// FVEC3
	static inline const fvec3 PREVIEW_BILLBOARD_POSITION = fvec3(0.0f, -0.5f, -1.0f);

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	// BOOL
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	map<pair<string, string>, shared_ptr<SpriteAnimation>> _startedAnimations;
	vector<shared_ptr<SpriteAnimation>> _animations;
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};