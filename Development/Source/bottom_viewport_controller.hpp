#pragma once

#include "viewport_controller.hpp"

class BottomViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void initialize() override;
	void update(float delta) override;

private:

};