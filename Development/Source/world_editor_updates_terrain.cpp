#include "world_editor.hpp"

void WorldEditor::_updateTerrainMenu()
{
	if (_currentWorldPart == WorldPart::TERRAIN)
	{
		auto screen = _window->getScreen("terrainMenu");

		// Update terrain management if possible
		_updateTerrainManagement();

		// Update buttons hoverability
		screen->getButton("create")->setHoverable(!_fe3d.terrainEntity_isExisting("@terrain"));
		screen->getButton("edit")->setHoverable(_fe3d.terrainEntity_isExisting("@terrain"));
		screen->getButton("remove")->setHoverable(_fe3d.terrainEntity_isExisting("@terrain"));

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered() || screen->getButton("edit")->isHovered())
			{
				_window->setActiveScreen("terrainManagement");

				// Show sky
				if (_fe3d.skyEntity_isExisting("@sky"))
				{
					_fe3d.skyEntity_show("@sky");
				}

				// Show terrain
				if (_fe3d.terrainEntity_isExisting("@terrain"))
				{
					_fe3d.terrainEntity_show("@terrain");
				}

				// Hide water
				if (_fe3d.waterEntity_isExisting("@water"))
				{
					_fe3d.waterEntity_hide("@water");
				}
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_unloadTerrainData();
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("worldManagement");
				_currentWorldPart = WorldPart::NONE;
			}
		}
	}
}

void WorldEditor::_updateTerrainManagement()
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
			_window->setActiveScreen("terrainMenu");

			// Hide sky
			if (_fe3d.skyEntity_isExisting("@sky"))
			{
				_fe3d.skyEntity_hide("@sky");
			}

			// Hide terrain
			if (_fe3d.terrainEntity_isExisting("@terrain"))
			{
				_fe3d.terrainEntity_hide("@terrain");
			}
		}
	}

	// Options screen hoverability
	screen->getButton("blendmap")->setHoverable(_fe3d.terrainEntity_isExisting("@terrain"));

	// Update sub-menus
	_updateTerrainCamera();
	_updateTerrainMesh();
	_updateTerrainBlendmap();
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
			if (screen->getScrollingList("buttonList")->getButton("heightmap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(heightmapPath, "BMP");
				_terrainHeightmapPath = (fileName == "") ? _terrainHeightmapPath : (heightmapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("diffusemap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainDiffusemapPath = (fileName == "") ? _terrainDiffusemapPath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("size")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("size", "Size", _terrainSize, vec2(0.0f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("maxHeight")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("maxHeight", "Max height", _maxTerrainHeight, vec2(0.0f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("uvRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV repeat", _terrainUvRepeat, vec2(0.0f));
			}
			else if (screen->getButton("load")->isHovered())
			{
				_loadTerrainEntity();
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("terrainManagement");
			}
		}

		// Check if value confirmed
		_gui->getGlobalScreen()->checkValueForm("size", _terrainSize);
		_gui->getGlobalScreen()->checkValueForm("maxHeight", _maxTerrainHeight);
		_gui->getGlobalScreen()->checkValueForm("uvRepeat", _terrainUvRepeat);

		// Filling statuses
		bool heightmap = _terrainHeightmapPath != "";
		bool diffusemap = _terrainDiffusemapPath != "";
		bool size = _terrainSize != 0.0f;
		bool maxHeight = _maxTerrainHeight != 0.0f;
		bool uvRepeat = _terrainUvRepeat != 0.0f;

		// Button hoverability
		screen->getScrollingList("buttonList")->getButton("diffusemap")->setHoverable(heightmap);
		screen->getScrollingList("buttonList")->getButton("size")->setHoverable(heightmap && diffusemap);
		screen->getScrollingList("buttonList")->getButton("maxHeight")->setHoverable(heightmap && diffusemap && size);
		screen->getScrollingList("buttonList")->getButton("uvRepeat")->setHoverable(heightmap && diffusemap && size && maxHeight);
		screen->getButton("load")->setHoverable(heightmap && diffusemap && size && maxHeight && uvRepeat);
	}
}

