#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "animation.hpp"
#include "model_editor.hpp"

class AnimationEditor final
{
public:
	AnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, ModelEditor& modelEditor);

	// Interface
	void load();
	void unload();
	void update();
	void setCurrentProjectID(const string& projectID);
	void loadAnimationsFromFile();
	void saveAnimationsToFile();
	void startAnimation(const string& animationID, const string& modelID, int loops);
	void pauseAnimation(const string& animationID, const string& modelID);
	void resumeAnimation(const string& animationID, const string& modelID);
	void fadeAnimation(const string& animationID, const string& modelID, int framestep);
	void stopAnimation(const string& animationID, const string& modelID);
	void stopAllAnimations();

	// Miscellaneous
	bool isLoaded();
	bool isAnimationExisting(const string& ID);
	bool isAnimationStarted(const string& animationID, const string& modelID);
	bool isAnimationPlaying(const string& animationID, const string& modelID);
	bool isAnimationPaused(const string& animationID, const string& modelID);
	bool isAnimationFading(const string& animationID, const string& modelID);
	Animation* getAnimationData(const string& animationID, const string& modelID, string baseErrorMessage);
	const vector<string> getAllAnimationIDs();
	const vector<string> getStartedAnimationIDs();
	const vector<string> getStartedAnimationIDs(const string& modelID);

private:
	void _loadGUI();
	void _unloadGUI();
	void _updateAnimationExecution();
	void _updateManagementScreen();
	void _updateAnimationCreation();
	void _updateAnimationChoice();
	void _updateEditingScreen();
	void _updateFrameScreen();
	void _updateAnimationRemoval();
	void _updateCamera();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);
	bool _hasReachedFloat(float first, float second, float speed);
	bool _comparePartIDs(vector<string> first, vector<string> second);
	shared_ptr<Animation> _getAnimation(const string& ID);

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	ModelEditor& _modelEditor;

	// Containers
	vector<shared_ptr<Animation>> _animations;
	set<pair<string, string>> _animationsToStop;
	set<pair<string, string>> _animationsToStart;
	map<pair<string, string>, Animation> _startedAnimations;

	// Strings
	string _currentProjectID   = "";
	string _currentAnimationID = "";
	string _currentPartID	   = "";

	// Vectors
	Vec3 _cameraLookatPosition  = Vec3(0.0f);
	Vec2 _totalCursorDifference = Vec2(0.0f, 0.5f);
	Vec2 _cameraAcceleration    = Vec2(0.0f);
	Vec2 _lastCursorPos			= Vec2(0.0f);

	// Floats
	static inline const float MIN_CAMERA_HEIGHT = 1.0f;
	static inline const float SCROLL_WHEEL_DIVIDER = 5.0f;
	static inline const float CAMERA_DISTANCE = 5.0f;
	static inline const float CAMERA_SPEED = 0.1f;
	float _cameraDistance			   = CAMERA_DISTANCE;
	float _cameraScrollingAcceleration = 0.0f;
	float _partColorStrength		   = 0.0f;
	float _colorChangingSpeed		   = 0.05f;
	float _cameraSpeed				   = CAMERA_SPEED;

	// Integers
	static inline const unsigned int MAX_FRAME_COUNT = 100;
	unsigned int _currentFrameIndex = 0;

	// Booleans
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isEditingAnimation  = false;
	bool _isRemovingAnimation = false;
	bool _isEditorLoaded	  = false;
	bool _isEditorLoading	  = false;
	bool _partColorIncreasing = true;
};