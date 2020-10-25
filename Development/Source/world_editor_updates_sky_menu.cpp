#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSkyMenuMain()
{
	if (_leftWindow->getActiveScreen()->getID() == "skyEditorMenuMain")
	{
		auto screen = _leftWindow->getScreen("skyEditorMenuMain");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered())
			{
				_skyCreationEnabled = true;
				_gui.getGlobalScreen()->addValueForm("newSkyName", "New sky name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_skyChoosingEnabled = true;
				_skyEditingEnabled = true;
				for (auto& name : _skyNames) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("skyList", "Select sky", vec2(-0.4f, 0.1f), _skyNames);
				for (auto& name : _skyNames) { name = "@" + name; }
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_skyChoosingEnabled = true;
				_skyRemovalEnabled = true;
				for (auto& name : _skyNames) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("skyList", "Select sky", vec2(-0.4f, 0.1f), _skyNames);
				for (auto& name : _skyNames) { name = "@" + name; }
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
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID());
				_fe3d.skyEntity_select("@@engineBackground");
				_currentSkyID = "";
				_skyEditingEnabled = false;
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
				_gui.getGlobalScreen()->addValueForm("rotationSpeed", "Rotation speed", skyRotationSpeed * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness (%)", skyLightness * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R(0-255)", skyColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G(0-255)", skyColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B(0-255)", skyColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("skyEditorMenuChoice");
			}
		}

		// Speed value conversion
		if (_gui.getGlobalScreen()->checkValueForm("rotationSpeed", skyRotationSpeed))
		{
			skyRotationSpeed /= 100.0f;
		}

		// Lightness value conversion
		if (_gui.getGlobalScreen()->checkValueForm("lightness", skyLightness))
		{
			skyLightness = std::clamp(skyLightness / 100.0f, 0.0f, 1.0f);
		}

		// Color R values conversion
		if (_gui.getGlobalScreen()->checkValueForm("colorR", skyColor.r))
		{
			skyColor.r = std::clamp(skyColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Color G values conversion
		if (_gui.getGlobalScreen()->checkValueForm("colorG", skyColor.g))
		{
			skyColor.g = std::clamp(skyColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Color B values conversion
		if (_gui.getGlobalScreen()->checkValueForm("colorB", skyColor.b))
		{
			skyColor.b = std::clamp(skyColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Dynamically update sky options
		_fe3d.skyEntity_setRotationSpeed(_currentSkyID, skyRotationSpeed);
		_fe3d.skyEntity_setLightness(_currentSkyID, skyLightness);
		_fe3d.skyEntity_setColor(_currentSkyID, skyColor);
	}
}