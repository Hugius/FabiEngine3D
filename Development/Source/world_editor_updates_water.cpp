#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateWaterMenu()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _leftWindow->getScreen("waterMenu");

		// If water existing, show water and enable bloom
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			_fe3d.waterEntity_show("@water");
		}
		else // Otherwise just show default sky
		{
			_fe3d.skyEntity_select("@defaultSky");
		}

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
				_leftWindow->setActiveScreen("waterManagement");
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_unloadWaterData();
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("worldEditorMenu");
				_currentWorldPart = WorldPart::NONE;
			}
		}
	}
}

void WorldEditor::_updateWaterManagement()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _leftWindow->getScreen("waterManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMesh");
			}
			else if (screen->getButton("effects")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEffects");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_leftWindow->setActiveScreen("waterOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenu");
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
			_fe3d.waterEntity_setPosition("@water", _waterPosition);
			_fe3d.waterEntity_setReflective("@water", _waterReflectionEnabled);
			_fe3d.waterEntity_setRefractive("@water", _waterRefractionEnabled);
			_fe3d.waterEntity_setWaving("@water", _waterDisplacementMapPath, _waterWaveHeightFactor, _waterWavingEnabled);
			_fe3d.waterEntity_setRippling("@water", _waterDudvMapPath, _waterRipplingEnabled);
			_fe3d.waterEntity_setSpecular("@water", _waterNormalMapPath, _waterSpecularFactor, _waterSpecularIntensity, _waterSpecularEnabled);
			_fe3d.waterEntity_setTransparency("@water", _waterTransparency);
			_fe3d.waterEntity_setColor("@water", _waterColor);
			_fe3d.waterEntity_setUvRepeat("@water", _waterUvRepeat);
			_fe3d.waterEntity_setSpeed("@water", _waterSpeed);

			// Update camera values
			_waterCameraHeight = _waterPosition.y + (_waterSize / 16.0f);
			_waterCameraDistance = _waterSize / 2.0f;
		}
	}
}

void WorldEditor::_updateWaterMesh()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterMesh")
	{
		auto screen = _leftWindow->getScreen("waterMesh");

		// Pressed LMB
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("size")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("size", "Size", _waterSize, vec2(0.0f), vec2(0.3f, 0.1f));
			}			
			else if (screen->getScrollingList("buttonList")->getButton("position")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("positionY", "Y", _waterPosition.y, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionX", "X", _waterPosition.x, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionZ", "Z", _waterPosition.z, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterManagement");
			}
		}

		// Holding LMB
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("up")->isHovered())
			{
				_waterPosition.y += _waterHeightSpeed;
				_fe3d.waterEntity_setPosition("@water", _waterPosition);
			}
			else if (screen->getScrollingList("buttonList")->getButton("down")->isHovered())
			{
				_waterPosition.y -= _waterHeightSpeed;
				_fe3d.waterEntity_setPosition("@water", _waterPosition);
			}
		}

		// Reload water plane if size changed
		if (_gui->getGlobalScreen()->checkValueForm("size", _waterSize, { 0.0f }))
		{
			_loadWaterEntity();
		}

		// Update position changes
		_gui->getGlobalScreen()->checkValueForm("positionX", _waterPosition.x, { });
		_gui->getGlobalScreen()->checkValueForm("positionY", _waterPosition.y, { });
		_gui->getGlobalScreen()->checkValueForm("positionZ", _waterPosition.z, { });
			
		// Button hoverabilities
		screen->getScrollingList("buttonList")->getButton("up")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getScrollingList("buttonList")->getButton("down")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
	}
}

