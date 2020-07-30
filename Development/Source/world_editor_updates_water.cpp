#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateWaterMenuMain()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		auto screen = _leftWindow->getScreen("waterEditorMenuMain");

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
				_leftWindow->setActiveScreen("waterEditorMenuChoice");
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuChoice");
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_fe3d.waterEntity_delete("@water");
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
		auto screen = _leftWindow->getScreen("waterEditorMenuChoice");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuMesh");
			}
			else if (screen->getButton("effects")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuEffects");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuMain");
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
	if (_leftWindow->getActiveScreen()->getID() == "waterEditorMenuMesh")
	{
		auto screen = _leftWindow->getScreen("waterEditorMenuMesh");
		vec3 waterPosition = _fe3d.waterEntity_getPosition("@water");
		float waterSize = _fe3d.waterEntity_getSize("@water");

		// Button hoverabilities
		screen->getButton("up")->setHoverable(_fe3d.waterEntity_isExisting("@water"));
		screen->getButton("down")->setHoverable(_fe3d.waterEntity_isExisting("@water"));

		// Pressed LMB
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("position")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("positionY", "Y", waterPosition.y, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionX", "X", waterPosition.x, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionZ", "Z", waterPosition.z, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("size", "Size", waterSize, vec2(0.0f), vec2(0.3f, 0.1f));
			}			
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuChoice");
			}
		}

		// Holding LMB
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("up")->isHovered())
			{
				_fe3d.waterEntity_setPosition("@water", waterPosition + vec3(0.0f, 0.1f, 0.0f));
			}
			else if (screen->getButton("down")->isHovered())
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
		if 
		(
			_gui->getGlobalScreen()->checkValueForm("positionX", waterPosition.x, { }) ||
			_gui->getGlobalScreen()->checkValueForm("positionY", waterPosition.y, { }) ||
			_gui->getGlobalScreen()->checkValueForm("positionZ", waterPosition.z, { })
		)
		{
			_fe3d.waterEntity_setPosition("@water", waterPosition);
		}
	}
}

void WorldEditor::_updateWaterMenuEffects()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterEditorMenuEffects")
	{
		// Variables
		auto screen = _leftWindow->getScreen("waterEditorMenuEffects");
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
		screen->getButton("isWaving")->setHoverable(displacementMapPath != "");
		screen->getButton("isRippling")->setHoverable(dudvMapPath != "");
		screen->getButton("isSpecular")->setHoverable(normalMapPath != "");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("uvRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV repeat", uvRepeat, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("dudvMap")->isHovered())
			{
				string filePath = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\DudvMaps\\", "PNG");

				// Check if not cancelled
				if (filePath != "")
				{
					_fe3d.misc_clearTextureCache(filePath);
					_fe3d.waterEntity_setDudvMap("@water", filePath);
				}
			}
			else if (screen->getButton("normalMap")->isHovered())
			{
				string filePath = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\NormalMaps\\", "PNG");

				// Check if not cancelled
				if (filePath != "")
				{
					_fe3d.misc_clearTextureCache(filePath);
					_fe3d.waterEntity_setNormalMap("@water", filePath);
				}
			}
			else if (screen->getButton("displaceMap")->isHovered())
			{
				string filePath = _fe3d.misc_getWinExplorerFilename("User\\Assets\\Textures\\DisplacementMaps\\", "PNG");

				// Check if not cancelled
				if (filePath != "")
				{
					_fe3d.misc_clearTextureCache(filePath);
					_fe3d.waterEntity_setDisplacementMap("@water", filePath);
				}
			}
			else if (screen->getButton("isReflective")->isHovered())
			{
				isReflective = !isReflective;
				_fe3d.waterEntity_setReflective("@water", isReflective);
			}
			else if (screen->getButton("isRefractive")->isHovered())
			{
				isRefractive = !isRefractive;
				_fe3d.waterEntity_setRefractive("@water", isRefractive);
			}
			else if (screen->getButton("isWaving")->isHovered())
			{
				isWaving = !isWaving;
				_fe3d.waterEntity_setWaving("@water", isWaving);
			}
			else if (screen->getButton("isRippling")->isHovered())	
			{
				isRippling = !isRippling;
				_fe3d.waterEntity_setRippling("@water", isRippling);
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				isSpecularLighted = !isSpecularLighted;
				_fe3d.waterEntity_setSpecularLighted("@water", isSpecularLighted);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuChoice");
			}
		}

		// Update GUI button contents
		auto reflectiveID = screen->getButton("isReflective")->getTextfield()->getEntityID();
		auto refractiveID = screen->getButton("isRefractive")->getTextfield()->getEntityID();
		auto wavingID = screen->getButton("isWaving")->getTextfield()->getEntityID();
		auto ripplingID = screen->getButton("isRippling")->getTextfield()->getEntityID();
		auto specularID = screen->getButton("isSpecular")->getTextfield()->getEntityID();
		_fe3d.textEntity_setTextContent(reflectiveID, isReflective ? "Reflective: ON" : "Reflective: OFF");
		_fe3d.textEntity_setTextContent(refractiveID, isRefractive ? "Refractive: ON" : "Refractive: OFF");
		_fe3d.textEntity_setTextContent(wavingID, isWaving ? "Waving: ON" : "Waving: OFF");
		_fe3d.textEntity_setTextContent(ripplingID, isRippling ? "Rippling: ON" : "Rippling: OFF");
		_fe3d.textEntity_setTextContent(specularID, isSpecularLighted ? "Specular: ON" : "Specular: OFF");

		// Update uvRepeat changes
		_gui->getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat);
		_fe3d.waterEntity_setUvRepeat("@water", uvRepeat);
	}
}

