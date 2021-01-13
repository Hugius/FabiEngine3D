#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateMainLightingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuLighting")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (screen->getButton("ambient")->isHovered()) // Ambient light button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLightingAmbient");
				}
				else if (screen->getButton("directional")->isHovered()) // Directional light button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLightingDirectional");
				}
				else if (screen->getButton("point")->isHovered()) // Point light button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLightingPoint");
				}
			}
		}
	}
}

void SceneEditor::_updateAmbientLightingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		if (screen->getID() == "sceneEditorMenuLightingAmbient")
		{
			// Temporary values
			Vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
			float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("ambientColorR", "R(0-255)", ambientLightingColor.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("ambientColorG", "G(0-255)", ambientLightingColor.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("ambientColorB", "B(0-255)", ambientLightingColor.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("ambientIntensity", "Ambient intensity (%)", ambientLightingIntensity * 100.0f, Vec2(0.0f), Vec2(0.3f, 0.1f));
				}
			}

			// Ambient value conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientIntensity", ambientLightingIntensity))
			{
				ambientLightingIntensity /= 100.0f;
			}

			// Color R values conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientColorR", ambientLightingColor.r))
			{
				ambientLightingColor.r = std::clamp(ambientLightingColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G values conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientColorG", ambientLightingColor.g))
			{
				ambientLightingColor.g = std::clamp(ambientLightingColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B values conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientColorB", ambientLightingColor.b))
			{
				ambientLightingColor.b = std::clamp(ambientLightingColor.b / 255.0f, 0.0f, 1.0f);
			}

			// Update ambient lighting
			_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
		}
	}
}

void SceneEditor::_updateDirectionalLightingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		if (screen->getID() == "sceneEditorMenuLightingDirectional")
		{
			// Temporary values
			Vec3 directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
			Vec3 directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
			float directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();
			float billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("directionalColorR", "R(0-255)", directionalLightingColor.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("directionalColorG", "G(0-255)", directionalLightingColor.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("directionalColorB", "B(0-255)", directionalLightingColor.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("position")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("positionX", "X", directionalLightingPosition.x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("positionY", "Y", directionalLightingPosition.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("positionZ", "Z", directionalLightingPosition.z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("directionalIntensity", "Directional intensity(%)", directionalLightingIntensity * 100.0f, Vec2(0.0f), Vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("billboardSize")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("billboardSize", "Billboard size", billboardSize, Vec2(0.0f), Vec2(0.3f, 0.1f));
				}
			}

			// Color R values conversion
			if (_gui.getGlobalScreen()->checkValueForm("directionalColorR", directionalLightingColor.r))
			{
				directionalLightingColor.r = std::clamp(directionalLightingColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G values conversion
			if (_gui.getGlobalScreen()->checkValueForm("directionalColorG", directionalLightingColor.g))
			{
				directionalLightingColor.g = std::clamp(directionalLightingColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B values conversion
			if (_gui.getGlobalScreen()->checkValueForm("directionalColorB", directionalLightingColor.b))
			{
				directionalLightingColor.b = std::clamp(directionalLightingColor.b / 255.0f, 0.0f, 1.0f);
			}

			// Update position values
			_gui.getGlobalScreen()->checkValueForm("positionX", directionalLightingPosition.x);
			_gui.getGlobalScreen()->checkValueForm("positionY", directionalLightingPosition.y);
			_gui.getGlobalScreen()->checkValueForm("positionZ", directionalLightingPosition.z);

			// Directional intensity value conversion
			if (_gui.getGlobalScreen()->checkValueForm("directionalIntensity", directionalLightingIntensity))
			{
				directionalLightingIntensity /= 100.0f;
			}

			// Update billboard size value
			_gui.getGlobalScreen()->checkValueForm("billboardSize", billboardSize);

			// Update directional lighting
			_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);

			// Update lightsource billboard
			_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
			_fe3d.billboardEntity_setSize("@@lightSource",  Vec2(billboardSize));
			_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);
		}
	}
}

void SceneEditor::_updatePointLightingMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuLightingPoint")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
					_isPlacingPointlight = false;
				}
				else if (screen->getButton("add")->isHovered())
				{
					_isPlacingPointlight = true;
					_fe3d.misc_setCursorPosition(_fe3d.misc_convertToScreenCoords(Vec2(0.5f)));
				}
			}
		}
	}
}