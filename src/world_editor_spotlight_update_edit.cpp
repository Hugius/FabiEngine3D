#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSpotlightEditing()
{
	if(_currentTemplateModelId.empty() &&
	   _currentTemplateQuad3dId.empty() &&
	   _currentTemplateText3dId.empty() &&
	   _currentTemplateAabbId.empty() &&
	   _currentTemplatePointlightId.empty() &&
	   _currentTemplateSpotlightId.empty() &&
	   _currentTemplateCaptorId.empty() &&
	   _currentTemplateSound3dId.empty())
	{
		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedSpotlight)
		{
			_selectedSpotlightId = "";
		}
		else
		{
			_dontResetSelectedSpotlight = false;
		}

		for(const auto & spotlightId : _loadedSpotlightIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@torch_" + spotlightId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectSpotlight(spotlightId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedSpotlightId != _activeSpotlightId)
					{
						_activateSpotlight(_selectedSpotlightId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((spotlightId != _selectedSpotlightId) && (spotlightId != _activeSpotlightId))
				{
					_deselectSpotlight(spotlightId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSpotlightId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedSpotlightId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						window->setActiveScreen("empty");

						_activeSpotlightId = "";
					}
				}
			}
		}

		if(!_activeSpotlightId.empty())
		{
			const auto screen = window->getScreen("spotlightPropertiesMenu");

			window->setActiveScreen("spotlightPropertiesMenu");

			if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_duplicator->deleteCopiedSpotlight(_activeSpotlightId);

				_fe3d->model_delete(("@@torch_" + _activeSpotlightId));

				window->setActiveScreen("empty");

				_loadedSpotlightIds.erase(remove(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end(), _activeSpotlightId), _loadedSpotlightIds.end());

				_activeSpotlightId = "";

				return;
			}

			auto position = _fe3d->spotlight_getPosition(_activeSpotlightId);
			auto yaw = _fe3d->spotlight_getYaw(_activeSpotlightId);
			auto pitch = _fe3d->spotlight_getPitch(_activeSpotlightId);

			_handleInputBox("spotlightPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / SPOTLIGHT_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
			_handleInputBox("spotlightPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / SPOTLIGHT_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
			_handleInputBox("spotlightPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / SPOTLIGHT_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
			_handleInputBox("spotlightPropertiesMenu", "yawMinus", "yaw", "yawPlus", yaw, SPOTLIGHT_YAW_SPEED, 1.0f, -FLT_MAX, FLT_MAX);
			_handleInputBox("spotlightPropertiesMenu", "pitchMinus", "pitch", "pitchPlus", pitch, SPOTLIGHT_PITCH_SPEED, 1.0f, -FLT_MAX, FLT_MAX);

			_fe3d->spotlight_setPosition(_activeSpotlightId, position);
			_fe3d->spotlight_setYaw(_activeSpotlightId, yaw);
			_fe3d->spotlight_setPitch(_activeSpotlightId, pitch);
			_fe3d->model_setBasePosition(("@@torch_" + _activeSpotlightId), position);
			_fe3d->model_setBaseRotation(("@@torch_" + _activeSpotlightId), fvec3(0.0f, -yaw, _fe3d->model_getBaseRotation("@@torch_" + _activeSpotlightId).z));
			_fe3d->model_setBaseRotation(("@@torch_" + _activeSpotlightId), fvec3(0.0f, _fe3d->model_getBaseRotation("@@torch_" + _activeSpotlightId).y, pitch));
		}
	}
}