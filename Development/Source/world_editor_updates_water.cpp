#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateWaterMenu()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _window->getScreen("waterMenu");

		// Show sky
		if (_fe3d.skyEntity_isExisting("@sky"))
		{
			_fe3d.skyEntity_select("@sky");
			_fe3d.skyEntity_show("@sky");
		}

		// Show terrain
		if (_fe3d.terrainEntity_isExisting("@terrain"))
		{
			_fe3d.terrainEntity_show("@terrain");
		}

		// If water existing, show water and enable bloom
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			_fe3d.waterEntity_show("@water");
		}
		else // Otherwise just show default sky
		{
			_fe3d.skyEntity_select("@defaultSky");
		}

		// Update water management if possible
		_updateWaterManagement();

		// Update buttons hoverability
		screen->getButton("create")->setHoverable(!_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("edit")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("remove")->setHoverable(_fe3d.waterEntity_isExisting("@water"));

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered() || screen->getButton("edit")->isHovered())
			{
				_window->setActiveScreen("waterManagement");
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_unloadWaterData();
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("worldManagement");
				_currentWorldPart = WorldPart::NONE;
			}
		}
	}
}

void WorldEditor::_updateWaterManagement()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _window->getScreen("waterManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_window->setActiveScreen("waterMesh");
			}
			else if (screen->getButton("effects")->isHovered())
			{
				_window->setActiveScreen("waterEffects");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_window->setActiveScreen("waterOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("waterMenu");

				// Hide sky
				if (_fe3d.skyEntity_isExisting("@sky"))
				{
					_fe3d.skyEntity_hide("@sky");
					_fe3d.skyEntity_select("@defaultSky");
				}

				// Hide terrain
				if (_fe3d.terrainEntity_isExisting("@terrain"))
				{
					_fe3d.terrainEntity_hide("@terrain");
				}

				// Hide water
				if (_fe3d.waterEntity_isExisting("@water"))
				{
					_fe3d.waterEntity_hide("@water");
				}
			}
		}

		// Screen hoverabilities
		screen->getButton("effects")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("options")->setHoverable(_fe3d.waterEntity_isExisting("@water"));

		// Update sub-menus
		_updateWaterCamera();
		_updateWaterMesh();
		_updateWaterEffects();
		_updateWaterOptions();

		// Dnyamic water updates
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			// Update water properties
			_fe3d.waterEntity_setReflective("@water", _waterReflectionEnabled);
			_fe3d.waterEntity_setRefractive("@water", _waterRefractionEnabled);
			_fe3d.waterEntity_setWaving("@water", _waterWavingEnabled);
			_fe3d.waterEntity_setRippling("@water", _waterDudvmapPath, _waterRipplingEnabled);
			_fe3d.waterEntity_setSpecular("@water", _waterNormalmapPath, _waterShininess, _waterSpecularEnabled);
			_fe3d.waterEntity_setTransparency("@water", _waterTransparency);
			_fe3d.waterEntity_setColor("@water", _waterColor);
			_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
			_fe3d.waterEntity_setUvRepeat("@water", _waterUvRepeat);
			_fe3d.waterEntity_setSpeed("@water", _waterSpeed);

			// Update camera values
			_waterCameraHeight = _waterHeight + (_waterSize / 16.0f);
			_waterCameraDistance = _waterSize / 2.0f;
		}
	}
}

void WorldEditor::_updateWaterMesh()
{
	if (_window->getActiveScreen()->getID() == "waterMesh")
	{
		auto screen = _window->getScreen("waterMesh");

		// Pressed LMB
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("size")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("size", "Size", _waterSize, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("height")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("height", "Height", _waterHeight, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("waterManagement");
			}
		}

		// Holding LMB
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("up")->isHovered())
			{
				_waterHeight += _waterHeightSpeed;
				_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
			}
			else if (screen->getScrollingList("buttonList")->getButton("down")->isHovered())
			{
				_waterHeight -= _waterHeightSpeed;
				_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
			}
		}

		// Check if height changed
		_gui->getGlobalScreen()->checkValueForm("height", _waterHeight);

		// Reload water plane if size changed
		if (_gui->getGlobalScreen()->checkValueForm("size", _waterSize, { 0.0f }))
		{
			_loadWaterEntity();
		}

		// Button hoverabilities
		screen->getScrollingList("buttonList")->getButton("height")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getScrollingList("buttonList")->getButton("up")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getScrollingList("buttonList")->getButton("down")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
	}
}

