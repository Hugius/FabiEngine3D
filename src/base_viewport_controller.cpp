#include "base_viewport_controller.hpp"

void BaseViewportController::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void BaseViewportController::inject(shared_ptr<GuiManager> gui)
{
	_gui = gui;
}

const vector<float> BaseViewportController::calculateButtonPositions(unsigned int buttonCount, float buttonHeight)
{
	vector<float> result;

	float freeSpace = (2.0f - (static_cast<float>(buttonCount) * buttonHeight));
	float gapSpace = (freeSpace / static_cast<float>(buttonCount + 1));
	float height = 1.0f;

	height -= (gapSpace + (buttonHeight / 2.0f));

	for(unsigned int i = 0; i < buttonCount; i++)
	{
		result.push_back(height);
		height -= (gapSpace + buttonHeight);
	}

	return result;
}

const float BaseViewportController::calculateTextWidth(const string& text, float charWidth)
{
	return static_cast<float>(text.size()) * charWidth;
}
