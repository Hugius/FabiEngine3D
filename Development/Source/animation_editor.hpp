#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class AnimationEditor final
{
public:
	AnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);
	~AnimationEditor() = default;

	void initializeGUI();
	void load();
	void unload();
	void update();
	void setCurrentProjectName(const string& projectName);
	void loadAnimationsFromFile();
	void saveAnimationsToFile();

	vector<string>& getAnimationNames();

	bool isLoaded();

private:
	void _updateAnimationManagement();
	void _updateAnimationCreation();
	void _updateAnimationChoosing();
	void _updateAnimationRemoval();
	void _updateCamera();
	void _updateMiscellaneous();

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	string _currentAnimationID = "";
	string _currentProjectName = "";
	vector<string> _animationNames;

	// Vector3
	const Vec3 _defaultCameraPosition = Vec3(0.0f, 5.0f, 5.0f);
	Vec2 _totalCursorDifference = Vec2(0.0f);
	Vec2 _cameraAcceleration = Vec2(0.0f);
	Vec2 _lastCursorPos = Vec2(0.0f);

	// Floats
	float _cameraDistance = 5.0f;
	float _cameraScrollingAcceleration = 0.0f;
	const float _minCameraDistance = 1.0f;
	const float _minCameraHeight = 1.0f;
	const float _cameraSpeed = 0.15f;
	const float _scrollWheelDivider = 15.0f;

	// Booleans
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isEditingAnimation = false;
	bool _isRemovingAnimation = false;
	bool _isLoaded = false;
};