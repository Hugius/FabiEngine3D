#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateTerrainMenuMain()
{
	if (_leftWindow->getActiveScreen()->getID() == "terrainEditorMenuMain")
	{
		auto screen = _leftWindow->getScreen("terrainEditorMenuMain");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered())
			{
				_terrainCreationEnabled = true;
				_gui->getGlobalScreen()->addValueForm("newTerrainName", "New terrain name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_terrainChoosingEnabled = true;
				_terrainEditingEnabled = true;
				for (auto& name : _terrainNames) { name = name.substr(1); }
				_gui->getGlobalScreen()->addChoiceForm("terrainList", "Select terrain", vec2(-0.4f, 0.1f), _terrainNames);
				for (auto& name : _terrainNames) { name = "@" + name; }
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_terrainChoosingEnabled = true;
				_terrainRemovalEnabled = true;
				for (auto& name : _terrainNames) { name = name.substr(1); }
				_gui->getGlobalScreen()->addChoiceForm("terrainList", "Select terrain", vec2(-0.4f, 0.1f), _terrainNames);
				for (auto& name : _terrainNames) { name = "@" + name; }
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
	if (_leftWindow->getActiveScreen()->getID() == "terrainEditorMenuChoice")
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
				_fe3d.camera_load(90.0f, 0.1f, 10000.0f, vec3(0.0f));
				_leftWindow->setActiveScreen("terrainEditorMenuMain");
				_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID());
				_fe3d.terrainEntity_select("");
				_currentTerrainID = "";
				_terrainEditingEnabled = false;
			}
		}
	}
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
		screen->getButton("isSpecular")->setHoverable(existing);
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

						// Check if terrain entity already exists
						if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
						{
							_fe3d.terrainEntity_setHeightmap(_currentTerrainID, newFilePath);
							_fe3d.terrainEntity_select(_currentTerrainID);
						}
						else
						{
							_fe3d.terrainEntity_add(_currentTerrainID, newFilePath);
							_fe3d.terrainEntity_select(_currentTerrainID);
						}
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