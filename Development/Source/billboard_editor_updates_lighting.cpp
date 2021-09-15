#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateLightingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "billboardEditorMenuLighting")
	{
		// Temporary values
		auto lightness = _fe3d.billboardEntity_getLightness(_currentBillboardID);
		auto isReflected = _fe3d.billboardEntity_isReflected(_currentBillboardID);
		auto isShadowed = _fe3d.billboardEntity_isShadowed(_currentBillboardID);
		auto isBright = _fe3d.billboardEntity_isBright(_currentBillboardID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (lightness * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			isShadowed = !isShadowed;
			_fe3d.billboardEntity_setShadowed(_currentBillboardID, isShadowed);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			isReflected = !isReflected;
			_fe3d.billboardEntity_setReflected(_currentBillboardID, isReflected);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			isBright = !isBright;
			_fe3d.billboardEntity_setBright(_currentBillboardID, isBright);
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness, {}))
		{
			lightness /= 100.0f;
			_fe3d.billboardEntity_setLightness(_currentBillboardID, lightness);
		}

		// Update button text contents
		screen->getButton("isBright")->changeTextContent(isBright ? "Bright: ON" : "Bright : OFF");
		screen->getButton("isReflected")->changeTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isShadowed")->changeTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}