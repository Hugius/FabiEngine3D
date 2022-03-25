#pragma once

#include "base_viewport_controller.hpp"

class RightViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::inject;

	void load();
	void update();

private:
	static inline const fvec3 FRAME_COLOR = fvec3(0.175f);
	static inline const fvec3 BLACK = fvec3(0.0f);
	static inline const fvec3 WHITE = fvec3(1.0f);
	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
};