void WorldEditor::_updateWaterEffects()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterEffects")
	{
		auto screen = _leftWindow->getScreen("waterEffects");
		string dudvMapPath = "User\\Assets\\Textures\\DudvMaps\\";
		string normalMapPath = "User\\Assets\\Textures\\NormalMaps\\";
		string displacementMapPath = "User\\Assets\\Textures\\DisplacementMaps\\";

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("uvRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV repeat", _waterUvRepeat, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("dudvMap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(dudvMapPath, "PNG");
				_waterDudvMapPath = (fileName == "") ? _waterDudvMapPath : (dudvMapPath + fileName);
				_fe3d.misc_clearTextureCache(_waterDudvMapPath);
			}
			else if (screen->getScrollingList("buttonList")->getButton("normalMap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(normalMapPath, "PNG");
				_waterNormalMapPath = (fileName == "") ? _waterNormalMapPath : (normalMapPath + fileName);
				_fe3d.misc_clearTextureCache(_waterNormalMapPath);
			}
			else if (screen->getScrollingList("buttonList")->getButton("displaceMap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(displacementMapPath, "PNG");
				_waterDisplacementMapPath = (fileName == "") ? _waterDisplacementMapPath : (displacementMapPath + fileName);
				_fe3d.misc_clearTextureCache(_waterDisplacementMapPath);
			}
			else if (screen->getScrollingList("buttonList")->getButton("isReflective")->isHovered())
			{
				_waterReflectionEnabled = !_waterReflectionEnabled;
			}
			else if (screen->getScrollingList("buttonList")->getButton("isRefractive")->isHovered())
			{
				_waterRefractionEnabled = !_waterRefractionEnabled;
			}
			else if (screen->getScrollingList("buttonList")->getButton("isWaving")->isHovered())
			{
				_waterWavingEnabled = !_waterWavingEnabled;
			}
			else if (screen->getScrollingList("buttonList")->getButton("isRippling")->isHovered())	
			{
				_waterRipplingEnabled = !_waterRipplingEnabled;
			}
			else if (screen->getScrollingList("buttonList")->getButton("isSpecular")->isHovered())
			{
				_waterSpecularEnabled = !_waterSpecularEnabled;
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterManagement");
			}
		}

		// Update GUI button contents
		auto reflectiveID = screen->getScrollingList("buttonList")->getButton("isReflective")->getTextfield()->getEntityID();
		auto refractiveID = screen->getScrollingList("buttonList")->getButton("isRefractive")->getTextfield()->getEntityID();
		auto wavingID = screen->getScrollingList("buttonList")->getButton("isWaving")->getTextfield()->getEntityID();
		auto ripplingID = screen->getScrollingList("buttonList")->getButton("isRippling")->getTextfield()->getEntityID();
		auto specularID = screen->getScrollingList("buttonList")->getButton("isSpecular")->getTextfield()->getEntityID();
		_fe3d.textEntity_setTextContent(reflectiveID, _waterReflectionEnabled ? "Reflective: ON" : "Reflective: OFF");
		_fe3d.textEntity_setTextContent(refractiveID, _waterRefractionEnabled ? "Refractive: ON" : "Refractive: OFF");
		_fe3d.textEntity_setTextContent(wavingID, _waterWavingEnabled ? "Waving: ON" : "Waving: OFF");
		_fe3d.textEntity_setTextContent(ripplingID, _waterRipplingEnabled ? "Rippling: ON" : "Rippling: OFF");
		_fe3d.textEntity_setTextContent(specularID, _waterSpecularEnabled ? "Specular: ON" : "Specular: OFF");

		// Check if value confirmed
		_gui->getGlobalScreen()->checkValueForm("uvRepeat", _waterUvRepeat);

		// Button hoverabilities
		screen->getScrollingList("buttonList")->getButton("isWaving")->setHoverable(_waterDisplacementMapPath != "");
		screen->getScrollingList("buttonList")->getButton("isRippling")->setHoverable(_waterDudvMapPath != "");
		screen->getScrollingList("buttonList")->getButton("isSpecular")->setHoverable(_waterNormalMapPath != "");
	}
}

void WorldEditor::_updateWaterOptions()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterOptions")
	{
		auto screen = _leftWindow->getScreen("waterOptions");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("speed")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("speed", "Water speed", _waterSpeed * 100000.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("transparency")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("transparency", "Transparency(0 - 10)", _waterTransparency * 10.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _waterColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _waterColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _waterColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.15f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("specularFactor")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("specularFactor", "Specular factor(0 - 256)", _waterSpecularFactor, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("specularIntensity")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("specularIntensity", "Specular intensity", _waterSpecularIntensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("waveHeight")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("waveHeight", "Wave height factor", _waterWaveHeightFactor * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterManagement");
			}
		}

		// Check if speed value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("speed", _waterSpeed))
		{
			_waterSpeed /= 100000.0f;
		}

		// Check if transparency value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("transparency", _waterTransparency))
		{
			_waterTransparency = std::clamp(_waterTransparency / 10.0f, 0.0f, 1.0f);
		}

		// Check if color R value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorR", _waterColor.r))
		{
			_waterColor.r = std::clamp(_waterColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Check if color G value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorG", _waterColor.g))
		{
			_waterColor.g = std::clamp(_waterColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Check if color B value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorB", _waterColor.b))
		{
			_waterColor.b = std::clamp(_waterColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Check if specular factor value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("specularFactor", _waterSpecularFactor))
		{
			_waterSpecularFactor = std::clamp(_waterSpecularFactor, 0.0f, 256.0f);
		}

		// Check if specular intensity value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("specularIntensity", _waterSpecularIntensity))
		{
			_waterSpecularIntensity /= 100.0f;
		}

		// Check if wave height value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("waveHeight", _waterWaveHeightFactor))
		{
			_waterWaveHeightFactor /= 100.0f;
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
		float x = _waterPosition.x + _waterCameraDistance * sin(_totalCameraRotation);
		float y = _waterPosition.y + _waterCameraHeight;
		float z = _waterPosition.z + _waterCameraDistance * cos(_totalCameraRotation);

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
		_fe3d.camera_enableLookat(_waterPosition);
	}
}