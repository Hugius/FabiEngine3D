#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"

class LeftViewportController final : public ViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);

	void update(float delta) override;

private:
	ModelEditor _modelEditor;
};