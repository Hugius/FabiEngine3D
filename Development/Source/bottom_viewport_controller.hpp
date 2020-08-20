#pragma once

#include "viewport_controller.hpp"

class BottomViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void initialize() override;
	void update() override;

	static inline const vec3 frameColor = vec3(0.05f);
	static inline const vec3 buttonColor = vec3(0.0f, 0.25f, 0.0f);
	static inline const vec3 buttonHoverColor = vec3(0.0f, 0.25f, 0.0f);
	static inline const vec3 textColor = vec3(1.0f);
	static inline const vec3 textHoverColor = vec3(0.0f);

private:
	shared_ptr<EngineGuiScreen> _statsScreen;
};