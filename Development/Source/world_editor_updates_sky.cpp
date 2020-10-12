#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSkyMenuMain()
{
	if (_currentWorldPart == WorldPart::SKY)
	{
		auto screen = _leftWindow->getScreen("skyEditorMenuMain");

		// If sky existing, show sky
		if (_fe3d.skyEntity_isExisting(_currentSkyID))
		{
			_fe3d.skyEntity_show(_currentSkyID);
			_fe3d.skyEntity_select(_currentSkyID);
		}
		else // Otherwise just show default sky
		{
			_fe3d.skyEntity_select("@@defaultSky");
		}

		// Hide terrain
		if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
		{
			_fe3d.terrainEntity_hide(_currentTerrainID);
		}

		// Hide water
		if (_fe3d.waterEntity_isExisting(_currentWaterID))
		{
			_fe3d.waterEntity_hide(_currentWaterID);
		}

		// Update sky functionality
		_updateSkyMenuChoice();
		_updateSkyCamera();
		_updateSkyMenuMesh();
		_updateSkyMenuOptions();

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered())
			{
				_skyCreationEnabled = true;
				_gui->getGlobalScreen()->addValueForm("newSkyName", "New sky name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_skyChoosingEnabled = true;
				_skyEditingEnabled = true;
				for (auto& name : _skyNames) { name = name.substr(1); }
				_gui->getGlobalScreen()->addChoiceForm("skyList", "Select sky", vec2(-0.4f, 0.1f), _skyNames);
				for (auto& name : _skyNames) { name = "@" + name; }
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_fe3d.skyEntity_delete(_currentSkyID);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("worldEditorMenu");
				_currentWorldPart = WorldPart::NONE;
			}
		}
	}
}

void WorldEditor::_updateSkyMenuChoice()
{
	if (_leftWindow->getActiveScreen()->getID() == "skyEditorMenuChoice")
	{
		auto screen = _leftWindow->getScreen("skyEditorMenuChoice");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_leftWindow->setActiveScreen("skyEditorMenuMesh");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_leftWindow->setActiveScreen("skyEditorMenuOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("skyEditorMenuMain");
			}
		}

		// Options screen hoverability
		screen->getButton("options")->setHoverable(_fe3d.skyEntity_isExisting(_currentSkyID));
	}
}

