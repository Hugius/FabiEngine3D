#pragma once

#include "viewport_controller.hpp"

class TopViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void initialize() override;
	void update(float delta) override;

private:
	void _initializeProjectCreation();
	void _initializeProjectLoading();
	void _initializeProjectSaving();
	void _initializeDocsOpening();
	void _initializeEngineQuitting();
	void _updateProjectCreation();
	void _updateProjectLoading();
	void _updateProjectSaving();
	void _updateDocsOpening();
	void _updateEngineQuitting();

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