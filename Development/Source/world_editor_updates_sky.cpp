#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateSkyMenuMain()
{
	if (_currentWorldPart == WorldPart::SKY)
	{
		auto screen = _leftWindow->getScreen("skyEditorMenuMain");

		// If sky existing, show sky
		if (_fe3d.skyEntity_isExisting("@sky"))
		{
			_fe3d.skyEntity_show("@sky");
			_fe3d.skyEntity_select("@sky");
		}
		else // Otherwise just show default sky
		{
			_fe3d.skyEntity_select("@@defaultSky");
		}

		// Hide terrain
		if (_fe3d.terrainEntity_isExisting("@terrain"))
		{
			_fe3d.terrainEntity_hide("@terrain");
		}

		// Hide water
		if (_fe3d.waterEntity_isExisting("@water"))
		{
			_fe3d.waterEntity_hide("@water");
		}

		// Update sky functionality
		_updateSkyMenuChoice();
		_updateSkyCamera();
		_updateSkyMenuMesh();
		_updateSkyMenuOptions();

		// Update buttons hoverability
		screen->getButton("create")->setHoverable(!_fe3d.skyEntity_isExisting("@sky"));
		screen->getButton("edit")->setHoverable(_fe3d.skyEntity_isExisting("@sky"));
		screen->getButton("remove")->setHoverable(_fe3d.skyEntity_isExisting("@sky"));

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered())
			{
				_loadSkyEntity();
				_leftWindow->setActiveScreen("skyEditorMenuChoice");
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_leftWindow->setActiveScreen("skyEditorMenuChoice");
			}
			else if (screen->getButton("remove")->isHovered())
			{
				_fe3d.skyEntity_delete("@sky");
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
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
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
		screen->getButton("options")->setHoverable(_fe3d.skyEntity_isExisting("@sky"));
	}
}

void WorldEditor::_updateSkyMenuMesh()
{
	if (_leftWindow->getActiveScreen()->getID() == "skyEditorMenuMesh")
	{
		auto screen = _leftWindow->getScreen("skyEditorMenuMesh");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
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
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths("@sky"));
						_fe3d.skyEntity_setDiffuseMapRight("@sky", newFilePath);
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
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths("@sky"));
						_fe3d.skyEntity_setDiffuseMapLeft("@sky", newFilePath);
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
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths("@sky"));
						_fe3d.skyEntity_setDiffuseMapTop("@sky", newFilePath);
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
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths("@sky"));
						_fe3d.skyEntity_setDiffuseMapBottom("@sky", newFilePath);
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
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths("@sky"));
						_fe3d.skyEntity_setDiffuseMapFront("@sky", newFilePath);
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
						_fe3d.misc_clearCubeMapCache(_fe3d.skyEntity_getDiffuseMapPaths("@sky"));
						_fe3d.skyEntity_setDiffuseMapBack("@sky", newFilePath);
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
		float skyRotationSpeed = _fe3d.skyEntity_getRotationSpeed("@sky");
		float skyLightness = _fe3d.skyEntity_getLightness("@sky");
		vec3 skyColor = _fe3d.skyEntity_getColor("@sky");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
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
		_fe3d.skyEntity_setRotationSpeed("@sky", skyRotationSpeed);
		_fe3d.skyEntity_setLightness("@sky", skyLightness);
		_fe3d.skyEntity_setColor("@sky", skyColor);
	}
}

void WorldEditor::_updateSkyCamera()
{
	if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
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