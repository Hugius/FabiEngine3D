#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateCamera()
{
	if(!_currentWorldId.empty())
	{
		if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT) && !_gui->getOverlay()->isFocused())
		{
			if(Tools::isCursorInsideDisplay() && !_fe3d->camera_isFirstPersonEnabled())
			{
				_fe3d->camera_setFirstPersonEnabled(true);
			}

			if(_fe3d->camera_isFirstPersonEnabled())
			{
				_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);
			}
		}
		else
		{
			_fe3d->camera_setFirstPersonEnabled(false);

			if(Tools::isCursorInsideWindow())
			{
				_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), true);
			}
		}

		if(!_gui->getOverlay()->isFocused())
		{
			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_A))
			{
				_fe3d->camera_followRightXZ(-_editorSpeed / 100.0f);
			}
			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_D))
			{
				_fe3d->camera_followRightXZ(_editorSpeed / 100.0f);
			}

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR))
			{
				_fe3d->camera_move(fvec3(0.0f, _editorSpeed / 75.0f, 0.0f));
			}
			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT))
			{
				_fe3d->camera_move(fvec3(0.0f, -(_editorSpeed / 75.0f), 0.0f));
			}

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_W))
			{
				_fe3d->camera_followFrontXZ(_editorSpeed / 100.0f);
			}
			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_S))
			{
				_fe3d->camera_followFrontXZ(-_editorSpeed / 100.0f);
			}
		}
	}
	else
	{
		_fe3d->camera_setYaw(0.0f);
		_fe3d->camera_setPitch(0.0f);
	}
}

void WorldEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
		{
			_isWireframeModeEnabled = !_isWireframeModeEnabled;
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_B))
		{
			_isAabbModeEnabled = !_isAabbModeEnabled;
		}
	}

	if(!_fe3d->sky_getSelectedId().empty())
	{
		_fe3d->sky_setWireframed(_fe3d->sky_getSelectedId(), _isWireframeModeEnabled);
	}

	if(!_fe3d->terrain_getSelectedId().empty())
	{
		_fe3d->terrain_setWireframed(_fe3d->terrain_getSelectedId(), _isWireframeModeEnabled);
	}

	if(!_fe3d->water_getSelectedId().empty())
	{
		_fe3d->water_setWireframed(_fe3d->water_getSelectedId(), _isWireframeModeEnabled);
	}

	for(const auto & [modelId, templateId] : _loadedModelIds)
	{
		for(const auto & partId : _fe3d->model_getPartIds(modelId))
		{
			_fe3d->model_setWireframed(modelId, partId, _isWireframeModeEnabled);
		}

		for(const auto & aabbId : _fe3d->model_getChildAabbIds(modelId))
		{
			_fe3d->aabb_setVisible(aabbId, _isAabbModeEnabled);
		}
	}

	for(const auto & [quadId, templateId] : _loadedQuadIds)
	{
		_fe3d->quad3d_setWireframed(quadId, _isWireframeModeEnabled);

		for(const auto & aabbId : _fe3d->quad3d_getChildAabbIds(quadId))
		{
			_fe3d->aabb_setVisible(aabbId, _isAabbModeEnabled);
		}
	}

	for(const auto & [textId, templateId] : _loadedTextIds)
	{
		_fe3d->text3d_setWireframed(textId, _isWireframeModeEnabled);

		for(const auto & aabbId : _fe3d->text3d_getChildAabbIds(textId))
		{
			_fe3d->aabb_setVisible(aabbId, _isAabbModeEnabled);
		}
	}

	if(_fe3d->terrain_getSelectedId().empty())
	{
		_fe3d->collision_setCameraTerrainResponseEnabled(false);
		_fe3d->collision_setCameraTerrainResponseHeight(0.0f);
		_fe3d->collision_setCameraTerrainResponseSpeed(0.0f);
		_fe3d->raycast_setTerrainIntersectionEnabled(false);
		_fe3d->raycast_setTerrainIntersectionDistance(0.0f);
		_fe3d->raycast_setTerrainIntersectionPrecision(0.0f);
	}
	else
	{
		_fe3d->collision_setCameraTerrainResponseEnabled(true);
		_fe3d->collision_setCameraTerrainResponseHeight(1.0f);
		_fe3d->collision_setCameraTerrainResponseSpeed(_editorSpeed);
		_fe3d->raycast_setTerrainIntersectionEnabled(true);
		_fe3d->raycast_setTerrainIntersectionDistance(Mathematics::calculateDistance(fvec3(_fe3d->terrain_getSize(_fe3d->terrain_getSelectedId())), fvec3(0.0f)));
		_fe3d->raycast_setTerrainIntersectionPrecision(0.1f);
	}

	const auto isSelected = (!_selectedModelId.empty() ||
							 !_selectedQuadId.empty() ||
							 !_selectedTextId.empty() ||
							 !_selectedPointlightId.empty() ||
							 !_selectedSpotlightId.empty() ||
							 !_selectedReflectionId.empty() ||
							 !_selectedSoundId.empty());

	const auto isActive = (!_activeModelId.empty() ||
						   !_activeQuadId.empty() ||
						   !_activeTextId.empty() ||
						   !_activePointlightId.empty() ||
						   !_activeSpotlightId.empty() ||
						   !_activeReflectionId.empty() ||
						   !_activeSoundId.empty());

	_gui->getOverlay()->getTextField("selectedId")->setVisible(isSelected);
	_gui->getOverlay()->getTextField("activeId")->setVisible(isActive);
	_gui->getOverlay()->getTextField("selectedId")->setPosition(fvec2(0.0f, (isActive ? 0.75f : 0.85f)));
	_gui->getOverlay()->getTextField("activeId")->setPosition(fvec2(0.0f, 0.85f));
}

void WorldEditor::_updateWorldCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createWorld") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newWorldId = _gui->getOverlay()->getValueFormContent();

		if(newWorldId.empty())
		{
			Logger::throwWarning("World ID cannot be empty");
			return;
		}

		if(any_of(newWorldId.begin(), newWorldId.end(), isspace))
		{
			Logger::throwWarning("World ID cannot contain any spaces");
			return;
		}

		if(any_of(newWorldId.begin(), newWorldId.end(), isupper))
		{
			Logger::throwWarning("World ID cannot contain any capitals");
			return;
		}

		const auto worldNames = _getWorldIds();

		if(find(worldNames.begin(), worldNames.end(), newWorldId) != worldNames.end())
		{
			Logger::throwWarning("World already exists");
			return;
		}

		_currentWorldId = newWorldId;
		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
	}
}

void WorldEditor::_updateWorldChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editWorld") || (_gui->getOverlay()->getChoiceFormId() == "deleteWorld"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentWorldId = selectedOptionId;

				if(_gui->getOverlay()->getChoiceFormId() == "deleteWorld")
				{
					_gui->getOverlay()->openAnswerForm("deleteWorld", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					if(loadWorldFromFile(_currentWorldId))
					{
						_fe3d->misc_setVsyncEnabled(false);
						_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
					}
				}
			}
		}
	}
}

void WorldEditor::_updateWorldDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteWorld") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_deleteWorldFile(_currentWorldId);
			_currentWorldId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentWorldId = "";
		}
	}
}