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
			bool isEnabled = _fe3d.gfx_isAmbientLightingEnabled();
			Vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
			float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("enabled")->isHovered())
				{
					isEnabled = !isEnabled;
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("ambientColorR", "R", ambientLightingColor.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("ambientColorG", "G", ambientLightingColor.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("ambientColorB", "B", ambientLightingColor.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("ambientIntensity", "Ambient intensity", ambientLightingIntensity * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
				}
			}

			// Enabled button content
			_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), isEnabled ? "Enabled: YES" : "Enabled: NO");

			// Color R value conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientColorR", ambientLightingColor.r))
			{
				ambientLightingColor.r = std::clamp(ambientLightingColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G value conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientColorG", ambientLightingColor.g))
			{
				ambientLightingColor.g = std::clamp(ambientLightingColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B value conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientColorB", ambientLightingColor.b))
			{
				ambientLightingColor.b = std::clamp(ambientLightingColor.b / 255.0f, 0.0f, 1.0f);
			}

			// Ambient intensity value conversion
			if (_gui.getGlobalScreen()->checkValueForm("ambientIntensity", ambientLightingIntensity))
			{
				ambientLightingIntensity = std::max(0.0f, ambientLightingIntensity / 100.0f);
			}

			// Enable or disable ambient lighting
			if (isEnabled)
			{
				_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
			}
			else
			{
				_fe3d.gfx_disableAmbientLighting();
			}

			// Update buttons hoverability
			screen->getButton("color")->setHoverable(isEnabled);
			screen->getButton("intensity")->setHoverable(isEnabled);
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
			bool isEnabled = _fe3d.gfx_isDirectionalLightingEnabled();
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
				else if (screen->getButton("enabled")->isHovered())
				{
					isEnabled = !isEnabled;
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("directionalColorR", "R", directionalLightingColor.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("directionalColorG", "G", directionalLightingColor.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("directionalColorB", "B", directionalLightingColor.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("position")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("positionX", "X", directionalLightingPosition.x, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("positionY", "Y", directionalLightingPosition.y, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("positionZ", "Z", directionalLightingPosition.z, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("directionalIntensity", "Directional intensity", directionalLightingIntensity * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("billboardSize")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("billboardSize", "Billboard size", billboardSize, Vec2(0.0f), Vec2(0.15f, 0.1f));
				}
			}

			// Enabled button content
			_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), isEnabled ? "Enabled: YES" : "Enabled: NO");

			// Color R value conversion
			if (_gui.getGlobalScreen()->checkValueForm("directionalColorR", directionalLightingColor.r))
			{
				directionalLightingColor.r = std::clamp(directionalLightingColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G value conversion
			if (_gui.getGlobalScreen()->checkValueForm("directionalColorG", directionalLightingColor.g))
			{
				directionalLightingColor.g = std::clamp(directionalLightingColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B value conversion
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
				directionalLightingIntensity = std::max(0.0f, directionalLightingIntensity / 100.0f);
			}

			// Update billboard size value
			_gui.getGlobalScreen()->checkValueForm("billboardSize", billboardSize);
			billboardSize = std::max(0.0f, billboardSize);

			// Update lightsource billboard
			_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
			_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
			_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);

			// Enable or disable directional lighting
			if (isEnabled)
			{
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);
			}
			else
			{
				_fe3d.gfx_disableDirectionalLighting();
			}

			// Update buttons hoverability
			screen->getButton("color")->setHoverable(isEnabled);
			screen->getButton("position")->setHoverable(isEnabled);
			screen->getButton("intensity")->setHoverable(isEnabled);
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