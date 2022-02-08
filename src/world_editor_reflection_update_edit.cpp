#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateReflectionEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedReflection)
		{
			_selectedReflectionId = "";
		}
		else
		{
			_dontResetSelectedReflection = false;
		}

		auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		for(const auto& id : _fe3d->model_getIds())
		{
			if(id.substr(0, string("@@camera").size()) == "@@camera")
			{
				if(hoveredAabbId == id && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectReflection(id.substr(string("@@camera_").size()));

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedReflectionId != _activeReflectionId)
						{
							_activateReflection(_selectedReflectionId.substr(string("@@camera_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedReflectionId) && (id != _activeReflectionId))
					{
						_deselectReflection(id);
					}
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

		if(_selectedReflectionId != _activeReflectionId)
		{
			_updateReflectionHighlighting(_selectedReflectionId, _selectedReflectionHighlightDirection);
		}
		_updateReflectionHighlighting(_activeReflectionId, _activeReflectionHighlightDirection);

		if(!_activeReflectionId.empty())
		{
			const string activeReflectionId = _activeReflectionId.substr(string("@@camera_").size());
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
				_fe3d->reflection_capture(activeReflectionId);
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeReflectionId);
				_fe3d->reflection_delete(activeReflectionId);
				_loadedReflectionIds.erase(remove(_loadedReflectionIds.begin(), _loadedReflectionIds.end(), activeReflectionId), _loadedReflectionIds.end());
				_activeReflectionId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("exceptionList");
			if(!selectedButtonId.empty())
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					_fe3d->reflection_setExceptionModelId(activeReflectionId, selectedButtonId);
					_gui->getOverlay()->deleteChoiceForm("exceptionList");
				}
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("exceptionList"))
			{
				_gui->getOverlay()->deleteChoiceForm("exceptionList");
			}

			auto position = _fe3d->reflection_getPosition(activeReflectionId);

			_handleValueChanging("reflectionPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleValueChanging("reflectionPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / REFLECTION_POSITION_DIVIDER));

			_fe3d->reflection_setPosition(activeReflectionId, position);
			_fe3d->model_setBasePosition(_activeReflectionId, position);
		}

		if(_selectedReflectionId.empty() && _activeReflectionId.empty())
		{
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("reflectionId")->getEntityId(), false);
		}
	}
}