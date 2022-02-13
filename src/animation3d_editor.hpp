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

	const vector<string> getAnimationIds() const;
	const vector<string> getAnimationPartIds(const string& id) const;

	const bool loadFromFile(bool mustCheckPreviewModel);
	const bool saveToFile() const;

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

	const bool _comparePartIds(vector<string> first, vector<string> second) const;

	string _currentAnimationId = "";
	string _currentPartId = "";
	string _hoveredModelId = "";
	string _hoveredPartId = "";

	fvec3 _cameraLookatPosition = fvec3(0.0f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 0.001f;
	static inline constexpr float GRID_SIZE = 100.0f;
	static inline constexpr float GRID_REPEAT = 10.0f;
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
	bool _isChoosingModel = false;
	bool _isChoosingPart = false;

	shared_ptr<ModelEditor> _modelEditor = nullptr;
};