#include "water_editor.hpp"
#include "tools.hpp"

void WaterEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuMiscellaneous")
	{
		const auto size = _fe3d->water_getSize(_currentWaterId);
		const auto rippleSpeed = _fe3d->water_getRippleSpeed(_currentWaterId);
		const auto waveSpeed = _fe3d->water_getWaveSpeed(_currentWaterId);
		const auto waveHeight = _fe3d->water_getWaveHeight(_currentWaterId);
		const auto maxDepth = _fe3d->water_getMaxDepth(_currentWaterId);

		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("size", "Size", size, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveHeight", "Wave Height", (waveHeight * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("maxDepth")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDepth", "Max Depth", maxDepth, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("rippleSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rippleSpeedX", "X", (rippleSpeed.x * 100000.0f), fvec2(-0.15f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("rippleSpeedY", "Y", (rippleSpeed.y * 100000.0f), fvec2(0.15f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("waveSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveSpeedX", "X", (waveSpeed.x * 100000.0f), fvec2(-0.15f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("waveSpeedY", "Y", (waveSpeed.y * 100000.0f), fvec2(0.15f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "size") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setSize(_currentWaterId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "rippleSpeedX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setRippleSpeed(_currentWaterId, fvec2((content / 100000.0f), rippleSpeed.y));
		}
		if((_gui->getOverlay()->getValueFormId() == "rippleSpeedY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setRippleSpeed(_currentWaterId, fvec2(rippleSpeed.x, (content / 100000.0f)));
		}
		if((_gui->getOverlay()->getValueFormId() == "waveSpeedX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setWaveSpeed(_currentWaterId, fvec2((content / 100000.0f), waveSpeed.y));
		}
		if((_gui->getOverlay()->getValueFormId() == "waveSpeedY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setWaveSpeed(_currentWaterId, fvec2(waveSpeed.x, (content / 100000.0f)));
		}
		if((_gui->getOverlay()->getValueFormId() == "waveHeight") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setWaveHeight(_currentWaterId, (content / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "maxDepth") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setMaxDepth(_currentWaterId, content);
		}
	}
}