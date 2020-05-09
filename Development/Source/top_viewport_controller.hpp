#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"

class TopViewportController final : public ViewportController
{
public:
	TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, ModelEditor& modelEditor);
	~TopViewportController();

	void initialize() override;
	void update(float delta) override;

private:
	void _initializeProjectCreation();
	void _initializeProjectLoading();
	void _saveCurrentProject();
	void _updateProjectCreation();
	void _updateProjectLoading();

	ModelEditor& _modelEditor;

	string _currentProjectName = "";

	bool _creatingProject = false;
	bool _loadingProject = false;
	bool _savingProject = false;
	bool _openingDocs = false;
	bool _quittingEngine = false;

	const vec3 _buttonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _buttonHoverColor = vec3(0.0f, 0.5f, 0.0f);
	const vec3 _textColor = vec3(1.0f);
	const vec3 _textHoverColor = vec3(0.0f);
};