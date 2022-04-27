#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateCaptorEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuad3dId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingCaptor)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedCaptor)
		{
			_selectedCaptorId = "";
		}
		else
		{
			_dontResetSelectedCaptor = false;
		}

		for(const auto & captorId : _loadedCaptorIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@camera_" + captorId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectCaptor(captorId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedCaptorId != _activeCaptorId)
					{
						_activateCaptor(_selectedCaptorId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((captorId != _selectedCaptorId) && (captorId != _activeCaptorId))
				{
					_deselectCaptor(captorId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeCaptorId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedCaptorId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						_activeCaptorId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedCaptorId.empty())
		{
			_updateCaptorHighlighting(_activeCaptorId, _selectedCaptorHighlightDirection);
		}
		else
		{
			_updateCaptorHighlighting(_selectedCaptorId, _activeCaptorHighlightDirection);
		}

		if(!_activeCaptorId.empty())
		{
			auto screen = rightWindow->getScreen("captorPropertiesMenu");

			rightWindow->setActiveScreen("captorPropertiesMenu");

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
				_fe3d->captor_capture(_activeCaptorId);
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->model_delete("@@camera_" + _activeCaptorId);
				_fe3d->captor_delete(_activeCaptorId);
				_loadedCaptorIds.erase(remove(_loadedCaptorIds.begin(), _loadedCaptorIds.end(), _activeCaptorId), _loadedCaptorIds.end());
				_activeCaptorId = "";
				rightWindow->setActiveScreen("main");

				return;
			}

			if((_gui->getOverlay()->getChoiceFormId() == "selectException") && _gui->getOverlay()->isChoiceFormConfirmed())
			{
				const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					_fe3d->captor_setExceptionEntityId(_activeCaptorId, selectedOptionId);
				}
			}

			auto position = _fe3d->captor_getPosition(_activeCaptorId);

			_handleInputBox("captorPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / CAPTOR_POSITION_DIVIDER));
			_handleInputBox("captorPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / CAPTOR_POSITION_DIVIDER));
			_handleInputBox("captorPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / CAPTOR_POSITION_DIVIDER));

			_fe3d->captor_setPosition(_activeCaptorId, position);

			_fe3d->model_setBasePosition(("@@camera_" + _activeCaptorId), position);
		}
	}
}