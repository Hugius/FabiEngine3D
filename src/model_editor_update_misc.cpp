#include "model_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void ModelEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));
		const auto lookatOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));
		_fe3d->camera_setThirdPersonLookat(fvec3(cameraLookat.x, max(0.0f, (cameraLookat.y + (lookatOffset * CAMERA_LOOKAT_SPEED))), cameraLookat.z));

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

void ModelEditor::_updateMiscellaneous()
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

		if(!_currentModelId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
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

	_fe3d->captor_setExceptionId(CAPTOR_ID, _currentModelId);
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

		if(find(_loadedModelIds.begin(), _loadedModelIds.end(), newModelId) != _loadedModelIds.end())
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

		const auto finalFilePath = filePath.substr(rootPath.size());

		_fe3d->misc_clearMeshCache(finalFilePath);
		_fe3d->model_create(newModelId, finalFilePath);

		if(_fe3d->model_isExisting(newModelId))
		{
			_loadedModelIds.push_back(newModelId);

			sort(_loadedModelIds.begin(), _loadedModelIds.end());

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			_gui->getOverlay()->getTextField(MODEL_TITLE_ID)->setTextContent("Model: " + newModelId.substr(1));
			_gui->getOverlay()->getTextField(MODEL_TITLE_ID)->setVisible(true);

			_currentModelId = newModelId;
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
					_gui->getOverlay()->openAnswerForm("deleteModel", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

					_gui->getOverlay()->getTextField(MODEL_TITLE_ID)->setTextContent("Model: " + _currentModelId.substr(1));
					_gui->getOverlay()->getTextField(MODEL_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(!_hoveredModelId.empty())
		{
			_fe3d->model_setVisible(_hoveredModelId, false);

			_hoveredModelId = "";
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

			_loadedModelIds.erase(remove(_loadedModelIds.begin(), _loadedModelIds.end(), _currentModelId), _loadedModelIds.end());

			_currentModelId = "";

		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
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
	else
	{
		if(!_hoveredPartId.empty())
		{
			_fe3d->model_setOpacity(_currentModelId, _hoveredPartId, _originalPartOpacity);

			_hoveredPartId = "";
		}
	}
}

void ModelEditor::_updateAabbCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createAabb") && _gui->getOverlay()->isValueFormConfirmed())
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

		if(_fe3d->aabb_isExisting("model@" + _currentModelId + "@" + newAabbId))
		{
			Logger::throwWarning("AABB already exists");

			return;
		}

		_fe3d->aabb_create(("model@" + _currentModelId + "@" + newAabbId), false);
		_fe3d->aabb_setParentId(("model@" + _currentModelId + "@" + newAabbId), _currentModelId);
		_fe3d->aabb_setParentType(("model@" + _currentModelId + "@" + newAabbId), AabbParentType::MODEL);

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");
		_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setTextContent("AABB: " + newAabbId);
		_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setVisible(true);

		_currentAabbId = newAabbId;
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
				_fe3d->aabb_setVisible(("model@" + _currentModelId + "@" + _hoveredAabbId), false);

				_hoveredAabbId = "";
			}
		}
		else
		{
			if(_hoveredAabbId.empty())
			{
				_hoveredAabbId = selectedOptionId;

				_fe3d->aabb_setVisible(("model@" + _currentModelId + "@" + _hoveredAabbId), true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentAabbId = _hoveredAabbId;
				_hoveredAabbId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteAabb")
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");

					_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setTextContent("AABB: " + _currentAabbId);
					_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(!_hoveredAabbId.empty())
		{
			_fe3d->aabb_setVisible(("model@" + _currentModelId + "@" + _hoveredAabbId), false);

			_hoveredAabbId = "";
		}
	}
}

void ModelEditor::_updateAabbDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAabb") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->aabb_delete("model@" + _currentModelId + "@" + _currentAabbId);

			_currentAabbId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAabbId = "";
		}
	}
}

void ModelEditor::_updateSkyChoosing()
{
	if(_gui->getOverlay()->getChoiceFormId() == "selectSky")
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(_isSkyHovered)
			{
				_fe3d->sky_select("");

				_isSkyHovered = false;
			}
		}
		else
		{
			if(!_isSkyHovered)
			{
				_isSkyHovered = true;

				_fe3d->sky_select("@" + selectedOptionId);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_fe3d->captor_capture(CAPTOR_ID);

				_isSkyHovered = false;
			}
		}
	}
	else
	{
		if(_isSkyHovered)
		{
			_fe3d->sky_select("");

			_isSkyHovered = false;
		}
	}
}