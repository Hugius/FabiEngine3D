#include "terrain_editor.hpp"
#include "logger.hpp"

void TerrainEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if (_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if (_isEditorLoaded)
	{
		_updateMeshMenu();
	}
	if (_isEditorLoaded)
	{
		_updateBlendMapMenu();
	}
	if (_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateTerrainCreating();
	}
	if (_isEditorLoaded)
	{
		_updateTerrainChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateTerrainDeleting();
	}
	if (_isEditorLoaded)
	{
		_updateCamera();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void TerrainEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "terrainEditorMenuMain")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", Vec2(0.0f, 0.25f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_isCreatingTerrain = true;
			_gui.getGlobalScreen()->createValueForm("terrainCreate", "Create Terrain", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_isChoosingTerrain = true;
			_isEditingTerrain = true;
			auto IDs = getLoadedTerrainIDs();
			for (auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("terrainList", "Edit Terrain", Vec2(0.0f, 0.1f), IDs);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_isChoosingTerrain = true;
			_isDeletingTerrain = true;
			auto IDs = getLoadedTerrainIDs();
			for (auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("terrainList", "Delete Terrain", Vec2(0.0f, 0.1f), IDs);
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveTerrainEntitiesToFile();
			unload();
			return;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void TerrainEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "terrainEditorMenuChoice")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMain");
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), false);
			_fe3d.terrainEntity_setWireFramed(_currentTerrainID, false);
			_fe3d.terrainEntity_select("");
			_currentTerrainID = "";
			_isEditingTerrain = false;
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("mesh")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMesh");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blendMap")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuBlendMap");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuLighting");
		}
	}
}

void TerrainEditor::_updateTerrainCreating()
{
	if (_isCreatingTerrain)
	{
		string newTerrainID;

		// Check if user filled in a new ID
		if (_gui.getGlobalScreen()->checkValueForm("terrainCreate", newTerrainID, {}))
		{
			// @ sign not allowed
			if (newTerrainID.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newTerrainID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newTerrainID = ("@" + newTerrainID);

					// If terrain not existing yet
					if (find(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), newTerrainID) == _loadedTerrainIDs.end())
					{
						// Get the chosen filename
						const auto rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("game_assets\\textures\\height_maps\\");

						// Validate target directory
						if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
						{
							Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
							_isCreatingTerrain = false;
							return;
						}

						// Validate chosen file
						const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "BMP");
						if (filePath.empty())
						{
							_isCreatingTerrain = false;
							return;
						}

						// Validate directory of file
						if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
							filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
						{
							Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
							_isCreatingTerrain = false;
							return;
						}

						// Create terrain
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearBitmapCache(newFilePath);
						_fe3d.terrainEntity_create(newTerrainID, newFilePath);

						// Check if terrain creation went well
						if (_fe3d.terrainEntity_isExisting(newTerrainID))
						{
							// Go to editor
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

							// Select terrain
							_currentTerrainID = newTerrainID;
							_loadedTerrainIDs.push_back(newTerrainID);
							_fe3d.terrainEntity_select(newTerrainID);

							// Miscellaneous
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), "Terrain: " + newTerrainID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), true);
							_isCreatingTerrain = false;
							_isEditingTerrain = true;
						}
					}
					else
					{
						Logger::throwWarning("Terrain with ID \"" + newTerrainID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Terrain ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Terrain ID cannot contain '@'!");
			}
		}
	}
}

void TerrainEditor::_updateTerrainChoosing()
{
	if (_isChoosingTerrain)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("terrainList");

		// Hide last terrain
		_fe3d.terrainEntity_select("");

		// Check if a terrain ID is hovered
		if (!selectedButtonID.empty())
		{
			// Show terrain
			_fe3d.terrainEntity_select("@" + selectedButtonID);

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select terrain
				_currentTerrainID = ("@" + selectedButtonID);

				// Go to editor
				if (_isEditingTerrain)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), "Terrain: " + _currentTerrainID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
				_isChoosingTerrain = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
		{
			_isChoosingTerrain = false;
			_isEditingTerrain = false;
			_isDeletingTerrain = false;
			_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
		}
	}
}

void TerrainEditor::_updateTerrainDeleting()
{
	if (_isDeletingTerrain && _currentTerrainID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Update answer form
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Delete entity
			_fe3d.terrainEntity_delete(_currentTerrainID);

			// Delete from ID record
			_loadedTerrainIDs.erase(remove(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), _currentTerrainID), _loadedTerrainIDs.end());
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.terrainEntity_select("");
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
	}
}