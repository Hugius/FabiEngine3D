#pragma once

#include "viewport_controller.hpp"

#define RVPC RightViewportController

class RightViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void initialize() override;
	void update() override;

	static inline const Vec3 frameColor = Vec3(0.4f);
	static inline const Vec3 buttonColor = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 buttonHoverColor = Vec3(0.0f, 0.25f, 0.0f);
	static inline const Vec3 textColor = Vec3(1.0f);
	static inline const Vec3 textHoverColor = Vec3(0.0f);

private:

};