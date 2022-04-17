#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::max;

void TerrainEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto scrollOffset = (_fe3d->input_isMouseScrolled(MouseWheel::WHEEL_FORWARD) ? 1.0f : _fe3d->input_isMouseScrolled(MouseWheel::WHEEL_BACKWARD) ? -1.0f : 0.0f);

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, _fe3d->camera_getThirdPersonDistance() - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED)));

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(MouseButton::BUTTON_RIGHT))
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
		if(_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentTerrainId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_F))
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
			_fe3d->terrain_select("");
		}
		else
		{
			_fe3d->terrain_select("@" + selectedOptionId);

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentTerrainId = _fe3d->terrain_getSelectedId();

				if(_gui->getOverlay()->getChoiceFormId() == "deleteTerrain")
				{
					_gui->getOverlay()->openAnswerForm("deleteTerrain", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

					_gui->getOverlay()->getTextField("terrainId")->setTextContent("Terrain: " + _currentTerrainId.substr(1));
					_gui->getOverlay()->getTextField("terrainId")->setVisible(true);
				}
			}
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

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentTerrainId), _loadedEntityIds.end());
			_currentTerrainId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentTerrainId = "";
		}
	}
}