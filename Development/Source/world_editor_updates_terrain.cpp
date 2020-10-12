#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateTerrainMenuMain()
{
	if (_currentWorldPart == WorldPart::TERRAIN)
	{
		auto screen = _leftWindow->getScreen("terrainEditorMenuMain");

		// If terrain existing, show terrain
		if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
		{
			_fe3d.terrainEntity_show(_currentTerrainID);
		}
		else // Otherwise just show default sky
		{
			_fe3d.skyEntity_select("@@defaultSky");
		}

		// Show sky
		if (_fe3d.skyEntity_isExisting(_currentSkyID))
		{
			_fe3d.skyEntity_select(_currentSkyID);
			_fe3d.skyEntity_show(_currentSkyID);
		}

		// Hide water
		if (_fe3d.waterEntity_isExisting(_currentWaterID))
		{
			_fe3d.waterEntity_hide(_currentWaterID);
		}

		// Update terrain management if possible
		_updateTerrainMenuChoice();

		// Update buttons hoverability
		screen->getButton("create")->setHoverable(!_fe3d.terrainEntity_isExisting(_currentTerrainID));
		screen->getButton("edit")->setHoverable(_fe3d.terrainEntity_isExisting(_currentTerrainID));
		screen->getButton("remove")->setHoverable(_fe3d.terrainEntity_isExisting(_currentTerrainID));

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered() || screen->getButton("edit")->isHovered())
			{
				_leftWindow->setActiveScreen("terrainEditorMenuChoice");
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_fe3d.terrainEntity_delete(_currentTerrainID);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("worldEditorMenu");
				_currentWorldPart = WorldPart::NONE;
			}
		}
	}
}

void WorldEditor::_updateTerrainMenuChoice()
{
	auto screen = _leftWindow->getScreen("terrainEditorMenuChoice");

	// BlendMap screen hoverability
	screen->getButton("blendMap")->setHoverable(_fe3d.terrainEntity_isExisting(_currentTerrainID));

	// GUI management
	if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("mesh")->isHovered())
		{
			_leftWindow->setActiveScreen("terrainEditorMenuMesh");
		}
		else if (screen->getButton("blendMap")->isHovered())
		{
			_leftWindow->setActiveScreen("terrainEditorMenuBlendMap");
		}
		else if (screen->getButton("back")->isHovered())
		{
			_leftWindow->setActiveScreen("terrainEditorMenuMain");
		}
	}

	// Update sub-menus
	_updateTerrainCamera();
	_updateTerrainMenuMesh();
	_updateTerrainMenuBlendMap();
}

void WorldEditor::_updateTerrainMenuMesh()
{
	if (_leftWindow->getActiveScreen()->getID() == "terrainEditorMenuMesh")
	{
		// Variables
		auto screen = _leftWindow->getScreen("terrainEditorMenuMesh");

		// Buttons hoverability
		bool existing = _fe3d.terrainEntity_isExisting(_currentTerrainID);
		screen->getButton("diffuseMap")->setHoverable(existing);
		screen->getButton("maxHeight")->setHoverable(existing);
		screen->getButton("uvRepeat")->setHoverable(existing);
		screen->getButton("specularIntensity")->setHoverable(existing);
		screen->getButton("lightness")->setHoverable(existing);

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("heightMap")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\height_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "BMP");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearHeightMapCache(newFilePath);
						_loadTerrainEntity(newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("diffuseMap")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.terrainEntity_setDiffuseMap(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("maxHeight")->isHovered())
			{
				float maxHeight = _fe3d.terrainEntity_getMaxHeight(_currentTerrainID);
				_gui->getGlobalScreen()->addValueForm("maxHeight", "Max height", maxHeight, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("uvRepeat")->isHovered())
			{
				float uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);
				_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV repeat", uvRepeat, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				_fe3d.terrainEntity_setSpecularLighted(_currentTerrainID, !_fe3d.terrainEntity_isSpecularLighted(_currentTerrainID));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				float intensity = _fe3d.terrainEntity_getSpecularLightingIntensity(_currentTerrainID);
				_gui->getGlobalScreen()->addValueForm("intensity", "Intensity (%)", intensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);
				_gui->getGlobalScreen()->addValueForm("lightness", "Lightness (%)", lightness * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("terrainEditorMenuChoice");
			}
		}

		// If terrain entity exists
		if (existing)
		{
			// Check if maxHeight confirmed
			float maxHeight = _fe3d.terrainEntity_getMaxHeight(_currentTerrainID);
			if (_gui->getGlobalScreen()->checkValueForm("maxHeight", maxHeight))
			{
				_fe3d.terrainEntity_setMaxHeight(_currentTerrainID, maxHeight);
			}

			// Check if uvRepeat confirmed
			float uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);
			if (_gui->getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat))
			{
				_fe3d.terrainEntity_setUvRepeat(_currentTerrainID, uvRepeat);
			
			}

			// Update specular button content
			auto specularID = screen->getButton("isSpecular")->getTextfield()->getEntityID();
			auto isSpecular = _fe3d.terrainEntity_isSpecularLighted(_currentTerrainID);
			_fe3d.textEntity_setTextContent(specularID, isSpecular ? "Specular: ON" : "Specular: OFF");

			// Check if intensity confirmed
			float intensity = _fe3d.terrainEntity_getSpecularLightingIntensity(_currentTerrainID);
			if (_gui->getGlobalScreen()->checkValueForm("intensity", intensity))
			{
				intensity /= 100.0f;
				_fe3d.terrainEntity_setSpecularLightingIntensity(_currentTerrainID, intensity);
			}

			// Check if lightness confirmed
			float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);
			if (_gui->getGlobalScreen()->checkValueForm("lightness", lightness))
			{
				lightness /= 100.0f;
				_fe3d.terrainEntity_setLightness(_currentTerrainID, lightness);
			}
		}
	}
}

