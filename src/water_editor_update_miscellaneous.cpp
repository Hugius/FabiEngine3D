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

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("size", "Size", size, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveHeight", "Wave Height", (waveHeight * WAVE_HEIGHT_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("maxDepth")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDepth", "Max Depth", maxDepth, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rippleSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rippleSpeedX", "X", (rippleSpeed.x * RIPPLE_SPEED_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("rippleSpeedY", "Y", (rippleSpeed.y * RIPPLE_SPEED_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("waveSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveSpeedX", "X", (waveSpeed.x * WAVE_SPEED_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("waveSpeedY", "Y", (waveSpeed.y * WAVE_SPEED_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
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
	}
}