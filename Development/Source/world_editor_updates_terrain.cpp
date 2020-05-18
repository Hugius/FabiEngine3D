#include "world_editor.hpp"

void WorldEditor::_upateTerrainManagement()
{
	if (_currentWorldPart == WorldPart::TERRAIN)
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
				_currentWorldPart = WorldPart::NONE;
			}
		}

		// Options screen hoverability
		screen->getButton("blendmap")->setHoverable(_fe3d.terrainEntity_isExisting("@terrain"));

		// Update sub-menus
		_updateTerrainCamera();
		_updateTerrainMesh();
		_updateTerrainBlendmap();
	}
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
				string fileName = _fe3d.misc_getWinExplorerFilename(heightmapPath, "BMP");
				_terrainHeightmapPath = (fileName == "") ? _terrainHeightmapPath : (heightmapPath + fileName);
			}
			else if (screen->getScrollingList("terrainList")->getButton("diffusemap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainDiffusemapPath = (fileName == "") ? _terrainDiffusemapPath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("terrainList")->getButton("size")->isHovered())
			{
				_addValueForm("size", _terrainSize);
			}
			else if (screen->getScrollingList("terrainList")->getButton("maxHeight")->isHovered())
			{
				_addValueForm("maxHeight", _maxTerrainHeight);
			}
			else if (screen->getScrollingList("terrainList")->getButton("uvRepeat")->isHovered())
			{
				_addValueForm("uvRepeat", _terrainUvRepeat);
			}
			else if (screen->getButton("load")->isHovered())
			{
				// Remove existing terrain
				if (_fe3d.terrainEntity_isExisting("@terrain"))
				{
					_fe3d.terrainEntity_delete("@terrain");
				}

				// Add new terrain
				_fe3d.terrainEntity_add("@terrain", _terrainHeightmapPath, _terrainDiffusemapPath, vec3(0.0f), _terrainSize, _maxTerrainHeight, _terrainUvRepeat);
				_fe3d.terrainEntity_select("@terrain");

				// Get possibly corrected size
				_terrainSize = _fe3d.terrainEntity_getSize("@terrain");
				_fe3d.camera_enableLookat(vec3(_terrainSize / 2.0f, 0.0f, _terrainSize / 2.0f));
				_cameraDistance = _terrainSize;
				_cameraHeight = _maxTerrainHeight * 1.5f;
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("terrainManagement");
			}
		}

		// Check if value confirmed
		_checkValueForm("size", _terrainSize);
		_checkValueForm("maxHeight", _maxTerrainHeight);
		_checkValueForm("uvRepeat", _terrainUvRepeat);

		// Filling statuses
		bool heightmap = _terrainHeightmapPath != "";
		bool diffusemap = _terrainDiffusemapPath != "";
		bool size = _terrainSize != 0.0f;
		bool maxHeight = _maxTerrainHeight != 0.0f;
		bool uvRepeat = _terrainUvRepeat != 0.0f;

		// Button hoverability
		screen->getScrollingList("terrainList")->getButton("diffusemap")->setHoverable(heightmap);
		screen->getScrollingList("terrainList")->getButton("size")->setHoverable(heightmap && diffusemap);
		screen->getScrollingList("terrainList")->getButton("maxHeight")->setHoverable(heightmap && diffusemap && size);
		screen->getScrollingList("terrainList")->getButton("uvRepeat")->setHoverable(heightmap && diffusemap && size && maxHeight);
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
			if (screen->getScrollingList("blendmapList")->getButton("blendmap")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(blendmapPath, "PNG");
				_terrainBlendmapPath = (fileName == "") ? _terrainBlendmapPath : (blendmapPath + fileName);
			}
			else if (screen->getScrollingList("blendmapList")->getButton("red")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainRedPath = (fileName == "") ? _terrainRedPath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("blendmapList")->getButton("green")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainGreenPath = (fileName == "") ? _terrainGreenPath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("blendmapList")->getButton("blue")->isHovered())
			{
				string fileName = _fe3d.misc_getWinExplorerFilename(diffusemapPath, "PNG");
				_terrainBluePath = (fileName == "") ? _terrainBluePath : (diffusemapPath + fileName);
			}
			else if (screen->getScrollingList("blendmapList")->getButton("redRepeat")->isHovered())
			{
				_addValueForm("redRepeat", _redUvRepeat);
			}
			else if (screen->getScrollingList("blendmapList")->getButton("greenRepeat")->isHovered())
			{
				_addValueForm("greenRepeat", _greenUvRepeat);
			}
			else if (screen->getScrollingList("blendmapList")->getButton("blueRepeat")->isHovered())
			{
				_addValueForm("blueRepeat", _blueUvRepeat);
			}
			else if (screen->getButton("load")->isHovered())
			{
				_fe3d.terrainEntity_addBlending("@terrain", _terrainBlendmapPath, _terrainRedPath, _terrainGreenPath, _terrainBluePath, _redUvRepeat, _greenUvRepeat, _blueUvRepeat);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("terrainManagement");
			}
		}

		// Check if value confirmed
		_checkValueForm("redRepeat", _redUvRepeat);
		_checkValueForm("greenRepeat", _greenUvRepeat);
		_checkValueForm("blueRepeat", _blueUvRepeat);

		// Filling statuses
		bool loadedBlendmap = _terrainBlendmapPath != "";
		bool loadedRedTex = _terrainRedPath != "";
		bool loadedGreenTex = _terrainGreenPath != "";
		bool loadedBlueTex = _terrainBluePath != "";
		bool loadedRedUV = _redUvRepeat != 0.0f;
		bool loadedGreenUV = _greenUvRepeat != 0.0f;
		bool loadedBlueUV = _blueUvRepeat != 0.0f;

		// Button hoverability
		screen->getScrollingList("blendmapList")->getButton("red")->setHoverable(loadedBlendmap);
		screen->getScrollingList("blendmapList")->getButton("green")->setHoverable(loadedBlendmap);
		screen->getScrollingList("blendmapList")->getButton("blue")->setHoverable(loadedBlendmap);
		screen->getScrollingList("blendmapList")->getButton("redRepeat")->setHoverable(loadedBlendmap && loadedRedTex);
		screen->getScrollingList("blendmapList")->getButton("greenRepeat")->setHoverable(loadedBlendmap && loadedGreenTex);
		screen->getScrollingList("blendmapList")->getButton("blueRepeat")->setHoverable(loadedBlendmap && loadedBlueTex);
		screen->getButton("load")->setHoverable(loadedBlendmap && loadedRedTex && loadedGreenTex && loadedBlueTex && loadedRedUV && loadedGreenUV && loadedBlueUV);
	}
}