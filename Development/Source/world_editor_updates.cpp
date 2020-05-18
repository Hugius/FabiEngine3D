#include "world_editor.hpp"

void WorldEditor::update(float delta)
{
	_updateWorldManagement();
	_upateSkyManagement();
	_upateTerrainManagement();
	_upateWaterManagement();
}

void WorldEditor::_updateWorldManagement()
{
	auto screen = _window->getScreen("worldManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("sky")->isHovered())
		{
			_window->setActiveScreen("skyManagement");
		}
		else if (screen->getButton("terrain")->isHovered())
		{
			_window->setActiveScreen("terrainManagement");
		}
		else if (screen->getButton("water")->isHovered())
		{

		}
		else if (screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("main");
		}
	}
}

void WorldEditor::_upateSkyManagement()
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
		else if(screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("worldManagement");
		}
	}

	// Update sub-menus
	_updateSkyMesh();
	_updateSkyOptions();
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
				_skyTexturePaths[0] = cubemapPath + _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
			}
			else if (screen->getScrollingList("textureList")->getButton("leftTexture")->isHovered())
			{
				_skyTexturePaths[1] = cubemapPath + _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
			}
			else if (screen->getScrollingList("textureList")->getButton("topTexture")->isHovered())
			{
				_skyTexturePaths[2] = cubemapPath + _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
			}
			else if (screen->getScrollingList("textureList")->getButton("bottomTexture")->isHovered())
			{
				_skyTexturePaths[3] = cubemapPath + _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
			}
			else if (screen->getScrollingList("textureList")->getButton("backTexture")->isHovered())
			{
				_skyTexturePaths[4] = cubemapPath + _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
			}
			else if (screen->getScrollingList("textureList")->getButton("frontTexture")->isHovered())
			{
				_skyTexturePaths[5] = cubemapPath + _fe3d.misc_getWinExplorerFilename(cubemapPath, "PNG");
			}
			else if (screen->getButton("load")->isHovered())
			{
				if (_fe3d.skyEntity_isExisting("sky"))
				{
					_fe3d.skyEntity_delete("sky");
				}

				// Add new skybox
				_fe3d.skyEntity_add("sky", 0.0f, _skyTexturePaths);
				_fe3d.skyEntity_select("sky");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
			}
		}

		// Update load button hoverability
		bool texturesLoaded = (std::find(_skyTexturePaths.begin(), _skyTexturePaths.end(), cubemapPath) == _skyTexturePaths.end()) &&
							  (std::find(_skyTexturePaths.begin(), _skyTexturePaths.end(), "") == _skyTexturePaths.end());
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

void WorldEditor::_upateTerrainManagement()
{
	auto screen = _window->getScreen("terrainManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("mesh")->isHovered())
		{
			_window->setActiveScreen("terrainMesh");
		}
		else if (screen->getButton("blendmap")->isHovered())
		{
			_window->setActiveScreen("terrainBlendmap");
		}
		else if (screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("worldManagement");
		}
	}

	// Update sub-menus
	_updateTerrainCamera();
	_updateTerrainMesh();
	_updateTerrainBlendmap();
}

void WorldEditor::_updateTerrainCamera()
{
	// Get scroll wheel input
	float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) * 0.001f;
	_cameraRotationSpeed += rotationAcceleration;
	_cameraRotationSpeed *= 0.995f;
	_totalCameraRotation += _cameraRotationSpeed;

	// Calculate new camera position
	float x = ((_cameraDistance / 2.0f) * sin(_totalCameraRotation)) + (_cameraDistance / 2.0f);
	float y = _cameraHeight;
	float z = ((_cameraDistance / 2.0f) * cos(_totalCameraRotation)) + (_cameraDistance / 2.0f);

	// Update camera position
	_fe3d.camera_setPosition(vec3(x, y, z));
}

