#include "environment_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void EnvironmentEditor::_updateTerrainMenuMain()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuMain")
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenu");
				_currentEnvironmentType = EnvironmentType::NONE;
			}
			else if (screen->getButton("add")->isHovered())
			{
				_isTerrainCreationEnabled = true;
				_gui.getGlobalScreen()->addValueForm("newTerrainName", "New Terrain Name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_isTerrainChoosingEnabled = true;
				_isTerrainEditingEnabled = true;
				auto IDs = getLoadedTerrainIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("terrainList", "Select Terrain", Vec2(-0.4f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isTerrainChoosingEnabled = true;
				_isTerrainRemovalEnabled = true;
				auto IDs = getLoadedTerrainIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("terrainList", "Select Terrain", Vec2(-0.4f, 0.1f), IDs);
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainMenuChoice()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuChoice")
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMain");
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(), false);
				_fe3d.terrainEntity_select("");
				_currentTerrainID = "";
				_isTerrainEditingEnabled = false;
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMesh");
			}
			else if (screen->getButton("blendMap")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuBlendMap");
			}
			else if (screen->getButton("lighting")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuLighting");
			}
		}

		// Screens hoverability
		screen->getButton("blendMap")->setHoverable(_fe3d.terrainEntity_isExisting(_currentTerrainID));
		screen->getButton("lighting")->setHoverable(_fe3d.terrainEntity_isExisting(_currentTerrainID));
	}
}

void EnvironmentEditor::_updateTerrainMenuMesh()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuMesh")
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			}
			else if (screen->getButton("heightMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\height_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "BMP");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearBitmapCache(newFilePath);

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
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("diffuseMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setDiffuseMap(_currentTerrainID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("maxHeight")->isHovered())
			{
				float maxHeight = _fe3d.terrainEntity_getMaxHeight(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("maxHeight", "Max Height", maxHeight, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("uvRepeat")->isHovered())
			{
				float uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Button hoverabilities
		bool existing = _fe3d.terrainEntity_isExisting(_currentTerrainID);
		screen->getButton("diffuseMap")->setHoverable(existing);
		screen->getButton("maxHeight")->setHoverable(existing);
		screen->getButton("uvRepeat")->setHoverable(existing);

		// If terrain entity exists
		if (existing)
		{
			// Check if maxHeight confirmed
			float maxHeight = _fe3d.terrainEntity_getMaxHeight(_currentTerrainID);
			if (_gui.getGlobalScreen()->checkValueForm("maxHeight", maxHeight))
			{
				maxHeight = std::max(0.0f, maxHeight);
				_fe3d.terrainEntity_setMaxHeight(_currentTerrainID, maxHeight);
			}

			// Check if uvRepeat confirmed
			float uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);
			if (_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat))
			{
				uvRepeat = std::max(0.0f, uvRepeat);
				_fe3d.terrainEntity_setUvRepeat(_currentTerrainID, uvRepeat);
			}
		}
	}
}