#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateReflectionEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedReflection)
		{
			_selectedReflectionId = "";
		}
		else
		{
			_dontResetSelectedReflection = false;
		}

		for(const auto& reflectionId : _loadedReflectionIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@camera_" + reflectionId));

			if(isHovered && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_selectReflection(reflectionId);

				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if(_selectedReflectionId != _activeReflectionId)
					{
						_activateReflection(_selectedReflectionId);
					}
				}
			}
			else
			{
				if((reflectionId != _selectedReflectionId) && (reflectionId != _activeReflectionId))
				{
					_deselectReflection(reflectionId);
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeReflectionId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedReflectionId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeReflectionId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedReflectionId.empty())
		{
			_updateReflectionHighlighting(_activeReflectionId, _selectedReflectionHighlightDirection);
		}
		else
		{
			_updateReflectionHighlighting(_selectedReflectionId, _activeReflectionHighlightDirection);
		}

		if(!_activeReflectionId.empty())
		{
			auto screen = rightWindow->getScreen("reflectionPropertiesMenu");

			rightWindow->setActiveScreen("reflectionPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("exception")->isHovered())
			{
				vector<string> modelIds;

				for(auto& [key, templateId] : _loadedModelIds)
				{
					modelIds.push_back(key);
				}

				_gui->getOverlay()->createChoiceForm("exceptionList", "Select Exception", fvec2(0.0f, 0.1f), modelIds);
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("capture")->isHovered())
			{
				_fe3d->reflection_capture(_activeReflectionId);
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete("@@camera_" + _activeReflectionId);
				_fe3d->reflection_delete(_activeReflectionId);
				_loadedReflectionIds.erase(remove(_loadedReflectionIds.begin(), _loadedReflectionIds.end(), _activeReflectionId), _loadedReflectionIds.end());
				_activeReflectionId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("exceptionList");
			if(!selectedButtonId.empty())
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					_fe3d->reflection_setExceptionEntityId(_activeReflectionId, selectedButtonId);
					_gui->getOverlay()->deleteChoiceForm("exceptionList");
				}
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("exceptionList"))
			{
				_gui->getOverlay()->deleteChoiceForm("exceptionList");
			}

			auto position = _fe3d->reflection_getPosition(_activeReflectionId);

			_handleValueChanging("reflectionPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));

			_fe3d->reflection_setPosition(_activeReflectionId, position);
			_fe3d->model_setBasePosition(("@@camera_" + _activeReflectionId), position);
		}
	}
}