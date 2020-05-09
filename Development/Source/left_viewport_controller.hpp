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

	const vec3 _leftVpButtonColor = vec3(0.0f, 0.0f, 0.5f);
	const vec3 _leftVpButtonHoverColor = vec3(0.5f, 0.5f, 1.0f);
	const vec3 _leftVpTextColor = vec3(1.0f);
	const vec3 _leftVpTextHoverColor = vec3(0.0f);
};