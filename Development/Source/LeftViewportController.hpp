#pragma once

#include "ViewportController.hpp"

class LeftViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void update(float delta) override;

private:
	void _updateModelCreation();
	void _updateModelEditing();
	void _updateModelRemoval();

	void _updateWorldEditor();
	void _updatePlacingEditor();
	void _updateLightingEditor();
	void _updateScriptEditor();

	bool _modelCreationEnabled = false;
	bool _modelEditingEnabled = false;
	bool _modelRemovalEnabled = false;
	bool _worldlEditorEnabled = false;
	bool _placingEditorEnabled = false;
	bool _lightingEditorEnabled = false;
	bool _scriptEditorEnabled = false;
};