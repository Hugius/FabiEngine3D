#pragma once

#include "ViewportController.hpp"

class TopViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void update(float delta) override;

private:
	void _updateProjectCreation();
	void _updateProjectLoading();
	void _updateProjectSaving();
	void _updateDocsOpening();
	void _updateEngineQuitting();

	bool _creatingProject = false;
	bool _loadingProject = false;
	bool _savingProject = false;
	bool _openingDocs = false;
	bool _quittingEngine = false;
};