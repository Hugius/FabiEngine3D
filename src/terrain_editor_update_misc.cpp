#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void TerrainEditor::_updateCamera()
{
	// Check if third person view is enabled
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		// Update distance scrolling
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		// Hide cursor
		_fe3d.image_setVisible("@@cursor", false);
	}

	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check third person view status
			if(_fe3d.camera_isThirdPersonViewEnabled())
			{
				_fe3d.camera_disableThirdPersonView();
			}
			else
			{
				_fe3d.camera_enableThirdPersonView(_fe3d.camera_getThirdPersonYaw(), _fe3d.camera_getThirdPersonPitch());
			}
		}
	}

	// Disable third person view if necessary
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		if(_gui.getGlobalScreen()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void TerrainEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update reference model visibility
		if(_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d.model_isVisible("@@box"))
			{
				_fe3d.model_setVisible("@@box", false);
			}
			else
			{
				_fe3d.model_setVisible("@@box", true);
			}
		}

		// Update wireframe rendering
		if(_fe3d.terrain_isExisting(_currentTerrainID))
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.terrain_isWireframed(_currentTerrainID))
				{
					_fe3d.terrain_setWireframed(_currentTerrainID, false);
				}
				else
				{
					_fe3d.terrain_setWireframed(_currentTerrainID, true);
				}
			}
		}

		// Update debug rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_H))
		{
			if(_fe3d.misc_isDebugRenderingEnabled())
			{
				_fe3d.misc_disableDebugRendering();
			}
			else
			{
				_fe3d.misc_enableDebugRendering();
			}
		}
	}
}

void TerrainEditor::_updateTerrainCreating()
{
	if(_isCreatingTerrain)
	{
		string newTerrainID;

		// Check if user filled in a new ID
		if(_gui.getGlobalScreen()->checkValueForm("terrainCreate", newTerrainID, {}))
		{
			// @ sign not allowed
			if(newTerrainID.find('@') == string::npos)
			{
				// Spaces not allowed
				if(newTerrainID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newTerrainID = ("@" + newTerrainID);

					// If terrain not existing yet
					if(find(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), newTerrainID) == _loadedTerrainIDs.end())
					{
						// Validate project ID
						if(_currentProjectID.empty())
						{
							Logger::throwError("TerrainEditor::_updateTerrainCreating");
						}

						// Get the chosen file name
						const auto rootDirectoryPath = Tools::getRootDirectoryPath();
						const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\texture\\height_map\\");

						// Validate target directory
						if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
						{
							Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
							_isCreatingTerrain = false;
							return;
						}

						// Validate chosen file
						const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "BMP");
						if(filePath.empty())
						{
							_isCreatingTerrain = false;
							return;
						}

						// Validate directory of file
						if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
						   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
						{
							Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
							_isCreatingTerrain = false;
							return;
						}

						// Create terrain
						const string newFilePath = filePath.substr(rootDirectoryPath.size());
						_fe3d.misc_clearBitmapCache(newFilePath);
						_fe3d.terrain_create(newTerrainID, newFilePath);

						// Check if terrain creation went well
						if(_fe3d.terrain_isExisting(newTerrainID))
						{
							// Go to next screen
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

							// Select terrain
							_currentTerrainID = newTerrainID;
							_loadedTerrainIDs.push_back(newTerrainID);
							_fe3d.terrain_select(newTerrainID);

							// Miscellaneous
							_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), "Terrain: " + newTerrainID.substr(1), 0.025f);
							_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), true);
							_isCreatingTerrain = false;
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
	if(_isChoosingTerrain)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("terrainList");

		// Hide last terrain
		_fe3d.terrain_select("");

		// Check if a terrain ID is hovered
		if(!selectedButtonID.empty())
		{
			// Show terrain
			_fe3d.terrain_select("@" + selectedButtonID);

			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select terrain
				_currentTerrainID = ("@" + selectedButtonID);

				// Go to next screen
				if(!_isDeletingTerrain)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), "Terrain: " + _currentTerrainID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("terrainID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
				_isChoosingTerrain = false;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
		{
			_isChoosingTerrain = false;
			_isDeletingTerrain = false;
			_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
		}
	}
}

void TerrainEditor::_updateTerrainDeleting()
{
	if(_isDeletingTerrain && _currentTerrainID != "")
	{
		// Add answer form
		if(!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Delete entity
			_fe3d.terrain_delete(_currentTerrainID);

			// Delete from ID record
			_loadedTerrainIDs.erase(remove(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), _currentTerrainID), _loadedTerrainIDs.end());
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.terrain_select("");
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
	}
}