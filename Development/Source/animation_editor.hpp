#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "animation.hpp"
#include "model_editor.hpp"

class AnimationEditor final
{
public:
	AnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, ModelEditor& modelEditor);
	~AnimationEditor() = default;

	void load();
	void unload();
	void update();
	void setCurrentProjectID(const string& projectName);
	void loadAnimationsFromFile();
	void saveAnimationsToFile();
	void startAnimation(const string& animationID, const string& modelID, int timesToPlay);
	void setAnimationSpeedMultiplier(const string animationID, const string& modelID, float speed);
	void pauseAnimation(const string& animationID, const string& modelID);
	void resumeAnimation(const string& animationID, const string& modelID);
	void stopAnimation(const string& animationID, const string& modelID);
	void fadeAnimation(const string& animationID, const string& modelID, int framestep);
	void stopAllAnimations();

	bool isLoaded();
	bool isAnimationStarted(const string& animationID, const string& modelID);
	bool isAnimationPlaying(const string& animationID, const string& modelID);
	bool isAnimationPaused(const string& animationID, const string& modelID);
	unsigned int getAnimationFrameIndex(const string& animationID, const string& modelID);
	const vector<string> getLoadedAnimationIDs();
	const vector<string> getPlayingAnimationNames();
	const vector<string> getPlayingAnimationNames(const string& modelID);

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
	bool _isAnimationExisting(const string& ID);
	bool _hasReachedFloat(float first, float second, float speed);
	bool _comparePartNames(vector<string> first, vector<string> second);
	shared_ptr<Animation> _getAnimation(const string& ID);

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	ModelEditor& _modelEditor;

	// Containers
	vector<shared_ptr<Animation>> _animations;
	set<pair<string, string>> _animationsToStop;
	set<pair<string, string>> _animationsToStart;
	map<pair<string, string>, Animation> _playingAnimations;

	// Strings
	string _currentProjectID = "";
	string _currentAnimationID = "";
	string _currentPartName	   = "";

	// Vectors
	const Vec3 _defaultCameraPosition = Vec3(0.0f, 5.0f, 5.0f);
	Vec3 _cameraLookatPosition = Vec3(0.0f);
	Vec2 _totalCursorDifference = Vec2(0.0f, 0.5f);
	Vec2 _cameraAcceleration = Vec2(0.0f);
	Vec2 _lastCursorPos = Vec2(0.0f);

	// Floats
	float _cameraDistance = 5.0f;
	float _cameraScrollingAcceleration = 0.0f;
	float _partColorStrength = 0.0f;
	float _colorChangingSpeed = 0.05f;
	float _cameraSpeed = 0.1f;
	const float _minCameraDistance = 1.0f;
	const float _minCameraHeight = 1.0f;
	const float _scrollWheelDivider = 5.0f;

	// Integers
	const unsigned int _maxFrameCount = 100;
	unsigned int _currentFrameIndex = 0;

	// Booleans
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isEditingAnimation = false;
	bool _isRemovingAnimation = false;
	bool _isEditorLoaded = false;
	bool _isEditorLoading = false;
	bool _partColorIncreasing = true;
};