#pragma once

#include "base_editor.hpp"
#include "animation3d.hpp"
#include "model_editor.hpp"

class Animation3dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<ModelEditor> modelEditor);

	void update();
	void deleteLoadedAnimations();

	const vector<string>& getLoadedAnimationIds() const;

	const bool loadAnimationsFromFile();
	const bool saveAnimationsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateFrameMenu();
	void _updateAnimationCreating();
	void _updateAnimationChoosing();
	void _updateAnimationDeleting();
	void _updateModelChoosing();
	void _updatePartChoosing();
	void _updateCamera();
	void _updateMiscellaneous();

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 0.001f;
	static inline constexpr float GRID_SIZE = 100.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline constexpr float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline constexpr float PART_HIGHLIGHT_SPEED = 0.025f;
	static inline constexpr unsigned int GRID_REPEAT = 10;
	static inline constexpr unsigned int MAX_FRAME_COUNT = 100;

	vector<string> _loadedAnimationIds = {};

	string _currentAnimationId = "";
	string _currentPartId = "";
	string _hoveredModelId = "";
	string _hoveredPartId = "";
	string _previewModelId = "";

	fvec3 _cameraLookatPosition = fvec3(0.0f);
	fvec3 _initialModelSize = fvec3(0.0f);

	float _originalPartOpacity = 0.0f;

	unsigned int _currentFrameIndex = 0;

	int _selectedPartHighlightDirection = 1;

	bool _mustUpdateCurrentFramePreview = true;
	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;
	bool _isChoosingModel = false;
	bool _isChoosingPart = false;

	shared_ptr<ModelEditor> _modelEditor = nullptr;
};