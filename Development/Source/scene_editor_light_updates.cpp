#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateLightingMenu()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuLighting")
		{
			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
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
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuLightingAmbient")
		{
			// Temporary values
			bool isEnabled = _fe3d.gfx_isAmbientLightingEnabled();
			Vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
			float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("enabled")->isHovered())
				{
					isEnabled = !isEnabled;
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("ambientColorR", "R", ambientLightingColor.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("ambientColorG", "G", ambientLightingColor.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("ambientColorB", "B", ambientLightingColor.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("ambientIntensity", "Ambient Intensity", ambientLightingIntensity * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
			}

			// Button text contents
			screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");

			// Color R value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("ambientColorR", ambientLightingColor.r))
			{
				ambientLightingColor.r = std::clamp(ambientLightingColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("ambientColorG", ambientLightingColor.g))
			{
				ambientLightingColor.g = std::clamp(ambientLightingColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("ambientColorB", ambientLightingColor.b))
			{
				ambientLightingColor.b = std::clamp(ambientLightingColor.b / 255.0f, 0.0f, 1.0f);
			}

			// Ambient intensity value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("ambientIntensity", ambientLightingIntensity))
			{
				ambientLightingIntensity = max(0.0f, ambientLightingIntensity / 100.0f);
			}

			// Disable ambient lighting
			if (_fe3d.gfx_isAmbientLightingEnabled())
			{
				_fe3d.gfx_disableAmbientLighting();
			}

			// Enable ambient lighting
			if(isEnabled)
			{
				_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
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
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuLightingDirectional")
		{
			// Temporary values
			bool isEnabled = _fe3d.gfx_isDirectionalLightingEnabled();
			Vec3 directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
			Vec3 directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
			float directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();
			float billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("enabled")->isHovered())
				{
					isEnabled = !isEnabled;
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("directionalColorR", "R", directionalLightingColor.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("directionalColorG", "G", directionalLightingColor.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("directionalColorB", "B", directionalLightingColor.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("position")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("positionX", "X", directionalLightingPosition.x, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("positionY", "Y", directionalLightingPosition.y, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->addValueForm("positionZ", "Z", directionalLightingPosition.z, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("directionalIntensity", "Directional Intensity", directionalLightingIntensity * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("billboardSize")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("billboardSize", "Billboard Size", billboardSize, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
			}

			// Button text contents
			screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");

			// Color R value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("directionalColorR", directionalLightingColor.r))
			{
				directionalLightingColor.r = std::clamp(directionalLightingColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("directionalColorG", directionalLightingColor.g))
			{
				directionalLightingColor.g = std::clamp(directionalLightingColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("directionalColorB", directionalLightingColor.b))
			{
				directionalLightingColor.b = std::clamp(directionalLightingColor.b / 255.0f, 0.0f, 1.0f);
			}

			// Update position values
			_gui.getGlobalScreen()->hasValueFormChanged("positionX", directionalLightingPosition.x);
			_gui.getGlobalScreen()->hasValueFormChanged("positionY", directionalLightingPosition.y);
			_gui.getGlobalScreen()->hasValueFormChanged("positionZ", directionalLightingPosition.z);

			// Directional intensity value conversion
			if (_gui.getGlobalScreen()->hasValueFormChanged("directionalIntensity", directionalLightingIntensity))
			{
				directionalLightingIntensity = max(0.0f, directionalLightingIntensity / 100.0f);
			}

			// Update billboard size value
			_gui.getGlobalScreen()->hasValueFormChanged("billboardSize", billboardSize);
			billboardSize = max(0.0f, billboardSize);

			// Update lightsource billboard
			_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
			_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
			_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);

			// Disable directional lighting
			if (_fe3d.gfx_isDirectionalLightingEnabled())
			{
				_fe3d.gfx_disableDirectionalLighting();
			}

			// Enable directional lighting
			if(isEnabled)
			{
				_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);
			}

			// Update buttons hoverability
			screen->getButton("color")->setHoverable(isEnabled);
			screen->getButton("position")->setHoverable(isEnabled);
			screen->getButton("intensity")->setHoverable(isEnabled);
			screen->getButton("billboardSize")->setHoverable(isEnabled);
		}
	}
}

void SceneEditor::_updatePointLightingMenu()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuLightingPoint")
		{
			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
					_isPlacingPointLight = false;
				}
				else if (screen->getButton("add")->isHovered())
				{
					_isPlacingPointLight = true;
					_fe3d.misc_centerCursor();
				}
			}
		}
	}
}