void WorldEditor::_updateWaterEffects()
{
	if (_window->getActiveScreen()->getID() == "waterEffects")
	{
		auto screen = _window->getScreen("waterEffects");
		string dudvmapPath = "User\\Assets\\Textures\\DudvMaps\\";
		string normalmapPath = "User\\Assets\\Textures\\NormalMaps\\";

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("uvRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV repeat", _waterUvRepeat, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("dudvmap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(dudvmapPath, "PNG");
				_waterDudvmapPath = (fileName == "") ? _waterDudvmapPath : (dudvmapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("normalmap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(normalmapPath, "PNG");
				_waterNormalmapPath = (fileName == "") ? _waterNormalmapPath : (normalmapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("reflective")->isHovered())
			{
				auto buttonID = screen->getScrollingList("buttonList")->getButton("reflective")->getTextfield()->getEntityID();
				_waterReflectionEnabled = !_waterReflectionEnabled;
				_fe3d.textEntity_setTextContent(buttonID, _waterReflectionEnabled ? "Reflective: ON" : "Reflective: OFF");
			}
			else if (screen->getScrollingList("buttonList")->getButton("refractive")->isHovered())
			{
				auto buttonID = screen->getScrollingList("buttonList")->getButton("refractive")->getTextfield()->getEntityID();
				_waterRefractionEnabled = !_waterRefractionEnabled;
				_fe3d.textEntity_setTextContent(buttonID, _waterRefractionEnabled ? "Refractive: ON" : "Refractive: OFF");
			}
			else if (screen->getScrollingList("buttonList")->getButton("waving")->isHovered())
			{
				auto buttonID = screen->getScrollingList("buttonList")->getButton("waving")->getTextfield()->getEntityID();
				_waterWavingEnabled = !_waterWavingEnabled;
				_fe3d.textEntity_setTextContent(buttonID, _waterWavingEnabled ? "Waving: ON" : "Waving: OFF");
			}
			else if (screen->getScrollingList("buttonList")->getButton("rippling")->isHovered())	
			{
				auto buttonID = screen->getScrollingList("buttonList")->getButton("rippling")->getTextfield()->getEntityID();
				_waterRipplingEnabled = !_waterRipplingEnabled;
				_fe3d.textEntity_setTextContent(buttonID, _waterRipplingEnabled ? "Rippling: ON" : "Rippling: OFF");
			}
			else if (screen->getScrollingList("buttonList")->getButton("specular")->isHovered())
			{
				auto buttonID = screen->getScrollingList("buttonList")->getButton("specular")->getTextfield()->getEntityID();
				_waterSpecularEnabled = !_waterSpecularEnabled;
				_fe3d.textEntity_setTextContent(buttonID, _waterSpecularEnabled ? "Specular: ON" : "Specular: OFF");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("waterManagement");
			}
		}

		// Check if value confirmed
		_gui->getGlobalScreen()->checkValueForm("uvRepeat", _waterUvRepeat);

		// Button hoverabilities
		screen->getScrollingList("buttonList")->getButton("rippling")->setHoverable(_waterDudvmapPath != "");
		screen->getScrollingList("buttonList")->getButton("specular")->setHoverable(_waterNormalmapPath != "");
	}
}

void WorldEditor::_updateWaterOptions()
{
	if (_window->getActiveScreen()->getID() == "waterOptions")
	{
		auto screen = _window->getScreen("waterOptions");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("speed")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("speed", "Water speed", _waterSpeed * 1000.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("transparency")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("transparency", "Transparency(0 - 10)", _waterTransparency * 10.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _waterColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _waterColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _waterColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.15f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("shininess")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("shininess", "Shininess(0 - 256)", _waterShininess, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("waterManagement");
			}
		}

		// Speed value conversion
		if (_gui->getGlobalScreen()->checkValueForm("speed", _waterSpeed))
		{
			_waterSpeed /= 1000.0f;
		}

		// Transparency value conversion
		if (_gui->getGlobalScreen()->checkValueForm("transparency", _waterTransparency))
		{
			_waterTransparency = std::clamp(_waterTransparency / 10.0f, 0.0f, 1.0f);
		}

		// Color R values conversion
		if (_gui->getGlobalScreen()->checkValueForm("colorR", _waterColor.r))
		{
			_waterColor.r = std::clamp(_waterColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Color G values conversion
		if (_gui->getGlobalScreen()->checkValueForm("colorG", _waterColor.g))
		{
			_waterColor.g = std::clamp(_waterColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Color B values conversion
		if (_gui->getGlobalScreen()->checkValueForm("colorB", _waterColor.b))
		{
			_waterColor.b = std::clamp(_waterColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Check if shininess confirmed
		if (_gui->getGlobalScreen()->checkValueForm("shininess", _waterShininess))
		{
			_waterShininess = std::clamp(_waterShininess, 0.0f, 256.0f);
		}
	}
}

void WorldEditor::_updateWaterCamera()
{
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		// Get scroll wheel input
		if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
		{
			float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) / _scrollWheelDivider;
			_cameraRotationSpeed += rotationAcceleration;
		}
		_cameraRotationSpeed *= 0.975f;
		_totalCameraRotation += _cameraRotationSpeed;

		// Calculate new camera position
		float x = _waterCameraDistance * sin(_totalCameraRotation);
		float y = _waterCameraHeight;
		float z = _waterCameraDistance * cos(_totalCameraRotation);

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
		_fe3d.camera_enableLookat(vec3(0.0f, _waterHeight, 0.0f));
	}
}