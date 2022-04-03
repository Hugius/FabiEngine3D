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

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
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
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
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

		//if(_gui->getOverlay()->checkValueForm("terrainCreate", newTerrainId, {}))
		{
			if(newTerrainId.empty())
			{
				Logger::throwWarning("Terrain ID cannot be empty");
				return;
			}

			if(any_of(newTerrainId.begin(), newTerrainId.end(), isspace))
			{
				Logger::throwWarning("Terrain ID cannot contain any spaces");
				return;
			}

			if(any_of(newTerrainId.begin(), newTerrainId.end(), isupper))
			{
				Logger::throwWarning("Terrain ID cannot contain any capitals");
				return;
			}

			newTerrainId = ("@" + newTerrainId);

			if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newTerrainId) != _loadedEntityIds.end())
			{
				Logger::throwWarning("Terrain already exists");
				return;
			}

			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\terrain\\height_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
				_isCreatingTerrain = false;
				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				_isCreatingTerrain = false;
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
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
				_loadedEntityIds.push_back(newTerrainId);
				sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
				_gui->getOverlay()->getTextField("terrainId")->setTextContent("Terrain: " + newTerrainId.substr(1));
				_gui->getOverlay()->getTextField("terrainId")->setVisible(true);
				_isCreatingTerrain = false;
			}
		}
	}
}

void TerrainEditor::_updateTerrainChoosing()
{
	if(_isChoosingTerrain)
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			_fe3d->terrain_select("@" + selectedOptionId);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentTerrainId = _fe3d->terrain_getSelectedId();

				if(_isDeletingTerrain)
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

					_gui->getOverlay()->getTextField("terrainId")->setTextContent("Terrain: " + _currentTerrainId.substr(1));
					_gui->getOverlay()->getTextField("terrainId")->setVisible(true);
				}

				_gui->getOverlay()->closeChoiceForm();
				_isChoosingTerrain = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled())
		{
			_gui->getOverlay()->closeChoiceForm();
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
	if(_isDeletingTerrain && !_isChoosingTerrain)
	{
		if(_gui->getOverlay()->isAnswerFormAccepted())
		{
			_fe3d->terrain_delete(_currentTerrainId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentTerrainId), _loadedEntityIds.end());
			_currentTerrainId = "";
			_isDeletingTerrain = false;

			_gui->getOverlay()->closeAnswerForm();
		}
		if(_gui->getOverlay()->isAnswerFormDenied())
		{
			_currentTerrainId = "";
			_isDeletingTerrain = false;

			_gui->getOverlay()->closeAnswerForm();
		}
	}
}