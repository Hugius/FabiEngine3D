#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void TerrainEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_RIGHT))
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
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
		{
			_fe3d->model_setVisible(GRID_ID, !_fe3d->model_isVisible(GRID_ID));
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible(BOX_ID, !_fe3d->model_isVisible(BOX_ID));
		}

		if(!_currentTerrainId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->terrain_setWireframed(_currentTerrainId, !_fe3d->terrain_isWireframed(_currentTerrainId));
			}
		}
	}
}

void TerrainEditor::_updateTerrainCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createTerrain") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newTerrainId = _gui->getOverlay()->getValueFormContent();

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

		if(find(_loadedTerrainIds.begin(), _loadedTerrainIds.end(), newTerrainId) != _loadedTerrainIds.end())
		{
			Logger::throwWarning("Terrain already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\terrain\\height_map\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

			return;
		}

		const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

		if(filePath.empty())
		{
			return;
		}

		if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

			return;
		}

		const auto finalFilePath = filePath.substr(rootPath.size());

		_fe3d->misc_clearImageCache(finalFilePath);

		_fe3d->terrain_create(newTerrainId, finalFilePath);

		if(_fe3d->terrain_isExisting(newTerrainId))
		{
			_fe3d->terrain_select(newTerrainId);

			_currentTerrainId = newTerrainId;

			_loadedTerrainIds.push_back(newTerrainId);

			sort(_loadedTerrainIds.begin(), _loadedTerrainIds.end());

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

			_gui->getOverlay()->getTextField(TERRAIN_TITLE_ID)->setTextContent("Terrain: " + newTerrainId.substr(1));
			_gui->getOverlay()->getTextField(TERRAIN_TITLE_ID)->setVisible(true);
		}
	}
}

void TerrainEditor::_updateTerrainChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editTerrain") || (_gui->getOverlay()->getChoiceFormId() == "deleteTerrain"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(_isTerrainHovered)
			{
				_fe3d->terrain_select("");

				_isTerrainHovered = false;
			}
		}
		else
		{
			if(!_isTerrainHovered)
			{
				_isTerrainHovered = true;

				_fe3d->terrain_select("@" + selectedOptionId);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentTerrainId = _fe3d->terrain_getSelectedId();
				_isTerrainHovered = false;

				if(_gui->getOverlay()->getChoiceFormId() == "deleteTerrain")
				{
					_gui->getOverlay()->openAnswerForm("deleteTerrain", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

					_gui->getOverlay()->getTextField(TERRAIN_TITLE_ID)->setTextContent("Terrain: " + _currentTerrainId.substr(1));
					_gui->getOverlay()->getTextField(TERRAIN_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(_isTerrainHovered)
		{
			_fe3d->terrain_select("");

			_isTerrainHovered = false;
		}
	}
}

void TerrainEditor::_updateTerrainDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteTerrain") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->terrain_delete(_currentTerrainId);

			_loadedTerrainIds.erase(remove(_loadedTerrainIds.begin(), _loadedTerrainIds.end(), _currentTerrainId), _loadedTerrainIds.end());

			_currentTerrainId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentTerrainId = "";
		}
	}
}