#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSkyMenu()
{
	if (_currentWorldPart == WorldPart::SKY)
	{
		auto screen = _leftWindow->getScreen("skyMenu");

		// If sky existing, show sky
		if (_fe3d.skyEntity_isExisting("@sky"))
		{
			_fe3d.skyEntity_show("@sky");
			_fe3d.skyEntity_select("@sky");
		}
		else // Otherwise just show default sky
		{
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

		// Update sky functionality
		_updateSkyManagement();
		_updateSkyCamera();
		_updateSkyMesh();
		_updateSkyOptions();

		// Update buttons hoverability
		screen->getButton("create")->setHoverable(!_fe3d.skyEntity_isExisting("@sky"));
		screen->getButton("edit")->setHoverable(_fe3d.skyEntity_isExisting("@sky"));
		screen->getButton("remove")->setHoverable(_fe3d.skyEntity_isExisting("@sky"));

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered() || screen->getButton("edit")->isHovered())
			{
				_leftWindow->setActiveScreen("skyManagement");
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_unloadSkyData();
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("worldEditorMenu");
				_currentWorldPart = WorldPart::NONE;
			}
		}
	}
}

void WorldEditor::_updateSkyManagement()
{
	if (_leftWindow->getActiveScreen()->getID() == "skyManagement")
	{
		auto screen = _leftWindow->getScreen("skyManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_leftWindow->setActiveScreen("skyMesh");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_leftWindow->setActiveScreen("skyOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("skyMenu");
			}
		}

		// Options screen hoverability
		screen->getButton("options")->setHoverable(_fe3d.skyEntity_isExisting("@sky"));
	}
}

void WorldEditor::_updateSkyMesh()
{
	if (_leftWindow->getActiveScreen()->getID() == "skyMesh")
	{
		auto screen = _leftWindow->getScreen("skyMesh");
		string cubemapPath = "User\\Assets\\Textures\\CubeMaps\\";

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("rightTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[0] = (fileName == "") ? _skyTexturePaths[0] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("leftTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[1] = (fileName == "") ? _skyTexturePaths[1] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("topTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[2] = (fileName == "") ? _skyTexturePaths[2] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("bottomTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[3] = (fileName == "") ? _skyTexturePaths[3] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("frontTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[4] = (fileName == "") ? _skyTexturePaths[4] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("backTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[5] = (fileName == "") ? _skyTexturePaths[5] : (cubemapPath + fileName);
			}
			else if (screen->getButton("load")->isHovered())
			{
				// Clear texture caches
				_fe3d.misc_clearCubeMapCache(_skyTexturePaths);

				// Load entity
				_loadSkyEntity();
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("skyManagement");
			}
		}

		// Update load button hoverability
		bool texturesLoaded = (std::find(_skyTexturePaths.begin(), _skyTexturePaths.end(), "") == _skyTexturePaths.end());
		screen->getButton("load")->setHoverable(texturesLoaded);
	}
}

void WorldEditor::_updateSkyOptions()
{	
	if (_leftWindow->getActiveScreen()->getID() == "skyOptions")
	{
		// Variables
		auto screen = _leftWindow->getScreen("skyOptions");
		float skyRotationSpeed = _fe3d.skyEntity_getRotationSpeed("@sky");
		float skyLightness = _fe3d.skyEntity_getLightness("@sky");
		vec3 skyColor = _fe3d.skyEntity_getColor("@sky");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("rotationSpeed")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("rotationSpeed", "Rotation speed", skyRotationSpeed * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("lightness", "lightness", skyLightness * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", skyColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", skyColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", skyColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("skyManagement");
			}
		}

		// Speed value conversion
		if (_gui->getGlobalScreen()->checkValueForm("rotationSpeed", skyRotationSpeed))
		{
			skyRotationSpeed /= 100.0f;
		}

		// Lightness value conversion
		if (_gui->getGlobalScreen()->checkValueForm("lightness", skyLightness))
		{
			skyLightness = std::clamp(skyLightness / 100.0f, 0.0f, 1.0f);
		}

		// Color R values conversion
		if (_gui->getGlobalScreen()->checkValueForm("colorR", skyColor.r))
		{
			skyColor.r = std::clamp(skyColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Color G values conversion
		if (_gui->getGlobalScreen()->checkValueForm("colorG", skyColor.g))
		{
			skyColor.g = std::clamp(skyColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Color B values conversion
		if (_gui->getGlobalScreen()->checkValueForm("colorB", skyColor.b))
		{
			skyColor.b = std::clamp(skyColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Dynamically update sky options
		_fe3d.skyEntity_setRotationSpeed("@sky", skyRotationSpeed);
		_fe3d.skyEntity_setLightness("@sky", skyLightness);
		_fe3d.skyEntity_setColor("@sky", skyColor);
	}
}

void WorldEditor::_updateSkyCamera()
{
	if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
	{
		if (_fe3d.misc_isMouseInsideViewport())
		{
			_fe3d.gfx_enableMotionBlur();
			_fe3d.camera_enableFirstPersonView(10.0f);
			_fe3d.camera_disableLookat();
			_fe3d.misc_hideCursor();
		}
	}
	else
	{
		_fe3d.gfx_disableMotionBlur();
		_fe3d.camera_disableFirstPersonView();
		_fe3d.misc_showCursor();
	}
}