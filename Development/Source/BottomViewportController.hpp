#pragma once

#include "ViewportController.hpp"

class BottomViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void update(float delta) override;

private:

};