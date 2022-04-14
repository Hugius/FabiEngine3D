#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSpotlightEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
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

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_selectSpotlight(spotlightId);

				if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
				{
					if(_selectedSpotlightId != _activeSpotlightId)
					{
						_activateSpotlight(_selectedSpotlightId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((spotlightId != _selectedSpotlightId) && (spotlightId != _activeSpotlightId))
				{
					_deselectSpotlight(spotlightId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSpotlightId.empty())
				{
					if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && _selectedSpotlightId.empty()) || _fe3d->input_isMouseHeld(ButtonType::BUTTON_MIDDLE))
					{
						_activeSpotlightId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedSpotlightId.empty())
		{
			_updateSpotlightHighlighting(_activeSpotlightId, _activeSpotlightHighlightDirection);
		}
		else
		{
			_updateSpotlightHighlighting(_selectedSpotlightId, _selectedSpotlightHighlightDirection);
		}

		if(!_activeSpotlightId.empty())
		{
			auto screen = rightWindow->getScreen("spotlightPropertiesMenu");

			rightWindow->setActiveScreen("spotlightPropertiesMenu");

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("color")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("color")->setHoverable(false);
			}
			else if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyType::KEY_DELETE))
			{
				_fe3d->model_delete(("@@torch_" + _activeSpotlightId));
				_fe3d->spotlight_delete(_activeSpotlightId);
				_loadedSpotlightIds.erase(remove(_loadedSpotlightIds.begin(), _loadedSpotlightIds.end(), _activeSpotlightId), _loadedSpotlightIds.end());
				_activeSpotlightId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->spotlight_getPosition(_activeSpotlightId);
			auto color = _fe3d->spotlight_getColor(_activeSpotlightId);
			auto yaw = _fe3d->spotlight_getYaw(_activeSpotlightId);
			auto pitch = _fe3d->spotlight_getPitch(_activeSpotlightId);
			auto intensity = _fe3d->spotlight_getIntensity(_activeSpotlightId);
			auto angle = _fe3d->spotlight_getAngle(_activeSpotlightId);
			auto distance = _fe3d->spotlight_getDistance(_activeSpotlightId);

			if(!screen->getButton("position")->isHoverable())
			{
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("x")->setTextContent("X");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("y")->setTextContent("Y");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("z")->setTextContent("Z");

				_handleInputBox("spotlightPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
				_handleInputBox("spotlightPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
				_handleInputBox("spotlightPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
			}
			else if(!screen->getButton("color")->isHoverable())
			{
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("x")->setTextContent("R");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("y")->setTextContent("G");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("z")->setTextContent("B");

				_handleInputBox("spotlightPropertiesMenu", "xMinus", "x", "xPlus", color.r, SPOTLIGHT_COLOR_SPEED, COLOR_MULTIPLIER, 0.0f, 1.0f);
				_handleInputBox("spotlightPropertiesMenu", "yMinus", "y", "yPlus", color.g, SPOTLIGHT_COLOR_SPEED, COLOR_MULTIPLIER, 0.0f, 1.0f);
				_handleInputBox("spotlightPropertiesMenu", "zMinus", "z", "zPlus", color.b, SPOTLIGHT_COLOR_SPEED, COLOR_MULTIPLIER, 0.0f, 1.0f);
			}

			_handleInputBox("spotlightPropertiesMenu", "yawMinus", "yaw", "yawPlus", yaw, SPOTLIGHT_YAW_SPEED);
			_handleInputBox("spotlightPropertiesMenu", "pitchMinus", "pitch", "pitchPlus", pitch, SPOTLIGHT_PITCH_SPEED);
			_handleInputBox("spotlightPropertiesMenu", "intensityMinus", "intensity", "intensityPlus", intensity, SPOTLIGHT_INTENSITY_SPEED, SPOTLIGHT_INTENSITY_MULTIPLIER, 0.0f);
			_handleInputBox("spotlightPropertiesMenu", "angleMinus", "angle", "anglePlus", angle, SPOTLIGHT_ANGLE_SPEED, 1.0f, 0.0f, 45.0f);
			_handleInputBox("spotlightPropertiesMenu", "distanceMinus", "distance", "distancePlus", distance, (_editorSpeed / SPOTLIGHT_DISTANCE_DIVIDER), 1.0f, 0.0f);

			_fe3d->spotlight_setPosition(_activeSpotlightId, position);
			_fe3d->spotlight_setColor(_activeSpotlightId, color);
			_fe3d->spotlight_setYaw(_activeSpotlightId, yaw);
			_fe3d->spotlight_setPitch(_activeSpotlightId, pitch);
			_fe3d->spotlight_setIntensity(_activeSpotlightId, intensity);
			_fe3d->spotlight_setAngle(_activeSpotlightId, angle);
			_fe3d->spotlight_setDistance(_activeSpotlightId, distance);

			_fe3d->model_setBasePosition(("@@torch_" + _activeSpotlightId), position);
			_fe3d->model_setBaseRotation(("@@torch_" + _activeSpotlightId), fvec3(0.0f, -yaw, _fe3d->model_getBaseRotation("@@torch_" + _activeSpotlightId).z));
			_fe3d->model_setBaseRotation(("@@torch_" + _activeSpotlightId), fvec3(0.0f, _fe3d->model_getBaseRotation("@@torch_" + _activeSpotlightId).y, pitch));
			_fe3d->model_setColor(("@@torch_" + _activeSpotlightId), "", color);
		}
	}
}