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
	   _currentTemplateSound3dId.empty() &&
	   !_isPlacingCaptor)
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

		for(const auto & [placedSpotlightId, templateSpotlightId] : _loadedSpotlightIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@spotlight_" + placedSpotlightId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectSpotlight(placedSpotlightId);

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
				if((placedSpotlightId != _selectedSpotlightId) && (placedSpotlightId != _activeSpotlightId))
				{
					_deselectSpotlight(placedSpotlightId);
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
				_fe3d->spotlight_delete(_activeSpotlightId);
				_fe3d->model_delete(("@@spotlight_" + _activeSpotlightId));

				window->setActiveScreen("empty");

				_loadedSpotlightIds.erase(_activeSpotlightId);

				_activeSpotlightId = "";

				return;
			}

			auto position = _fe3d->spotlight_getPosition(_activeSpotlightId);
			auto yaw = _fe3d->spotlight_getYaw(_activeSpotlightId);
			auto pitch = _fe3d->spotlight_getPitch(_activeSpotlightId);

			_handleInputBox("spotlightPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
			_handleInputBox("spotlightPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
			_handleInputBox("spotlightPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
			_handleInputBox("spotlightPropertiesMenu", "yawMinus", "yaw", "yawPlus", yaw, SPOTLIGHT_YAW_SPEED);
			_handleInputBox("spotlightPropertiesMenu", "pitchMinus", "pitch", "pitchPlus", pitch, SPOTLIGHT_PITCH_SPEED);

			_fe3d->spotlight_setPosition(_activeSpotlightId, position);
			_fe3d->spotlight_setYaw(_activeSpotlightId, yaw);
			_fe3d->spotlight_setPitch(_activeSpotlightId, pitch);
			_fe3d->model_setBasePosition(("@@spotlight_" + _activeSpotlightId), position);
			_fe3d->model_setBaseRotation(("@@spotlight_" + _activeSpotlightId), fvec3(0.0f, -yaw, _fe3d->model_getBaseRotation("@@spotlight_" + _activeSpotlightId).z));
			_fe3d->model_setBaseRotation(("@@spotlight_" + _activeSpotlightId), fvec3(0.0f, _fe3d->model_getBaseRotation("@@spotlight_" + _activeSpotlightId).y, pitch));
		}
	}
}