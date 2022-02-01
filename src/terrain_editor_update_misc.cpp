#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void TerrainEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		_fe3d->quad2d_setVisible("@@cursor", false);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonEnabled(!_fe3d->camera_isThirdPersonEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonEnabled(false);
	}
}

void TerrainEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentTerrainId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				_fe3d->terrain_setWireframed(_currentTerrainId, !_fe3d->terrain_isWireframed(_currentTerrainId));
			}
		}
	}
}

void TerrainEditor::_updateTerrainCreating()
{
	if(_isCreatingTerrain)
	{
		string newTerrainId;

		if(_gui->getOverlay()->checkValueForm("terrainCreate", newTerrainId, {}))
		{
			if(newTerrainId.find(' ') != string::npos)
			{
				Logger::throwWarning("Terrain id cannot contain any spaces!");
				return;
			}

			if(newTerrainId.find('@') != string::npos)
			{
				Logger::throwWarning("Terrain id cannot contain '@'!");
				return;
			}

			newTerrainId = ("@" + newTerrainId);

			if(find(_loadedTerrainIds.begin(), _loadedTerrainIds.end(), newTerrainId) != _loadedTerrainIds.end())
			{
				Logger::throwWarning("Terrain with id \"" + newTerrainId.substr(1) + "\" already exists!");
				return;
			}

			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\terrain\\height_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				_isCreatingTerrain = false;
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				_isCreatingTerrain = false;
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) && filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				_isCreatingTerrain = false;
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->terrain_create(newTerrainId, finalFilePath);

			if(_fe3d->terrain_isExisting(newTerrainId))
			{
				_fe3d->terrain_select(newTerrainId);

				_currentTerrainId = newTerrainId;
				_loadedTerrainIds.push_back(newTerrainId);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("terrainId")->getEntityId(), "Terrain: " + newTerrainId.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("terrainId")->getEntityId(), true);
				_isCreatingTerrain = false;
			}
		}
	}
}

void TerrainEditor::_updateTerrainChoosing()
{
	if(_isChoosingTerrain)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("terrainList");

		if(!selectedButtonId.empty())
		{
			_fe3d->terrain_select("@" + selectedButtonId);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTerrainId = _fe3d->terrain_getSelectedId();

				if(!_isDeletingTerrain)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("terrainId")->getEntityId(), "Terrain: " + _currentTerrainId.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("terrainId")->getEntityId(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("terrainList");
				_isChoosingTerrain = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("terrainList"))
		{
			_gui->getOverlay()->deleteChoiceForm("terrainList");
			_isChoosingTerrain = false;
			_isDeletingTerrain = false;
		}
		else
		{
			_fe3d->terrain_select("");
		}
	}
}

void TerrainEditor::_updateTerrainDeleting()
{
	if(_isDeletingTerrain && !_currentTerrainId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->terrain_delete(_currentTerrainId);

			_loadedTerrainIds.erase(remove(_loadedTerrainIds.begin(), _loadedTerrainIds.end(), _currentTerrainId), _loadedTerrainIds.end());
			_currentTerrainId = "";
			_isDeletingTerrain = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentTerrainId = "";
			_isDeletingTerrain = false;
		}
	}
}