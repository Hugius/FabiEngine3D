#pragma once

#include "base_viewport_controller.hpp"

#define RVPC RightViewportController

class RightViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::BaseViewportController;

	void initialize() override;
	void update() override;

	static inline const Vec3 FRAME_COLOR = Vec3(0.4f);
	static inline const Vec3 BUTTON_COLOR = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 BUTTON_HOVER_COLOR = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 TEXT_COLOR = Vec3(1.0f);
	static inline const Vec3 TEXT_HOVER_COLOR = Vec3(0.0f);

private:

};