#include "base_viewport_controller.hpp"

BaseViewportController::BaseViewportController(FabiEngine3D& fe3d, GuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

const vector<float> BaseViewportController::calculateButtonPositions(unsigned int buttonCount, float buttonHeight)
{
	// Positions to return
	vector<float> result;

	// Pre-calculations
	float freeSpace = (2.0f - (static_cast<float>(buttonCount) * buttonHeight));
	float gapSpace = freeSpace / static_cast<float>(buttonCount + 1);
	float height = 1.0f;

	// First position
	height -= (gapSpace + (buttonHeight / 2.0f));

	// The rest of the positions
	for(unsigned int i = 0; i < buttonCount; i++)
	{
		result.push_back(height);
		height -= (gapSpace + buttonHeight);
	}

	// Return
	return result;
}

const float BaseViewportController::calculateTextWidth(const string& text, float charWidth)
{
	return static_cast<float>(text.size()) * charWidth;
}
