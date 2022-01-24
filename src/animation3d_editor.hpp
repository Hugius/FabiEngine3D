#pragma once

#include "base_editor.hpp"
#include "animation3d.hpp"
#include "model_editor.hpp"

class Animation3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<ModelEditor> modelEditor);

	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void startModelAnimation(const string& animationID, const string& modelID, int playCount);
	void pauseModelAnimation(const string& animationID, const string& modelID);
	void autopauseModelAnimation(const string& animationID, const string& modelID);
	void resumeModelAnimation(const string& animationID, const string& modelID);
	void stopModelAnimation(const string& animationID, const string& modelID);
	void pauseModelAnimations();
	void autopauseModelAnimations();
	void resumeModelAnimations();
	void stopModelAnimations();
	void setModelAnimationSpeed(const string& animationID, const string& modelID, float value);

	const vector<string> getAnimationIDs() const;
	const vector<string> getStartedModelAnimationIDs() const;
	const vector<string> getStartedModelAnimationIDs(const string& modelID) const;

	const float getModelAnimationSpeed(const string& animationID, const string& modelID) const;

	const int getModelAnimationPlayCount(const string& animationID, const string& modelID) const;

	const unsigned int getModelAnimationFrameIndex(const string& animationID, const string& modelID) const;

	const bool isLoaded() const;
	const bool isAnimationExisting(const string& ID) const;
	const bool isModelAnimationStarted(const string& animationID, const string& modelID) const;
	const bool isModelAnimationPlaying(const string& animationID, const string& modelID) const;
	const bool isModelAnimationPaused(const string& animationID, const string& modelID) const;
	const bool isModelAnimationAutopaused(const string& animationID, const string& modelID) const;
	const bool loadFromFile(bool mustCheckPreviewModel);
	const bool saveToFile() const;

private:
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

	const bool _hasReachedFloat(float first, float second, float speed) const;
	const bool _comparePartIDs(vector<string> first, vector<string> second) const;

	shared_ptr<Animation3d> _getAnimation(const string& ID) const;

	set<pair<string, string>> _modelAnimationsToStop;
	set<pair<string, string>> _modelAnimationsToStart;
	string _currentProjectID = "";
	string _currentAnimationID = "";
	string _currentPartID = "";
	string _hoveredModelID = "";
	string _hoveredPartID = "";

	fvec3 _cameraLookatPosition = fvec3(0.0f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 0.001f;
	static inline constexpr float GRID_SIZE = 60.0f;
	static inline constexpr float GRID_REPEAT = 6.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;
	float _originalPartOpacity = 0.0f;

	int _selectedPartHighlightDirection = 1;

	static inline constexpr unsigned int MAX_FRAME_COUNT = 100;
	unsigned int _currentFrameIndex = 0;

	bool _mustUpdateCurrentFramePreview = true;
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;
	bool _isEditorLoaded = false;

	map<pair<string, string>, Animation3d> _startedModelAnimations;
	vector<shared_ptr<Animation3d>> _animations;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
};