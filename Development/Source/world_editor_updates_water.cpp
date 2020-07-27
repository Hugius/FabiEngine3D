#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateWaterMenuMain()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _leftWindow->getScreen("waterMenuMain");

		// If water existing, show water and enable bloom
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			_fe3d.waterEntity_show("@water");
		}
		else // Otherwise just show default sky
		{
			_fe3d.skyEntity_select("@@sky");
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
		_updateWaterMenuChoice();

		// Update buttons hoverability
		screen->getButton("create")->setHoverable(!_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("edit")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("remove")->setHoverable(_fe3d.waterEntity_isExisting("@water"));

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered())
			{
				_loadWaterEntity();
				_leftWindow->setActiveScreen("waterMenuChoice");
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuChoice");
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

void WorldEditor::_updateWaterMenuChoice()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _leftWindow->getScreen("waterMenuChoice");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuMesh");
			}
			else if (screen->getButton("effects")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuEffects");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuMain");
			}
		}

		// Screen hoverabilities
		screen->getButton("effects")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("options")->setHoverable(_fe3d.waterEntity_isExisting("@water"));

		// Update sub-menus
		_updateWaterCamera();
		_updateWaterMenuMesh();
		_updateWaterMenuEffects();
		_updateWaterMenuOptions();
	}
}

void WorldEditor::_updateWaterMenuMesh()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterMenuMesh")
	{
		auto screen = _leftWindow->getScreen("waterMenuMesh");
		vec3 waterPosition = _fe3d.waterEntity_getPosition("@water");
		float waterSize = _fe3d.waterEntity_getSize("@water");

		// Button hoverabilities
		screen->getScrollingList("buttonList")->getButton("up")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getScrollingList("buttonList")->getButton("down")->setHoverable(_fe3d.waterEntity_isExisting("@water"));

		// Pressed LMB
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("position")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("positionY", "Y", waterPosition.y, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionX", "X", waterPosition.x, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionZ", "Z", waterPosition.z, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("size")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("size", "Size", waterSize, vec2(0.0f), vec2(0.3f, 0.1f));
			}			
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuChoice");
			}
		}

		// Holding LMB
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("up")->isHovered())
			{
				_fe3d.waterEntity_setPosition("@water", waterPosition + vec3(0.0f, 0.1f, 0.0f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("down")->isHovered())
			{
				_fe3d.waterEntity_setPosition("@water", waterPosition - vec3(0.0f, 0.1f, 0.0f));
			}
		}

		// Update size changes
		if (_gui->getGlobalScreen()->checkValueForm("size", waterSize, { 0.0f }))
		{
			_fe3d.waterEntity_setSize("@water", waterSize);
		}

		// Update position changes
		_gui->getGlobalScreen()->checkValueForm("positionX", waterPosition.x, { });
		_gui->getGlobalScreen()->checkValueForm("positionY", waterPosition.y, { });
		_gui->getGlobalScreen()->checkValueForm("positionZ", waterPosition.z, { });
		_fe3d.waterEntity_setPosition("@water", waterPosition);
	}
}