void WorldEditor::_updateWaterMenuOptions()
{
	if (_leftWindow->getActiveScreen()->getID() == "waterEditorMenuOptions")
	{
		auto screen = _leftWindow->getScreen("waterEditorMenuOptions");
		float speed = _fe3d.waterEntity_getSpeed("@water");
		float transparency = _fe3d.waterEntity_getTransparency("@water");
		vec3 color = _fe3d.waterEntity_getColor("@water");
		float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor("@water");
		float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity("@water");
		float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor("@water");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("speed")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("speed", "Water speed", speed * 100000.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("transparency")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("transparency", "Transparency(0 - 10)", transparency * 10.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", color.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", color.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", color.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("specularFactor", "Specular factor(0 - 256)", specularFactor, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("specularIntensity", "Specular intensity", specularIntensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("waveHeight")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("waveHeight", "Wave height factor", waveHeightFactor * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("waterEditorMenuChoice");
			}
		}

		// Check if speed value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("speed", speed))
		{
			speed /= 100000.0f;
			_fe3d.waterEntity_setSpeed("@water", speed);
		}

		// Check if transparency value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("transparency", transparency))
		{
			transparency = std::clamp(transparency / 10.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setTransparency("@water", transparency);
		}

		// Check if color R value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r = std::clamp(color.r / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor("@water", color);
		}

		// Check if color G value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g = std::clamp(color.g / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor("@water", color);
		}

		// Check if color B value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b = std::clamp(color.b / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor("@water", color);
		}

		// Check if specular factor value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("specularFactor", specularFactor))
		{
			specularFactor = std::clamp(specularFactor, 0.0f, 256.0f);
			_fe3d.waterEntity_setSpecularLightingFactor("@water", specularFactor);
		}

		// Check if specular intensity value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.waterEntity_setSpecularLightingIntensity("@water", specularIntensity);
		}

		// Check if wave height value confirmed
		if (_gui->getGlobalScreen()->checkValueForm("waveHeight", waveHeightFactor))
		{
			waveHeightFactor /= 100.0f;
			_fe3d.waterEntity_setWaveHeightFactor("@water", waveHeightFactor);
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