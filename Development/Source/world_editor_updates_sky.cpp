#include "world_editor.hpp"

void WorldEditor::_upateSkyManagement()
{
	if (_currentWorldPart == WorldPart::SKY)
	{
		auto screen = _window->getScreen("skyManagement");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_window->setActiveScreen("skyMesh");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_window->setActiveScreen("skyOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("worldManagement");
				_currentWorldPart = WorldPart::NONE;
			}
		}

		// Options screen hoverability
		screen->getButton("options")->setHoverable(_fe3d.skyEntity_isExisting("@sky"));

		// Update sub-menus
		_updateSkyCamera();
		_updateSkyMesh();
		_updateSkyOptions();
		
		// Dynamic updates
		if (_fe3d.skyEntity_isExisting("@sky"))
		{
			_fe3d.skyEntity_setRotationSpeed("@sky", _skyRotationSpeed);
		}
	}
}

void WorldEditor::_updateSkyMesh()
{
	if (_window->getActiveScreen()->getID() == "skyMesh")
	{
		auto screen = _window->getScreen("skyMesh");
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
			else if (screen->getScrollingList("buttonList")->getButton("backTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[4] = (fileName == "") ? _skyTexturePaths[4] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("frontTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[5] = (fileName == "") ? _skyTexturePaths[5] : (cubemapPath + fileName);
			}
			else if (screen->getButton("load")->isHovered())
			{
				_loadSkybox();
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
			}
		}

		// Update load button hoverability
		bool texturesLoaded = (std::find(_skyTexturePaths.begin(), _skyTexturePaths.end(), "") == _skyTexturePaths.end());
		screen->getButton("load")->setHoverable(texturesLoaded);
	}
}

void WorldEditor::_updateSkyOptions()
{
	if (_window->getActiveScreen()->getID() == "skyOptions")
	{
		auto screen = _window->getScreen("skyOptions");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("rotationSpeed")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("rotationSpeed", "Rotation speed", _skyRotationSpeed * 100.0f, vec2(0.0f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
			}
		}

		// Speed value conversion
		if (_gui->getGlobalScreen()->checkValueForm("rotationSpeed", _skyRotationSpeed))
		{
			_skyRotationSpeed /= 100.0f;
		}
	}
}

void WorldEditor::_loadSkybox()
{
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Add new skybox
	_fe3d.skyEntity_add("@sky", _skyTexturePaths);
	_fe3d.skyEntity_select("@sky");
}

void WorldEditor::_updateSkyCamera()
{
	if (_fe3d.misc_isMouseInsideViewport() && _fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
	{
		// Move mouse to middle when pressed first time
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_RIGHT))
		{
			_fe3d.misc_centerMousePos();
		}

		// Enable FPS camera
		_fe3d.gfx_enableMotionBlur();
		_fe3d.camera_enableFirstPersonView(5.0f);
		_fe3d.camera_disableLookat();
		_fe3d.misc_hideCursor();
	}
	else
	{
		_fe3d.gfx_disableMotionBlur();
		_fe3d.camera_disableFirstPersonView();
		_fe3d.misc_showCursor();
	}
}