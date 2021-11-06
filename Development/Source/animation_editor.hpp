#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"
#include "animation.hpp"
#include "model_editor.hpp"

class AnimationEditor final
{
public:
	AnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, ModelEditor& modelEditor);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void startAnimation(const string& animationID, const string& modelID, int loops);
	void pauseAnimation(const string& animationID, const string& modelID);
	void resumeAnimation(const string& animationID, const string& modelID);
	void fadeAnimation(const string& animationID, const string& modelID, int framestep);
	void stopAnimation(const string& animationID, const string& modelID);
	void stopAllAnimations();

	// Strings
	const vector<string> getAllAnimationIDs() const;
	const vector<string> getStartedAnimationIDs() const;
	const vector<string> getStartedAnimationIDs(const string& modelID) const;

	// Booleans
	const bool isLoaded() const;
	const bool isAnimationExisting(const string& ID) const;
	const bool isAnimationStarted(const string& animationID, const string& modelID) const;
	const bool isAnimationPlaying(const string& animationID, const string& modelID) const;
	const bool isAnimationPaused(const string& animationID, const string& modelID) const;
	const bool isAnimationFading(const string& animationID, const string& modelID) const;
	const bool loadAnimationsFromFile(bool mustCheckPreviewModel = true);
	const bool saveAnimationsToFile() const;

	// Miscellaneous
	Animation* getAnimationData(const string& animationID, const string& modelID, string baseErrorMessage);

private:
	// Voids
	void _loadGUI();
	void _unloadGUI();
	void _updateAnimationExecution();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateFrameMenu();
	void _updateAnimationCreating();
	void _updateAnimationChoosing();
	void _updateAnimationDeleting();
	void _updateCamera();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);

	// Booleans
	const bool _hasReachedFloat(float first, float second, float speed) const;
	const bool _comparePartIDs(vector<string> first, vector<string> second) const;

	// Miscellaneous
	shared_ptr<Animation> _getAnimation(const string& ID) const;

	// Strings
	set<pair<string, string>> _animationsToStop;
	set<pair<string, string>> _animationsToStartAgain;
	string _currentProjectID = "";
	string _currentAnimationID = "";
	string _currentPartID = "";
	string _hoveredModelID = "";
	string _hoveredPartID = "";

	// Vectors
	Vec3 _cameraLookatPosition = Vec3(0.0f);

	// Decimals
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float CURSOR_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 0.001f;
	static inline const float GRID_SIZE = 60.0f;
	static inline const float GRID_UV = 6.0f;
	static inline const float MIN_CAMERA_DISTANCE = 0.5f;
	static inline const float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline const float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline const float PART_BLINKING_SPEED = 0.025f;

	// Integers
	static inline const unsigned int MAX_FRAME_COUNT = 100;
	int _selectedPartInversionDirection = 1;
	unsigned int _currentFrameIndex = 0;

	// Booleans
	bool _mustUpdateCurrentFramePreview = true;
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;
	bool _isEditorLoaded = false;

	// Miscellaneous
	map<pair<string, string>, Animation> _startedAnimations;
	vector<shared_ptr<Animation>> _animations;
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	ModelEditor& _modelEditor;
};