void WorldEditor::_updateSkyMenuMesh()
{
	if (_leftWindow->getActiveScreen()->getID() == "skyEditorMenuMesh")
	{
		auto screen = _leftWindow->getScreen("skyEditorMenuMesh");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("rightTexture")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
						_fe3d.skyEntity_setDiffuseMapRight(_currentSkyID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("leftTexture")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
						_fe3d.skyEntity_setDiffuseMapLeft(_currentSkyID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("topTexture")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
						_fe3d.skyEntity_setDiffuseMapTop(_currentSkyID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("bottomTexture")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
						_fe3d.skyEntity_setDiffuseMapBottom(_currentSkyID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("frontTexture")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
						_fe3d.skyEntity_setDiffuseMapFront(_currentSkyID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("backTexture")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
						_fe3d.skyEntity_setDiffuseMapBack(_currentSkyID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("skyEditorMenuChoice");
			}
		}
	}
}

void WorldEditor::_updateSkyMenuOptions()
{	
	if (_leftWindow->getActiveScreen()->getID() == "skyEditorMenuOptions")
	{
		// Variables
		auto screen = _leftWindow->getScreen("skyEditorMenuOptions");
		float skyRotationSpeed = _fe3d.skyEntity_getRotationSpeed(_currentSkyID);
		float skyLightness = _fe3d.skyEntity_getLightness(_currentSkyID);
		vec3 skyColor = _fe3d.skyEntity_getColor(_currentSkyID);

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("rotationSpeed")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("rotationSpeed", "Rotation speed", skyRotationSpeed * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("lightness", "Lightness (%)", skyLightness * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", skyColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", skyColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.15f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", skyColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("skyEditorMenuChoice");
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
		_fe3d.skyEntity_setRotationSpeed(_currentSkyID, skyRotationSpeed);
		_fe3d.skyEntity_setLightness(_currentSkyID, skyLightness);
		_fe3d.skyEntity_setColor(_currentSkyID, skyColor);
	}
}

void WorldEditor::_updateSkyCreation()
{
	if (_isLoaded)
	{
		if (_skyCreationEnabled)
		{
			string newSkyName;

			// Create new sky
			if (_gui->getGlobalScreen()->checkValueForm("newSkyName", newSkyName, {}))
			{
				// Starting with at-sign not allowed
				if (newSkyName[0] != '@')
				{
					newSkyName = "@" + newSkyName;

					// If sky name not existing yet
					if (std::find(_skyNames.begin(), _skyNames.end(), newSkyName) == _skyNames.end())
					{
						_currentSkyID = newSkyName;
						_skyNames.push_back(_currentSkyID);
						_fe3d.skyEntity_add(_currentSkyID);
						_fe3d.skyEntity_select(_currentSkyID);
						_fe3d.skyEntity_hide(_currentSkyID);
						_leftWindow->setActiveScreen("skyEditorMenuChoice");
						_skyCreationEnabled = false;
						_skyEditingEnabled = true;
					}
					else
					{
						_fe3d.logger_throwWarning("Sky name \"" + newSkyName.substr(1) + "\" already exists!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New sky name cannot begin with '@'");
				}
			}
		}
	}
}

void WorldEditor::_updateSkyChoosing()
{
	if (_isLoaded)
	{
		if (_skyChoosingEnabled)
		{
			// Get selected button ID
			string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("skyList");

			// Hide last sky
			if (_hoveredSkyID != "")
			{
				_fe3d.skyEntity_hide(_hoveredSkyID);
			}

			// Check if a sky name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select sky
					_currentSkyID = "@" + selectedButtonID;
					_hoveredSkyID = "";

					// Go to editor screen & show sky name
					if (_skyEditingEnabled)
					{
						_gui->getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(),
							"Sky: " + _currentSkyID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID());
					}

					// Miscellaneous
					_gui->getGlobalScreen()->removeChoiceForm("skyList");
					_skyChoosingEnabled = false;

				}
				else
				{
					// Set new hovered sky
					_hoveredSkyID = "@" + selectedButtonID;
				}
			}
			else if (_gui->getGlobalScreen()->isChoiceFormCancelled("skyList")) // Cancelled choosing
			{
				_skyChoosingEnabled = false;
				_skyEditingEnabled = false;
				_skyRemovalEnabled = false;
				_gui->getGlobalScreen()->removeChoiceForm("skyList");
			}
			else // Nothing hovered
			{
				_hoveredSkyID = "";
			}

			// Show hovered sky
			if (_hoveredSkyID != "")
			{
				_fe3d.skyEntity_show(_hoveredSkyID);
			}
		}
	}
}

void WorldEditor::_updateSkyRemoval()
{
	if (_isLoaded)
	{
		if (_modelRemovalEnabled && _currentModelID != "")
		{
			_gui->getGlobalScreen()->addAnswerForm("removeModel", "Are you sure?", vec2(0.0f));

			if (_gui->getGlobalScreen()->isAnswerFormConfirmed("removeModel"))
			{
				// Delete entity
				if (_fe3d.gameEntity_isExisting(_currentModelID))
				{
					_fe3d.gameEntity_delete(_currentModelID);
				}

				// Delete from name record
				_modelNames.erase(std::remove(_modelNames.begin(), _modelNames.end(), _currentModelID), _modelNames.end());
				_modelRemovalEnabled = false;
				_currentModelID = "";
			}
			else if (_gui->getGlobalScreen()->isAnswerFormCancelled("removeModel"))
			{
				_modelRemovalEnabled = false;
				_currentModelID = "";
			}
		}
	}
}

void WorldEditor::_updateSkyCamera()
{
	if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
	{
		if (_fe3d.misc_isMouseInsideViewport())
		{
			_fe3d.gfx_enableMotionBlur(5.0f);
			_fe3d.camera_enableFirstPersonView();
			_fe3d.camera_disableLookat();
			_fe3d.guiEntity_hide("@@cursor");
		}
	}
	else
	{
		_fe3d.gfx_disableMotionBlur();
		_fe3d.camera_disableFirstPersonView();
		_fe3d.guiEntity_show("@@cursor");
	}
}