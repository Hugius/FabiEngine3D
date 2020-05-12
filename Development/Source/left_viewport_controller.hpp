#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"

class LeftViewportController final : public ViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);

	void initialize() override;
	void update(float delta) override;

	ModelEditor& getModelEditor();

private:
	ModelEditor _modelEditor;
};