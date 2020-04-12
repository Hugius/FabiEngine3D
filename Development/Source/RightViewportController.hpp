#pragma once

#include "ViewportController.hpp"

class RightViewportController final : public ViewportController
{
public:
	using ViewportController::ViewportController;

	void update(float delta) override;

private:

};