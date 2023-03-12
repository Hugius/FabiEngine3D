#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateBloomSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsBloom")
	{
		const auto isEnabled = _fe3d->graphics_isBloomEnabled();
		const auto type = _fe3d->graphics_getBloomType();
		const auto intensity = _fe3d->graphics_getBloomIntensity();
		const auto blurCount = _fe3d->graphics_getBloomBlurCount();
		const auto quality = _fe3d->graphics_getBloomQuality();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setBloomEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("type")->isHovered())
		{
			switch(type)
			{
				case BloomType::EVERYTHING:
				{
					_fe3d->graphics_setBloomType(BloomType::PARTS);

					break;
				}
				case BloomType::PARTS:
				{
					_fe3d->graphics_setBloomType(BloomType::EVERYTHING);

					break;
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * BLOOM_INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("blurCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blurCount", "Blur Count", blurCount, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setBloomIntensity(value / BLOOM_INTENSITY_FACTOR);
		}
		else if((_gui->getOverlay()->getValueFormId() == "blurCount") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setBloomBlurCount(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setBloomQuality(value);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");

		switch(type)
		{
			case BloomType::EVERYTHING:
			{
				screen->getButton("type")->setTextContent("Type: EVERYTHING");

				break;
			}
			case BloomType::PARTS:
			{
				screen->getButton("type")->setTextContent("Type: PARTS");

				break;
			}
		}
	}
}

void WorldEditor::_updateDofSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsDof")
	{
		const auto isEnabled = _fe3d->graphics_isDofEnabled();
		const auto isDynamic = _fe3d->graphics_isDofDynamic();
		const auto blurDistance = _fe3d->graphics_getDofBlurDistance();
		const auto dynamicDistance = _fe3d->graphics_getDofDynamicDistance();
		const auto quality = _fe3d->graphics_getDofQuality();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setDofEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isDynamic")->isHovered())
		{
			_fe3d->graphics_setDofDynamic(!isDynamic);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("dynamicDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("dynamicDistance", "Dynamic Distance", dynamicDistance, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("blurDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blurDistance", "Blur Distance", blurDistance, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "dynamicDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDofDynamicDistance(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "blurDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDofBlurDistance(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setDofQuality(value);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isDynamic")->setTextContent(isDynamic ? "Dynamic: ON" : "Dynamic: OFF");
	}
}

void WorldEditor::_updateLensFlareSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsLensFlare")
	{
		const auto isEnabled = _fe3d->graphics_isLensFlareEnabled();
		const auto flareMapPath = _fe3d->graphics_getLensFlareMapPath();
		const auto intensity = _fe3d->graphics_getLensFlareIntensity();
		const auto sensitivity = _fe3d->graphics_getLensFlareSensitivity();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setLensFlareEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("flareMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\miscellaneous\\flare_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseWindowsExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			_fe3d->misc_clearImageCache(filePath.substr(rootPath.size()));
			_fe3d->graphics_setLensFlareMap(filePath.substr(rootPath.size()));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * LENS_FLARE_INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sensitivity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sensitivity", "Sensitivity", (sensitivity * LENS_FLARE_SENSITIVITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setLensFlareIntensity(value / LENS_FLARE_INTENSITY_FACTOR);
		}
		else if((_gui->getOverlay()->getValueFormId() == "sensitivity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setLensFlareSensitivity(value / LENS_FLARE_SENSITIVITY_FACTOR);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}