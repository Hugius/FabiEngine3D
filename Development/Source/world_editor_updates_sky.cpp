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
		_updateFPSCamera();
		_updateSkyMesh();
		_updateSkyOptions();
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
			if (screen->getScrollingList("textureList")->getButton("rightTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[0] = (fileName == "") ? _skyTexturePaths[0] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("textureList")->getButton("leftTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[1] = (fileName == "") ? _skyTexturePaths[1] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("textureList")->getButton("topTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[2] = (fileName == "") ? _skyTexturePaths[2] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("textureList")->getButton("bottomTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[3] = (fileName == "") ? _skyTexturePaths[3] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("textureList")->getButton("backTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[4] = (fileName == "") ? _skyTexturePaths[4] : (cubemapPath + fileName);
			}
			else if (screen->getScrollingList("textureList")->getButton("frontTexture")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
				_skyTexturePaths[5] = (fileName == "") ? _skyTexturePaths[5] : (cubemapPath + fileName);
			}
			else if (screen->getButton("load")->isHovered())
			{
				if (_fe3d.skyEntity_isExisting("@sky"))
				{
					_fe3d.skyEntity_delete("@sky");
				}

				// Add new skybox
				_fe3d.skyEntity_add("@sky", 0.0f, _skyTexturePaths);
				_fe3d.skyEntity_select("@sky");
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
			if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
			}
		}
	}
}