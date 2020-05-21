#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_loadWaterPlane()
{
	// Remove existing terrain
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

	// Add new terrain
	_fe3d.waterEntity_add("@water", vec3(0.0f, _waterHeight, 0.0f), _waterSize);
	_fe3d.waterEntity_select("@water");
}

void WorldEditor::_upateWaterManagement()
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
				_window->setActiveScreen("worldManagement");
				_currentWorldPart = WorldPart::NONE;
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

		// Update water properties
		if (_fe3d.waterEntity_isExisting("@water"))
		{
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
				_addValueForm("size", "Size", _waterSize);
			}
			else if (screen->getScrollingList("buttonList")->getButton("height")->isHovered())
			{
				_addValueForm("height", "Height", _waterHeight);
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
				_waterHeight += 0.01f * _delta;
				_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
			}
			else if (screen->getScrollingList("buttonList")->getButton("down")->isHovered())
			{
				_waterHeight -= 0.01f * _delta;
				_fe3d.waterEntity_setSurfaceHeight("@water", _waterHeight);
			}
		}

		// Check if values confirmed
		float oldSize = _waterSize;
		_checkValueForm("size", _waterSize);
		_checkValueForm("height", _waterHeight);

		// Reload water plane if size changed
		if (_waterSize != oldSize)
		{
			if (_waterSize != 0.0f)
			{
				_loadWaterPlane();
			}
		}

		// Miscellaneous
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			// Update camera values
			_waterCameraHeight = _waterHeight + (_waterSize / 16.0f);
			_waterCameraDistance = _waterSize / 2.0f;

			// Update wireframe visibility
			if (!_gui->isFocused())
			{
				_fe3d.input_getKeyToggled(Input::KEY_W) ? _fe3d.misc_enableWireframeRendering() : _fe3d.misc_disableWireframeRendering();
			}
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
				_addValueForm("uvRepeat", "UV repeat", _waterUvRepeat);
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
		_checkValueForm("uvRepeat", _waterUvRepeat);

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
				_addValueForm("speed", "Water speed", _waterSpeed * 1000.0f);
			}
			else if (screen->getScrollingList("buttonList")->getButton("transparency")->isHovered())
			{
				_addValueForm("transparency", "Transparency(0 - 10)", _waterTransparency * 10.0f);
			}
			else if (screen->getScrollingList("buttonList")->getButton("color")->isHovered())
			{

			}
			else if (screen->getScrollingList("buttonList")->getButton("shininess")->isHovered())
			{
				_addValueForm("shininess", "Shininess(0 - ~)", _waterShininess);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("waterManagement");
			}
		}

		// Check if value confirmed
		float oldSpeed = _waterSpeed;
		_checkValueForm("speed", _waterSpeed);
		if (oldSpeed != _waterSpeed)
		{
			_waterSpeed /= 1000.0f;
		}

		float oldTransparency = _waterTransparency;
		_checkValueForm("transparency", _waterTransparency);
		if (oldTransparency != _waterTransparency)
		{
			_waterTransparency /= 10.0f;
			_waterTransparency = std::clamp(_waterTransparency, 0.0f, 1.0f);
		}

		_checkValueForm("shininess", _waterShininess);
	}
}

void WorldEditor::_updateWaterCamera()
{
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		// Get scroll wheel input
		float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) * 0.001f;
		_cameraRotationSpeed += rotationAcceleration;
		_cameraRotationSpeed *= 0.995f;
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