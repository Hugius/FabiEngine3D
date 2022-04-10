#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettings")
	{
		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsLighting");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("graphics")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("editorSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("editorSpeed", "Editor Speed", _editorSpeed, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "editorSpeed") && _gui->getOverlay()->isValueFormConfirmed())
		{
			_editorSpeed = max(0.0f, static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent())));
		}
	}
}

void WorldEditor::_updateLightingSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsLighting")
	{
		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("ambient")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsLightingAmbient");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("directional")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsLightingDirectional");
		}
	}
}

void WorldEditor::_updateGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphics")
	{
		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("shadows")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsShadows");
			_fe3d->graphics_setShadowCircleEnabled(true);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("reflections")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsReflections");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("refractions")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsRefractions");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("dof")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsDof");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("fog")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsFog");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("lensFlare")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsLensFlare");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("skyExposure")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsSkyExposure");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("bloom")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphicsBloom");
		}
	}
}