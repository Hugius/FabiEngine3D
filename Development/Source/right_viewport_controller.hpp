#pragma once

#include "base_viewport_controller.hpp"

#define RVPC RightViewportController

class RightViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::BaseViewportController;

	void initialize() override;
	void update() override;

	static inline const Vec3 FRAME_COLOR = Vec3(0.175f);
};