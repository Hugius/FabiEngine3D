#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateOptionsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "billboardEditorMenuOptions")
	{
		// Temporary values
		auto textContent = _fe3d.billboardEntity_getTextContent(_currentBillboardID);
		auto color = _fe3d.billboardEntity_getColor(_currentBillboardID);
		auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
		auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
		auto uvRepeat = _fe3d.billboardEntity_getUvRepeat(_currentBillboardID);
		auto isText = _fe3d.billboardEntity_isText(_currentBillboardID);
		auto hasDiffuseMap = _fe3d.billboardEntity_hasDiffuseMap(_currentBillboardID);
		auto hasEmissionMap = _fe3d.billboardEntity_hasEmissionMap(_currentBillboardID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textContent")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("textContent", "Text content", textContent, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uvRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("facingX")->isHovered())
		{
			isFacingX = !isFacingX;
			_fe3d.billboardEntity_setCameraFacingX(_currentBillboardID, isFacingX);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("facingY")->isHovered())
		{
			isFacingY = !isFacingY;
			_fe3d.billboardEntity_setCameraFacingY(_currentBillboardID, isFacingY);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Reset rotations if not facing camera
		Vec3 rotation = _fe3d.billboardEntity_getRotation(_currentBillboardID);
		if (!isFacingX)
		{
			rotation.x = 0.0f;
			rotation.z = 0.0f;
		}
		if (!isFacingY)
		{
			rotation.y = 0.0f;
		}
		_fe3d.billboardEntity_setRotation(_currentBillboardID, rotation);

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("textContent", textContent, {}))
		{
			_fe3d.misc_clearFontCache(_fe3d.billboardEntity_getFontPath(_currentBillboardID));
			_fe3d.misc_clearTextCache(textContent, _fe3d.billboardEntity_getFontPath(_currentBillboardID));
			_fe3d.billboardEntity_setTextContent(_currentBillboardID, textContent);
		}
		if (_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat, {}))
		{
			_fe3d.billboardEntity_setUvRepeat(_currentBillboardID, uvRepeat);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d.billboardEntity_setColor(_currentBillboardID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d.billboardEntity_setColor(_currentBillboardID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d.billboardEntity_setColor(_currentBillboardID, color);
		}

		// Update buttons hoverability
		screen->getButton("textContent")->setHoverable(isText);
		screen->getButton("uvRepeat")->setHoverable((hasDiffuseMap && !isText) || hasEmissionMap);

		// Update button text contents
		screen->getButton("facingX")->changeTextContent(isFacingX ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("facingY")->changeTextContent(isFacingY ? "Facing Y: ON" : "Facing Y: OFF");
	}
}