void WorldEditor::_updateWaterMenuEffects()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterMenuEffects")
	{
		// Variables
		auto screen = _leftWindow->getScreen("waterMenuEffects");
		string dudvMapPath = "User\\Assets\\Textures\\DudvMaps\\";
		string normalMapPath = "User\\Assets\\Textures\\NormalMaps\\";
		string displacementMapPath = "User\\Assets\\Textures\\DisplacementMaps\\";
		float uvRepeat = _fe3d.waterEntity_getUvRepeat("@water");
		bool isReflective = _fe3d.waterEntity_isReflective("@water");
		bool isRefractive = _fe3d.waterEntity_isRefractive("@water");
		bool isWaving = _fe3d.waterEntity_isWaving("@water");
		bool isRippling = _fe3d.waterEntity_isRippling("@water");
		bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted("@water");

		// Button hoverabilities
		string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath("@water");
		string dudvMapPath = _fe3d.waterEntity_getDudvMapPath("@water");
		string normalMapPath = _fe3d.waterEntity_getNormalMapPath("@water");
		screen->getScrollingList("buttonList")->getButton("isWaving")->setHoverable(displacementMapPath != "");
		screen->getScrollingList("buttonList")->getButton("isRippling")->setHoverable(dudvMapPath != "");
		screen->getScrollingList("buttonList")->getButton("isSpecular")->setHoverable(normalMapPath != "");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("uvRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV repeat", uvRepeat, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("dudvMap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(dudvMapPath, "PNG");

				// Check if not cancelled
				if (fileName != "")
				{
					_fe3d.misc_clearTextureCache(dudvMapPath + fileName);
					_fe3d.waterEntity_setDudvMap("@water", dudvMapPath + fileName);
				}
			}
			else if (screen->getScrollingList("buttonList")->getButton("normalMap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(normalMapPath, "PNG");

				// Check if not cancelled
				if (fileName != "")
				{
					_fe3d.misc_clearTextureCache(normalMapPath + fileName);
					_fe3d.waterEntity_setDudvMap("@water", normalMapPath + fileName);
				}
			}
			else if (screen->getScrollingList("buttonList")->getButton("displaceMap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(displacementMapPath, "PNG");

				// Check if not cancelled
				if (fileName != "")
				{
					_fe3d.misc_clearTextureCache(displacementMapPath + fileName);
					_fe3d.waterEntity_setDudvMap("water", displacementMapPath + fileName);
				}
			}
			else if (screen->getScrollingList("buttonList")->getButton("isReflective")->isHovered())
			{
				isReflective = !isReflective;
				_fe3d.waterEntity_setReflective("@water", isReflective);
			}
			else if (screen->getScrollingList("buttonList")->getButton("isRefractive")->isHovered())
			{
				isRefractive = !isRefractive;
				_fe3d.waterEntity_setRefractive("@water", isRefractive);
			}
			else if (screen->getScrollingList("buttonList")->getButton("isWaving")->isHovered())
			{
				isWaving = !isWaving;
				_fe3d.waterEntity_setWaving("@water", isWaving);
			}
			else if (screen->getScrollingList("buttonList")->getButton("isRippling")->isHovered())	
			{
				isRippling = !isRippling;
				_fe3d.waterEntity_setRippling("@water", isRippling);
			}
			else if (screen->getScrollingList("buttonList")->getButton("isSpecular")->isHovered())
			{
				isSpecularLighted = !isSpecularLighted;
				_fe3d.waterEntity_setSpecularLighted("@water", isSpecularLighted);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuChoice");
			}
		}

		// Update GUI button contents
		auto reflectiveID = screen->getScrollingList("buttonList")->getButton("isReflective")->getTextfield()->getEntityID();
		auto refractiveID = screen->getScrollingList("buttonList")->getButton("isRefractive")->getTextfield()->getEntityID();
		auto wavingID = screen->getScrollingList("buttonList")->getButton("isWaving")->getTextfield()->getEntityID();
		auto ripplingID = screen->getScrollingList("buttonList")->getButton("isRippling")->getTextfield()->getEntityID();
		auto specularID = screen->getScrollingList("buttonList")->getButton("isSpecular")->getTextfield()->getEntityID();
		_fe3d.textEntity_setTextContent(reflectiveID, isReflective ? "Reflective: ON" : "Reflective: OFF");
		_fe3d.textEntity_setTextContent(refractiveID, isRefractive ? "Refractive: ON" : "Refractive: OFF");
		_fe3d.textEntity_setTextContent(wavingID, isWaving ? "Waving: ON" : "Waving: OFF");
		_fe3d.textEntity_setTextContent(ripplingID, isRippling ? "Rippling: ON" : "Rippling: OFF");
		_fe3d.textEntity_setTextContent(specularID, isSpecularLighted ? "Specular: ON" : "Specular: OFF");

		// Update uvRepeat changes
		_gui->getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat);
	}
}

void WorldEditor::_updateWaterMenuOptions()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterMenuOptions")
	{
		auto screen = _leftWindow->getScreen("waterMenuOptions");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("speed")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("speed", "Water speed", waterSpeed * 100000.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("transparency")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("transparency", "Transparency(0 - 10)", waterTransparency * 10.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", waterColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", waterColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", waterColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.15f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("specularFactor")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("specularFactor", "Specular factor(0 - 256)", waterSpecularFactor, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("specularIntensity")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("specularIntensity", "Specular intensity", waterSpecularIntensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("waveHeight")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("waveHeight", "Wave height factor", waterWaveHeightFactor * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterMenuChoice");
			}
		}

		// Check if speed value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("speed", waterSpeed))
		{
			waterSpeed /= 100000.0f;
		}

		// Check if transparency value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("transparency", waterTransparency))
		{
			waterTransparency = std::clamp(waterTransparency / 10.0f, 0.0f, 1.0f);
		}

		// Check if color R value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorR", waterColor.r))
		{
			waterColor.r = std::clamp(waterColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Check if color G value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorG", waterColor.g))
		{
			waterColor.g = std::clamp(waterColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Check if color B value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorB", waterColor.b))
		{
			waterColor.b = std::clamp(waterColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Check if specular factor value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("specularFactor", waterSpecularFactor))
		{
			waterSpecularFactor = std::clamp(waterSpecularFactor, 0.0f, 256.0f);
		}

		// Check if specular intensity value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("specularIntensity", waterSpecularIntensity))
		{
			_waterSpecularIntensity /= 100.0f;
		}

		// Check if wave height value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("waveHeight", waterWaveHeightFactor))
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

		// Apply camera smoothing & rotation
		_cameraRotationSpeed *= 0.975f;
		_totalCameraRotation += _cameraRotationSpeed;

		// Calculate new camera position
		vec3 waterPosition = _fe3d.waterEntity_getPosition("@water");
		float waterSize = _fe3d.waterEntity_getSize("@water");
		float x = waterPosition.x + (waterSize / 2.0f) * sin(_totalCameraRotation);
		float y = waterPosition.y + (waterPosition.y + (waterSize / 16.0f));
		float z = waterPosition.z + (waterSize / 2.0f) * cos(_totalCameraRotation);

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
		_fe3d.camera_enableLookat(waterPosition);
	}
}