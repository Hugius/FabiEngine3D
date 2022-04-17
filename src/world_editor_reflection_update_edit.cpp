#include "world_editor.hpp"
#include "tools.hpp"

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

		for(const auto & reflectionId : _loadedReflectionIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@camera_" + reflectionId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectReflection(reflectionId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedReflectionId != _activeReflectionId)
					{
						_activateReflection(_selectedReflectionId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((reflectionId != _selectedReflectionId) && (reflectionId != _activeReflectionId))
				{
					_deselectReflection(reflectionId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeReflectionId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedReflectionId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
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

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("exception")->isHovered())
			{
				vector<string> modelIds;

				for(auto & [placedId, templateId] : _loadedModelIds)
				{
					modelIds.push_back(placedId);
				}

				_gui->getOverlay()->openChoiceForm("selectException", "Select Exception", fvec2(0.0f, 0.1f), modelIds);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("capture")->isHovered())
			{
				_fe3d->reflection_capture(_activeReflectionId);
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->model_delete("@@camera_" + _activeReflectionId);
				_fe3d->reflection_delete(_activeReflectionId);
				_loadedReflectionIds.erase(remove(_loadedReflectionIds.begin(), _loadedReflectionIds.end(), _activeReflectionId), _loadedReflectionIds.end());
				_activeReflectionId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			if((_gui->getOverlay()->getChoiceFormId() == "selectException") && _gui->getOverlay()->isChoiceFormConfirmed())
			{
				const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					_fe3d->reflection_setExceptionEntityId(_activeReflectionId, selectedOptionId);
				}
			}

			auto position = _fe3d->reflection_getPosition(_activeReflectionId);

			_handleInputBox("reflectionPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleInputBox("reflectionPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / REFLECTION_POSITION_DIVIDER));
			_handleInputBox("reflectionPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / REFLECTION_POSITION_DIVIDER));

			_fe3d->reflection_setPosition(_activeReflectionId, position);

			_fe3d->model_setBasePosition(("@@camera_" + _activeReflectionId), position);
		}
	}
}