void WorldEditor::_updateTerrainMesh()
{
	if (_window->getActiveScreen()->getID() == "terrainMesh")
	{
		auto screen = _window->getScreen("terrainMesh");
		string heightmapPath = "User\\Assets\\Textures\\HeightMaps\\";
		string diffusemapPath = "User\\Assets\\Textures\\DiffuseMaps\\";
		
		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("terrainList")->getButton("heightmap")->isHovered())
			{
				_terrainHeightmapPath = heightmapPath + _fe3d.misc_getWinExplorerFilename(heightmapPath, "BMP");
			}
			else if (screen->getScrollingList("terrainList")->getButton("diffusemap")->isHovered())
			{
				_terrainDiffusemapPath = diffusemapPath + _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
			}
			else if (screen->getScrollingList("terrainList")->getButton("size")->isHovered())
			{
				_activeWritefield = "size";
				_gui->getGlobalScreen()->addWriteField("size", vec2(0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
				_gui->getGlobalScreen()->getWriteField("size")->setTextContent(std::to_string(int(_terrainSize)));
				_gui->getGlobalScreen()->getWriteField("size")->setActive(true);
				_gui->setFocus(true);
			}
			else if (screen->getScrollingList("terrainList")->getButton("maxHeight")->isHovered())
			{
				_activeWritefield = "maxHeight";
				_gui->getGlobalScreen()->addWriteField("maxHeight", vec2(0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
				_gui->getGlobalScreen()->getWriteField("maxHeight")->setTextContent(std::to_string(int(_maxTerrainHeight)));
				_gui->getGlobalScreen()->getWriteField("maxHeight")->setActive(true);
				_gui->setFocus(true);
			}
			else if (screen->getScrollingList("terrainList")->getButton("uvRepeat")->isHovered())
			{
				_activeWritefield = "uvRepeat";
				_gui->getGlobalScreen()->addWriteField("uvRepeat", vec2(0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
				_gui->getGlobalScreen()->getWriteField("uvRepeat")->setTextContent(std::to_string(int(_terrainUvRepeat)));
				_gui->getGlobalScreen()->getWriteField("uvRepeat")->setActive(true);
				_gui->setFocus(true);
			}
			else if (screen->getButton("load")->isHovered())
			{
				// Remove existing terrain
				if (_fe3d.terrainEntity_isExisting("terrain"))
				{
					_fe3d.terrainEntity_delete("terrain");
				}

				// Add new terrain
				_fe3d.terrainEntity_add("terrain", _terrainHeightmapPath, _terrainDiffusemapPath, vec3(0.0f), _terrainSize, _maxTerrainHeight, _terrainUvRepeat);
				_fe3d.terrainEntity_select("terrain");

				// Get possibly corrected size
				_terrainSize = _fe3d.terrainEntity_getSize("terrain");
				_fe3d.camera_enableLookat(vec3(_terrainSize / 2.0f, 0.0f, _terrainSize / 2.0f));
				_cameraDistance = _terrainSize;
				_cameraHeight = _maxTerrainHeight * 1.5f;
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
			}
		}

		// Filling in writefield
		if (_activeWritefield != "")
		{
			if (_gui->getGlobalScreen()->getWriteField(_activeWritefield)->confirmedInput() || _gui->getGlobalScreen()->getWriteField(_activeWritefield)->cancelledInput())
			{
				if (_gui->getGlobalScreen()->getWriteField(_activeWritefield)->confirmedInput())
				{
					if (_activeWritefield == "size")
					{
						_terrainSize = float(std::stoi(_gui->getGlobalScreen()->getWriteField(_activeWritefield)->getTextContent()));
					}
					else if (_activeWritefield == "maxHeight")
					{
						_maxTerrainHeight = float(std::stoi(_gui->getGlobalScreen()->getWriteField(_activeWritefield)->getTextContent()));
					}
					else if (_activeWritefield == "uvRepeat")
					{
						_terrainUvRepeat = float(std::stoi(_gui->getGlobalScreen()->getWriteField(_activeWritefield)->getTextContent()));
					}
				}

				// Cleanup
				_gui->getGlobalScreen()->deleteWriteField(_activeWritefield);
				_gui->setFocus(false);
				_activeWritefield = "";
			}
		}

		// Load button hoverability
		bool hoverable = _terrainHeightmapPath != "" && _terrainDiffusemapPath != "" && _terrainSize != 0.0f && _maxTerrainHeight != 0.0f && _terrainUvRepeat != 0.0f;
		screen->getButton("load")->setHoverable(hoverable);
	}
}

void WorldEditor::_updateTerrainBlendmap()
{
	if (_window->getActiveScreen()->getID() == "terrainBlendmap")
	{
		auto screen = _window->getScreen("skyOptions");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("blendmapList")->getButton("rightTexture")->isHovered())
			{

			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
			}
		}
	}
}

void WorldEditor::_upateWaterManagement()
{

}