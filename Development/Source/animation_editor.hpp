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

	void initializeGUI();
	void load();
	void unload();
	void update();
	void setCurrentProjectName(const string& projectName);
	void loadAnimationsFromFile();
	void saveAnimationsToFile();

	bool isLoaded();

private:
	void _updateManagementScreen();
	void _updateCreationScreen();
	void _updateChoosingScreen();
	void _updateEditingScreen();
	void _updateRemovalScreen();
	void _updateCamera();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);
	bool _isAnimationExisting(const string& ID);
	vector<string> _getAnimationIDs();
	shared_ptr<Animation> _getAnimation(const string& ID);

	// Core
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	ModelEditor& _modelEditor;

	// Strings
	string _currentProjectName = "";
	string _currentAnimationID = "";
	vector<shared_ptr<Animation>> _animations;

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