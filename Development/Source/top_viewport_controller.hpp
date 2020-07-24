#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"
#include "world_editor.hpp"
#include "billboard_editor.hpp"
#include "scene_editor.hpp"

class TopViewportController final : public ViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, 
		ModelEditor& modelEditor, WorldEditor& worldEditor, BillboardEditor& billboardEditor, SceneEditor& sceneEditor);
	~TopViewportController() = default;

	void initialize() override;
	void update() override;

	static inline const vec3 frameColor = vec3(0.25f);
	static inline const vec3 buttonColor = vec3(0.0f, 0.25f, 0.0f);
	static inline const vec3 buttonHoverColor = vec3(0.0f, 0.5f, 0.0f);
	static inline const vec3 textColor = vec3(1.0f);
	static inline const vec3 textHoverColor = vec3(0.0f);

private:
	void _initializeProjectChoosing();
	void _updateProjectCreation();
	void _updateProjectLoading();
	void _updateProjectDeletion();
	void _saveCurrentProject();
	void _loadCurrentProject();

	ModelEditor& _modelEditor;
	WorldEditor& _worldEditor;
	BillboardEditor& _billboardEditor;
	SceneEditor& _sceneEditor;

	string _currentProjectName = "";

	bool _creatingProject = false;
	bool _loadingProject = false;
	bool _deletingProject = false;
};