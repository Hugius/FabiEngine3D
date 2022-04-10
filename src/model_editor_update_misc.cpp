#include "model_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void ModelEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		if(_fe3d->input_isKeyboardHeld(KeyType::KEY_SPACEBAR))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d->input_isKeyboardHeld(KeyType::KEY_SHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d->camera_setThirdPersonLookat(cameraLookat);

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->graphics_setShadowPositionOffset(fvec3(cameraLookat + fvec3(distance)));
		_fe3d->graphics_setShadowLookatOffset(cameraLookat);
		_fe3d->graphics_setShadowSize(distance * 2.0f);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(ButtonType::BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonEnabled(!_fe3d->camera_isThirdPersonEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonEnabled(false);
	}
}

void ModelEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentModelId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyType::KEY_F))
			{
				for(const auto & partId : _fe3d->model_getPartIds(_currentModelId))
				{
					_fe3d->model_setWireframed(_currentModelId, partId, !_fe3d->model_isWireframed(_currentModelId, partId));
				}
			}
		}
	}

	if(!_currentModelId.empty())
	{
		const auto partId = (_hoveredPartId.empty() ? _currentPartId : _hoveredPartId);

		if(partId.empty())
		{
			_selectedPartHighlightDirection = 1;
		}
		else
		{
			const auto opacity = _fe3d->model_getOpacity(_currentModelId, partId);

			if(opacity == 0.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			if(opacity == 1.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			const float speed = (PART_HIGHLIGHT_SPEED * static_cast<float>(_selectedPartHighlightDirection));
			_fe3d->model_setOpacity(_currentModelId, partId, (opacity + speed));
		}
	}
}

void ModelEditor::_updateModelCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createModel") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newModelId = _gui->getOverlay()->getValueFormContent();

		if(newModelId.empty())
		{
			Logger::throwWarning("Model ID cannot be empty");
			return;
		}

		if(any_of(newModelId.begin(), newModelId.end(), isspace))
		{
			Logger::throwWarning("Model ID cannot contain any spaces");
			return;
		}

		if(any_of(newModelId.begin(), newModelId.end(), isupper))
		{
			Logger::throwWarning("Model ID cannot contain any capitals");
			return;
		}

		newModelId = ("@" + newModelId);

		if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newModelId) != _loadedEntityIds.end())
		{
			Logger::throwWarning("Model already exists");
			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\mesh\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
			return;
		}

		const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "OBJ");
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
		_fe3d->misc_clearMeshCache(finalFilePath);

		_fe3d->model_create(newModelId, finalFilePath);

		if(_fe3d->model_isExisting(newModelId))
		{
			_currentModelId = newModelId;
			_loadedEntityIds.push_back(newModelId);
			sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			_gui->getOverlay()->getTextField("modelId")->setTextContent("Model: " + newModelId.substr(1));
			_gui->getOverlay()->getTextField("modelId")->setVisible(true);
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editModel") || (_gui->getOverlay()->getChoiceFormId() == "deleteModel"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredModelId.empty())
			{
				_fe3d->model_setVisible(_hoveredModelId, false);

				_hoveredModelId = "";
			}
		}
		else
		{
			if(_hoveredModelId.empty())
			{
				_hoveredModelId = ("@" + selectedOptionId);

				_fe3d->model_setVisible(_hoveredModelId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentModelId = _hoveredModelId;
				_hoveredModelId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteModel")
				{
					_gui->getOverlay()->openAnswerForm("deleteModel", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

					_gui->getOverlay()->getTextField("modelId")->setTextContent("Model: " + _currentModelId.substr(1));
					_gui->getOverlay()->getTextField("modelId")->setVisible(true);
				}
			}
		}
	}
}

void ModelEditor::_updateModelDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteModel") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->model_delete(_currentModelId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentModelId), _loadedEntityIds.end());
			_currentModelId = "";

		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->model_setVisible(_currentModelId, false);

			_currentModelId = "";
		}
	}
}

void ModelEditor::_updatePartChoosing()
{
	if(_gui->getOverlay()->getChoiceFormId() == "selectPart")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredPartId.empty())
			{
				_fe3d->model_setOpacity(_currentModelId, _hoveredPartId, _originalPartOpacity);
				_hoveredPartId = "";
			}
		}
		else
		{
			if(_hoveredPartId.empty())
			{
				_hoveredPartId = selectedOptionId;
				_originalPartOpacity = _fe3d->model_getOpacity(_currentModelId, _hoveredPartId);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentPartId = _hoveredPartId;
				_hoveredPartId = "";
			}
		}
	}
}

void ModelEditor::_updateAabbCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "aabbCreate") && _gui->getOverlay()->isValueFormConfirmed())
	{
		const auto newAabbId = _gui->getOverlay()->getValueFormContent();

		if(newAabbId.empty())
		{
			Logger::throwWarning("AABB ID cannot be empty");
			return;
		}

		if(any_of(newAabbId.begin(), newAabbId.end(), isspace))
		{
			Logger::throwWarning("AABB ID cannot contain any spaces");
			return;
		}

		if(any_of(newAabbId.begin(), newAabbId.end(), isupper))
		{
			Logger::throwWarning("AABB ID cannot contain any capitals");
			return;
		}

		if(_fe3d->aabb_isExisting(_currentModelId + "@" + newAabbId))
		{
			Logger::throwWarning("AABB already exists");
			return;
		}

		_currentAabbId = newAabbId;

		_fe3d->aabb_create((_currentModelId + "@" + _currentAabbId), false);
		_fe3d->aabb_setVisible((_currentModelId + "@" + _currentAabbId), true);
		_fe3d->aabb_setParentId((_currentModelId + "@" + _currentAabbId), _currentModelId);
		_fe3d->aabb_setParentType((_currentModelId + "@" + _currentAabbId), AabbParentType::MODEL);

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");
		_gui->getOverlay()->getTextField("aabbId")->setTextContent("AABB: " + _currentAabbId);
		_gui->getOverlay()->getTextField("aabbId")->setVisible(true);
	}
}

void ModelEditor::_updateAabbChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editAabb") || (_gui->getOverlay()->getChoiceFormId() == "deleteAabb"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredAabbId.empty())
			{
				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), false);

				_hoveredAabbId = "";
			}
		}
		else
		{
			if(_hoveredAabbId.empty())
			{
				_hoveredAabbId = selectedOptionId;

				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentAabbId = _hoveredAabbId;
				_hoveredAabbId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteAabb")
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");

					_gui->getOverlay()->getTextField("aabbId")->setTextContent("AABB: " + _currentAabbId);
					_gui->getOverlay()->getTextField("aabbId")->setVisible(true);
				}
			}
		}
	}
}

void ModelEditor::_updateAabbDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAabb") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->aabb_delete((_currentModelId + "@" + _currentAabbId));
			_currentAabbId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAabbId = "";
		}
	}
}