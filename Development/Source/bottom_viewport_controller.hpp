#pragma once

#include "viewport_controller.hpp"

class BottomViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void initialize() override;
	void update(float delta) override;

private:
	const vec3 _bottomVpButtonColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _bottomVpButtonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	const vec3 _bottomVpTextColor = vec3(1.0f);
	const vec3 _bottomVpTextHoverColor = vec3(0.0f);
};