#include "environment_editor.hpp"

#include <algorithm>

void EnvironmentEditor::_updateSkyMenuMain()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "skyEditorMenuMain")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenu");
				_currentEnvironmentType = EnvironmentType::NONE;
			}
			else if (screen->getButton("create")->isHovered())
			{
				_skyCreationEnabled = true;
				_gui.getGlobalScreen()->addValueForm("newSkyName", "New sky name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_skyChoosingEnabled = true;
				_skyEditingEnabled = true;
				auto IDs = getLoadedSkyIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("skyList", "Select sky", Vec2(-0.4f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_skyChoosingEnabled = true;
				_skyRemovalEnabled = true;
				auto IDs = getLoadedSkyIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("skyList", "Select sky", Vec2(-0.4f, 0.1f), IDs);
			}
		}
	}
}

void EnvironmentEditor::_updateSkyMenuChoice()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "skyEditorMenuChoice")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMain");
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID());
				_fe3d.skyEntity_select("@@engineBackground");
				_currentSkyID = "";
				_skyEditingEnabled = false;
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMesh");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuOptions");
			}
		}

		// Options screen hoverability
		screen->getButton("options")->setHoverable(_fe3d.skyEntity_isExisting(_currentSkyID));
	}
}

void EnvironmentEditor::_updateSkyMenuMesh()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "skyEditorMenuMesh")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			}
			else if (screen->getButton("rightTexture")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
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
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
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
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
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
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
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
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
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
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\cube_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
						_fe3d.skyEntity_setDiffuseMapBack(_currentSkyID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
		}
	}
}

void EnvironmentEditor::_updateSkyMenuOptions()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "skyEditorMenuOptions")
	{
		// Temporary values
		float skyRotationSpeed = _fe3d.skyEntity_getRotationSpeed(_currentSkyID);
		float skyLightness = _fe3d.skyEntity_getLightness(_currentSkyID);
		Vec3 skyColor = _fe3d.skyEntity_getColor(_currentSkyID);

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			}
			else if (screen->getButton("rotationSpeed")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("rotationSpeed", "Rotation speed", skyRotationSpeed * 1000.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness", skyLightness * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R", skyColor.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G", skyColor.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B", skyColor.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
			}
		}
		std::cout << skyRotationSpeed << std::endl;
		// Speed value conversion
		if (_gui.getGlobalScreen()->checkValueForm("rotationSpeed", skyRotationSpeed))
		{
			skyRotationSpeed /= 1000.0f;
		}

		// Lightness value conversion
		if (_gui.getGlobalScreen()->checkValueForm("lightness", skyLightness))
		{
			skyLightness = std::max(0.0f, skyLightness / 100.0f);
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