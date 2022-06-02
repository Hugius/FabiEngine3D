#include "water_editor.hpp"
#include "tools.hpp"

void WaterEditor::_updateMiscellaneousMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuMiscellaneous")
	{
		const auto size = _fe3d->water_getSize(_currentWaterId);
		const auto rippleSpeed = _fe3d->water_getRippleSpeed(_currentWaterId);
		const auto waveSpeed = _fe3d->water_getWaveSpeed(_currentWaterId);
		const auto waveHeight = _fe3d->water_getWaveHeight(_currentWaterId);
		const auto maxDepth = _fe3d->water_getMaxDepth(_currentWaterId);
		const auto captureOffset = _fe3d->water_getCaptureOffset(_currentWaterId);
		const auto isCapturingSky = _fe3d->water_isCapturingSky(_currentWaterId);
		const auto isCapturingTerrain = _fe3d->water_isCapturingTerrain(_currentWaterId);
		const auto isCapturingModels = _fe3d->water_isCapturingModels(_currentWaterId);
		const auto isCapturingQuad3ds = _fe3d->water_isCapturingQuad3ds(_currentWaterId);
		const auto isCapturingText3ds = _fe3d->water_isCapturingText3ds(_currentWaterId);
		const auto isCapturingAabbs = _fe3d->water_isCapturingAabbs(_currentWaterId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("size", "Size", size, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveHeight", "Wave Height", (waveHeight * WAVE_HEIGHT_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("maxDepth")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDepth", "Max Depth", maxDepth, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rippleSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rippleSpeedX", "X", (rippleSpeed.x * RIPPLE_SPEED_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("rippleSpeedY", "Y", (rippleSpeed.y * RIPPLE_SPEED_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("waveSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveSpeedX", "X", (waveSpeed.x * WAVE_SPEED_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("waveSpeedY", "Y", (waveSpeed.y * WAVE_SPEED_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("captureOffset")->isHovered())
		{
			_gui->getOverlay()->openValueForm("captureOffset", "Capture Offset", captureOffset, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isCapturingSky")->isHovered())
		{
			_fe3d->water_setCaptureSky(_currentWaterId, !isCapturingSky);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isCapturingTerrain")->isHovered())
		{
			_fe3d->water_setCaptureTerrain(_currentWaterId, !isCapturingTerrain);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isCapturingModels")->isHovered())
		{
			_fe3d->water_setCaptureModels(_currentWaterId, !isCapturingModels);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isCapturingQuad3ds")->isHovered())
		{
			_fe3d->water_setCaptureQuad3ds(_currentWaterId, !isCapturingQuad3ds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isCapturingText3ds")->isHovered())
		{
			_fe3d->water_setCaptureText3ds(_currentWaterId, !isCapturingText3ds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isCapturingAabbs")->isHovered())
		{
			_fe3d->water_setCaptureAabbs(_currentWaterId, !isCapturingAabbs);
		}

		if((_gui->getOverlay()->getValueFormId() == "size") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setSize(_currentWaterId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "rippleSpeedX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setRippleSpeed(_currentWaterId, fvec2((value / RIPPLE_SPEED_FACTOR), rippleSpeed.y));
		}
		else if((_gui->getOverlay()->getValueFormId() == "rippleSpeedY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setRippleSpeed(_currentWaterId, fvec2(rippleSpeed.x, (value / RIPPLE_SPEED_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "waveSpeedX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setWaveSpeed(_currentWaterId, fvec2((value / WAVE_SPEED_FACTOR), waveSpeed.y));
		}
		else if((_gui->getOverlay()->getValueFormId() == "waveSpeedY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setWaveSpeed(_currentWaterId, fvec2(waveSpeed.x, (value / WAVE_SPEED_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "waveHeight") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setWaveHeight(_currentWaterId, (value / WAVE_HEIGHT_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "maxDepth") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setMaxDepth(_currentWaterId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "captureOffset") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->water_setCaptureOffset(_currentWaterId, value);
		}

		screen->getButton("isCapturingSky")->setTextContent(isCapturingSky ? "Sky: ON" : "Sky: OFF");
		screen->getButton("isCapturingTerrain")->setTextContent(isCapturingTerrain ? "Terrain: ON" : "Terrain: OFF");
		screen->getButton("isCapturingModels")->setTextContent(isCapturingModels ? "Models: ON" : "Models: OFF");
		screen->getButton("isCapturingQuad3ds")->setTextContent(isCapturingQuad3ds ? "Quad3Ds: ON" : "Quad3Ds: OFF");
		screen->getButton("isCapturingText3ds")->setTextContent(isCapturingText3ds ? "Text3Ds: ON" : "Text3Ds: OFF");
		screen->getButton("isCapturingAabbs")->setTextContent(isCapturingAabbs ? "AABBs: ON" : "AABBs: OFF");
	}
}