#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateSpotlightEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedSpotlight)
		{
			_selectedSpotlightId = "";
		}
		else
		{
			_dontResetSelectedSpotlight = false;
		}

		auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		for(const auto& modelId : _fe3d->model_getIds())
		{
			if(modelId.substr(0, string("@@torch").size()) == "@@torch")
			{
				const auto spotlightId = modelId.substr(string("@@torch_").size());

				if(hoveredAabbId == modelId && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectSpotlight(modelId.substr(string("@@torch_").size()));

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedSpotlightId != _activeSpotlightId)
						{
							_activateSpotlight(_selectedSpotlightId);
						}
					}
				}
				else
				{
					if((spotlightId != _selectedSpotlightId) && (spotlightId != _activeSpotlightId))
					{
						_deselectSpotlight(spotlightId);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSpotlightId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedSpotlightId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
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

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("color")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("color")->setHoverable(false);
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
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
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("x")->changeTextContent("X");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("y")->changeTextContent("Y");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("z")->changeTextContent("Z");

				_handleValueChanging("spotlightPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("spotlightPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("spotlightPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("spotlightPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("spotlightPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("spotlightPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / SPOTLIGHT_POSITION_DIVIDER));

				_fe3d->spotlight_setPosition(_activeSpotlightId, position);
				_fe3d->model_setBasePosition(("@@torch_" + _activeSpotlightId), position);
			}
			else if(!screen->getButton("color")->isHoverable())
			{
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("x")->changeTextContent("R");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("y")->changeTextContent("G");
				rightWindow->getScreen("spotlightPropertiesMenu")->getTextField("z")->changeTextContent("B");

				_handleValueChanging("spotlightPropertiesMenu", "xPlus", "x", color.r, SPOTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "xMinus", "x", color.r, -SPOTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "yPlus", "y", color.g, SPOTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "yMinus", "y", color.g, -SPOTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "zPlus", "z", color.b, SPOTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("spotlightPropertiesMenu", "zMinus", "z", color.b, -SPOTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);

				_fe3d->spotlight_setColor(_activeSpotlightId, color);
				_fe3d->model_setColor(("@@torch_" + _activeSpotlightId), "", color);
			}

			_handleValueChanging("spotlightPropertiesMenu", "yawPlus", "yaw", yaw, SPOTLIGHT_YAW_SPEED);
			_handleValueChanging("spotlightPropertiesMenu", "yawMinus", "yaw", yaw, -SPOTLIGHT_YAW_SPEED);
			_fe3d->spotlight_setYaw(_activeSpotlightId, yaw);
			_fe3d->model_setBaseRotation(("@@torch_" + _activeSpotlightId), fvec3(0.0f, -yaw, _fe3d->model_getBaseRotation("@@torch_" + _activeSpotlightId).z));

			_handleValueChanging("spotlightPropertiesMenu", "pitchPlus", "pitch", pitch, SPOTLIGHT_PITCH_SPEED);
			_handleValueChanging("spotlightPropertiesMenu", "pitchMinus", "pitch", pitch, -SPOTLIGHT_PITCH_SPEED);
			_fe3d->spotlight_setPitch(_activeSpotlightId, pitch);
			_fe3d->model_setBaseRotation(("@@torch_" + _activeSpotlightId), fvec3(0.0f, _fe3d->model_getBaseRotation("@@torch_" + _activeSpotlightId).y, pitch));

			_handleValueChanging("spotlightPropertiesMenu", "intensityPlus", "intensity", intensity, SPOTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_handleValueChanging("spotlightPropertiesMenu", "intensityMinus", "intensity", intensity, -SPOTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_fe3d->spotlight_setIntensity(_activeSpotlightId, intensity);

			_handleValueChanging("spotlightPropertiesMenu", "anglePlus", "angle", angle, SPOTLIGHT_ANGLE_SPEED, 1.0f, 0.0f, 45.0f);
			_handleValueChanging("spotlightPropertiesMenu", "angleMinus", "angle", angle, -SPOTLIGHT_ANGLE_SPEED, 1.0f, 0.0f, 45.0f);
			_fe3d->spotlight_setAngle(_activeSpotlightId, angle);

			_handleValueChanging("spotlightPropertiesMenu", "distancePlus", "distance", distance, (_editorSpeed / SPOTLIGHT_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleValueChanging("spotlightPropertiesMenu", "distanceMinus", "distance", distance, -(_editorSpeed / SPOTLIGHT_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_fe3d->spotlight_setDistance(_activeSpotlightId, distance);
		}
	}
}