void WorldEditor::_updateTerrainMenuBlendMap()
{
	if (_leftWindow->getActiveScreen()->getID() == "terrainEditorMenuBlendMap")
	{
		// Variables
		auto screen = _leftWindow->getScreen("terrainEditorMenuBlendMap");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("blendMap")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\blend_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.terrainEntity_setBlendMap(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("red")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.terrainEntity_setBlendMapR(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("green")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.terrainEntity_setBlendMapG(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("blue")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.terrainEntity_setBlendMapB(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("redRepeat")->isHovered())
			{
				float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
				_gui->getGlobalScreen()->addValueForm("redRepeat", "Red repeat", blendRepeatR, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("greenRepeat")->isHovered())
			{
				float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
				_gui->getGlobalScreen()->addValueForm("greenRepeat", "Green repeat", blendRepeatG, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("blueRepeat")->isHovered())
			{
				float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
				_gui->getGlobalScreen()->addValueForm("blueRepeat", "Blue repeat", blendRepeatB, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("terrainEditorMenuChoice");
			}
		}

		// Check if redRepeat confirmed
		float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
		if (_gui->getGlobalScreen()->checkValueForm("redRepeat", blendRepeatR))
		{
			_fe3d.terrainEntity_setBlendRepeatR(_currentTerrainID, blendRepeatR);
		}

		// Check if greenRepeat confirmed
		float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
		if (_gui->getGlobalScreen()->checkValueForm("greenRepeat", blendRepeatG))
		{
			_fe3d.terrainEntity_setBlendRepeatG(_currentTerrainID, blendRepeatG);
		}

		// Check if blueRepeat confirmed
		float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
		if (_gui->getGlobalScreen()->checkValueForm("blueRepeat", blendRepeatB))
		{
			_fe3d.terrainEntity_setBlendRepeatB(_currentTerrainID, blendRepeatB);
		}

		// Filling statuses
		bool loadedBlendMap = _fe3d.terrainEntity_getBlendMapPath(_currentTerrainID)  != "";
		bool loadedRedTex   = _fe3d.terrainEntity_getBlendMapPathR(_currentTerrainID) != "";
		bool loadedGreenTex = _fe3d.terrainEntity_getBlendMapPathG(_currentTerrainID) != "";
		bool loadedBlueTex  = _fe3d.terrainEntity_getBlendMapPathB(_currentTerrainID) != "";

		// Enabling blendMapping when every needed texture is chosen
		if (loadedBlendMap && loadedRedTex && loadedGreenTex && loadedBlueTex)
		{
			_fe3d.terrainEntity_setBlendMapped(_currentTerrainID, true);
		}

		// Button hoverability
		screen->getButton("red")->setHoverable(loadedBlendMap);
		screen->getButton("green")->setHoverable(loadedBlendMap);
		screen->getButton("blue")->setHoverable(loadedBlendMap);
		screen->getButton("redRepeat")->setHoverable(loadedBlendMap && loadedRedTex);
		screen->getButton("greenRepeat")->setHoverable(loadedBlendMap && loadedGreenTex);
		screen->getButton("blueRepeat")->setHoverable(loadedBlendMap && loadedBlueTex);
	}
}

void WorldEditor::_updateTerrainCreation()
{

}

void WorldEditor::_updateTerrainChoosing()
{

}

void WorldEditor::_updateTerrainRemoval()
{

}

void WorldEditor::_updateTerrainCamera()
{
	if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
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
		float x = (_fe3d.terrainEntity_getSize(_currentTerrainID) / 2.0f) * sin(_totalCameraRotation);
		float y = (_fe3d.terrainEntity_getMaxHeight(_currentTerrainID) * 1.25f);
		float z = (_fe3d.terrainEntity_getSize(_currentTerrainID) / 2.0f) * cos(_totalCameraRotation);

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
		_fe3d.camera_enableLookat(vec3(0.0f));
	}
}