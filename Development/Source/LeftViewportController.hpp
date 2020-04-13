#pragma once

#include "ViewportController.hpp"
#include "ModelEditorr.hpp"

class LeftViewportController final : public ViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);

	void update(float delta) override;

private:
	ModelEditorr _modelEditor;
};