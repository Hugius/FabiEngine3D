#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"
#include "animation3d.hpp"
#include "model_editor.hpp"

class Animation3dEditor final
{
public:
	Animation3dEditor(FabiEngine3D& fe3d, GuiManager& gui, ModelEditor& modelEditor);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void startModelAnimation(const string& animationID, const string& modelID, int playCount);
	void autopauseModelAnimation(const string& animationID, const string& modelID);
	void pauseModelAnimation(const string& animationID, const string& modelID);
	void resumeModelAnimation(const string& animationID, const string& modelID);
	void stopModelAnimation(const string& animationID, const string& modelID);
	void stopModelAnimations();
	void setModelAnimationSpeed(const string& animationID, const string& modelID, float value);

	// STRING
	const vector<string> getAnimationIDs() const;
	const vector<string> getStartedModelAnimationIDs() const;
	const vector<string> getStartedModelAnimationIDs(const string& modelID) const;

	// FLOAT
	const float getModelAnimationSpeed(const string& animationID, const string& modelID) const;

	// INT
	const int getModelAnimationPlayCount(const string& animationID, const string& modelID) const;

	// UNSIGNED INT
	const unsigned int getModelAnimationFrameIndex(const string& animationID, const string& modelID) const;

	// BOOL
	const bool isLoaded() const;
	const bool isAnimationExisting(const string& ID) const;
	const bool isModelAnimationStarted(const string& animationID, const string& modelID) const;
	const bool isModelAnimationPlaying(const string& animationID, const string& modelID) const;
	const bool isModelAnimationAutopaused(const string& animationID, const string& modelID) const;
	const bool isModelAnimationPaused(const string& animationID, const string& modelID) const;
	const bool loadFromFile(bool mustCheckPreviewModel);
	const bool saveToFile() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateFrameMenu();
	void _updateAnimationCreating();
	void _updateAnimationChoosing();
	void _updateAnimationDeleting();
	void _updateModelAnimationExecution();
	void _updateCamera();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);

	// BOOL
	const bool _hasReachedFloat(float first, float second, float speed) const;
	const bool _comparePartIDs(vector<string> first, vector<string> second) const;

	// MISCELLANEOUS
	shared_ptr<Animation3d> _getAnimation(const string& ID) const;

	// STRING
	set<pair<string, string>> _modelAnimationsToStop;
	set<pair<string, string>> _modelAnimationsToStart;
	string _currentProjectID = "";
	string _currentAnimationID = "";
	string _currentPartID = "";
	string _hoveredModelID = "";
	string _hoveredPartID = "";

	// FVEC3
	fvec3 _cameraLookatPosition = fvec3(0.0f);

	// FLOAT
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
	static inline const float PART_HIGHLIGHT_SPEED = 0.025f;

	// INT
	int _selectedPartHighlightDirection = 1;

	// UNSIGNED INT
	static inline const unsigned int MAX_FRAME_COUNT = 100;
	unsigned int _currentFrameIndex = 0;

	// BOOL
	bool _mustUpdateCurrentFramePreview = true;
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	map<pair<string, string>, Animation3d> _startedModelAnimations;
	vector<shared_ptr<Animation3d>> _animations;
	FabiEngine3D& _fe3d;
	GuiManager& _gui;
	ModelEditor& _modelEditor;
};