void WorldEditor::_updateTerrainBlendmap()
{
	if (_window->getActiveScreen()->getID() == "terrainBlendmap")
	{
		auto screen = _window->getScreen("terrainBlendmap");
		string blendmapPath = "User\\Assets\\Textures\\BlendMaps\\";
		string diffusemapPath = "User\\Assets\\Textures\\DiffuseMaps\\";

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getScrollingList("buttonList")->getButton("blendmap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(blendmapPath, "PNG");
				_terrainBlendmapPath = (fileName == "") ? _terrainBlendmapPath : (blendmapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("red")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainRedPath = (fileName == "") ? _terrainRedPath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("green")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainGreenPath = (fileName == "") ? _terrainGreenPath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("blue")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainBluePath = (fileName == "") ? _terrainBluePath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("buttonList")->getButton("redRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("redRepeat", "Red repeat", _terrainRedUvRepeat, vec2(0.0f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("greenRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("greenRepeat", "Green repeat", _terrainGreenUvRepeat, vec2(0.0f));
			}
			else if (screen->getScrollingList("buttonList")->getButton("blueRepeat")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("blueRepeat", "Blue repeat", _terrainBlueUvRepeat, vec2(0.0f));
			}
			else if (screen->getButton("load")->isHovered())
			{
				_isTerrainBlendmapped = true;
				_fe3d.terrainEntity_addBlending("@terrain", _terrainBlendmapPath, _terrainRedPath, _terrainGreenPath, _terrainBluePath, _terrainRedUvRepeat, _terrainGreenUvRepeat, _terrainBlueUvRepeat);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("terrainManagement");
			}
		}

		// Check if value confirmed
		_gui->getGlobalScreen()->checkValueForm("redRepeat", _terrainRedUvRepeat);
		_gui->getGlobalScreen()->checkValueForm("greenRepeat", _terrainGreenUvRepeat);
		_gui->getGlobalScreen()->checkValueForm("blueRepeat", _terrainBlueUvRepeat);

		// Filling statuses
		bool loadedBlendmap = _terrainBlendmapPath != "";
		bool loadedRedTex = _terrainRedPath != "";
		bool loadedGreenTex = _terrainGreenPath != "";
		bool loadedBlueTex = _terrainBluePath != "";
		bool loadedRedUV = _terrainRedUvRepeat != 0.0f;
		bool loadedGreenUV = _terrainGreenUvRepeat != 0.0f;
		bool loadedBlueUV = _terrainBlueUvRepeat != 0.0f;

		// Button hoverability
		screen->getScrollingList("buttonList")->getButton("red")->setHoverable(loadedBlendmap);
		screen->getScrollingList("buttonList")->getButton("green")->setHoverable(loadedBlendmap);
		screen->getScrollingList("buttonList")->getButton("blue")->setHoverable(loadedBlendmap);
		screen->getScrollingList("buttonList")->getButton("redRepeat")->setHoverable(loadedBlendmap && loadedRedTex);
		screen->getScrollingList("buttonList")->getButton("greenRepeat")->setHoverable(loadedBlendmap && loadedGreenTex);
		screen->getScrollingList("buttonList")->getButton("blueRepeat")->setHoverable(loadedBlendmap && loadedBlueTex);
		screen->getButton("load")->setHoverable(loadedBlendmap && loadedRedTex && loadedGreenTex && loadedBlueTex && loadedRedUV && loadedGreenUV && loadedBlueUV);
	}
}

void WorldEditor::_updateTerrainCamera()
{
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		// Get scroll wheel input
		float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) * 0.001f;
		_cameraRotationSpeed += rotationAcceleration;
		_cameraRotationSpeed *= 0.995f;
		_totalCameraRotation += _cameraRotationSpeed;

		// Calculate new camera position
		float x = _terrainCameraDistance * sin(_totalCameraRotation);
		float y = _terrainCameraHeight;
		float z = _terrainCameraDistance * cos(_totalCameraRotation);

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
		_fe3d.camera_enableLookat(vec3(0.0f));
	}
}