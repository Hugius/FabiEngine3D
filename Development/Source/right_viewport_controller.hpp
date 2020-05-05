#pragma once

#include "viewport_controller.hpp"

class RightViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void initialize() override;
	void update(float delta) override;

private:
	const vec3 _rightVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _rightVpButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _rightVpTextColor = vec3(1.0f);
	const vec3 _rightVpTextHoverColor = vec3(0.0f);
};