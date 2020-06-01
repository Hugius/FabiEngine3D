#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"
#include "world_editor.hpp"
#include "billboard_editor.hpp"

class LeftViewportController final : public ViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);

	void initialize() override;
	void update() override;

	ModelEditor& getModelEditor();
	WorldEditor& getWorldEditor();
	BillboardEditor& getBillboardEditor();

private:
	ModelEditor _modelEditor;
	WorldEditor _worldEditor;
	BillboardEditor _billboardEditor;
};