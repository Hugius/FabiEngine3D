#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void TerrainEditor::_updateCamera()
{
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		_fe3d.image_setVisible("@@cursor", false);
	}

	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
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

	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		if(_gui.getOverlay()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void TerrainEditor::_updateMiscellaneous()
{
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
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

		if(!_currentTerrainID.empty())
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
	}
}

void TerrainEditor::_updateTerrainCreating()
{
	if(_isCreatingTerrain)
	{
		string newTerrainID;

		if(_gui.getOverlay()->checkValueForm("terrainCreate", newTerrainID, {}))
		{
			if(newTerrainID.find(' ') != string::npos)
			{
				Logger::throwWarning("Terrain ID cannot contain any spaces!");
				return;
			}

			if(newTerrainID.find('@') != string::npos)
			{
				Logger::throwWarning("Terrain ID cannot contain '@'!");
				return;
			}

			newTerrainID = ("@" + newTerrainID);

			if(find(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), newTerrainID) != _loadedTerrainIDs.end())
			{
				Logger::throwWarning("Terrain with ID \"" + newTerrainID.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateTerrainCreating");
			}

			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\texture\\height_map\\");

			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				_isCreatingTerrain = false;
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "BMP");
			if(filePath.empty())
			{
				_isCreatingTerrain = false;
				return;
			}

			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				_isCreatingTerrain = false;
				return;
			}

			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearBitmapCache(newFilePath);
			_fe3d.terrain_create(newTerrainID, newFilePath);

			if(_fe3d.terrain_isExisting(newTerrainID))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

				_currentTerrainID = newTerrainID;
				_loadedTerrainIDs.push_back(newTerrainID);
				_fe3d.terrain_select(newTerrainID);

				_fe3d.text_setContent(_gui.getOverlay()->getTextField("terrainID")->getEntityID(), "Terrain: " + newTerrainID.substr(1), 0.025f);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("terrainID")->getEntityID(), true);
				_isCreatingTerrain = false;
			}
		}
	}
}

void TerrainEditor::_updateTerrainChoosing()
{
	if(_isChoosingTerrain)
	{
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("terrainList");

		_fe3d.terrain_select("");

		if(!selectedButtonID.empty())
		{
			_fe3d.terrain_select("@" + selectedButtonID);

			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTerrainID = ("@" + selectedButtonID);

				if(!_isDeletingTerrain)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
					_fe3d.text_setContent(_gui.getOverlay()->getTextField("terrainID")->getEntityID(), "Terrain: " + _currentTerrainID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("terrainID")->getEntityID(), true);
				}

				_gui.getOverlay()->deleteChoiceForm("terrainList");
				_isChoosingTerrain = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("terrainList"))
		{
			_isChoosingTerrain = false;
			_isDeletingTerrain = false;
			_gui.getOverlay()->deleteChoiceForm("terrainList");
		}
	}
}

void TerrainEditor::_updateTerrainDeleting()
{
	if(_isDeletingTerrain && !_currentTerrainID.empty())
	{
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d.terrain_delete(_currentTerrainID);

			_loadedTerrainIDs.erase(remove(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), _currentTerrainID), _loadedTerrainIDs.end());
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d.terrain_select("");
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
	}
}