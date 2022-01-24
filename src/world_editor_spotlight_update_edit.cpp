#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updateSpotlightEditing()
{
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelID.empty() && _currentTemplateQuadID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedTorch)
		{
			_selectedTorchID = "";
		}
		else
		{
			_dontResetSelectedTorch = false;
		}

		auto hoveredAabbID = _fe3d->raycast_checkCursorInAny().first;

		for(const auto& ID : _fe3d->model_getIDs())
		{
			if(ID.substr(0, string("@@torch").size()) == "@@torch")
			{
				if(hoveredAabbID == ID && _fe3d->misc_isCursorInsideViewport() &&
				   !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectSpotlight(ID.substr(string("@@torch_").size()));

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedTorchID != _activeTorchID)
						{
							_activateSpotlight(_selectedTorchID.substr(string("@@torch_").size()));
						}
					}
				}
				else
				{
					if((ID != _selectedTorchID) && (ID != _activeTorchID))
					{
						_unselectSpotlight(ID);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeTorchID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedTorchID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeTorchID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedTorchID.empty())
		{
			_updateTorchHighlighting(_activeTorchID, _activeTorchHighlightDirection);
		}
		else
		{
			_updateTorchHighlighting(_selectedTorchID, _selectedTorchHighlightDirection);
		}

		if(!_activeTorchID.empty())
		{
			const string activeSpotlightID = _activeTorchID.substr(string("@@torch_").size());
			auto screen = rightWindow->getScreen("spotlightPropertiesMenu");

			rightWindow->setActiveScreen("spotlightPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
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
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->model_delete(_activeTorchID);
					_fe3d->spotlight_delete(activeSpotlightID);
					_loadedSpotlightIDs.erase(remove(_loadedSpotlightIDs.begin(), _loadedSpotlightIDs.end(), activeSpotlightID), _loadedSpotlightIDs.end());
					_activeTorchID = "";
					rightWindow->setActiveScreen("main");
					return;
				}
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeTorchID);
				_fe3d->spotlight_delete(activeSpotlightID);
				_loadedSpotlightIDs.erase(remove(_loadedSpotlightIDs.begin(), _loadedSpotlightIDs.end(), activeSpotlightID), _loadedSpotlightIDs.end());
				_activeTorchID = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->spotlight_getPosition(activeSpotlightID);
			auto color = _fe3d->spotlight_getColor(activeSpotlightID);
			auto yaw = _fe3d->spotlight_getYaw(activeSpotlightID);
			auto pitch = _fe3d->spotlight_getPitch(activeSpotlightID);
			auto intensity = _fe3d->spotlight_getIntensity(activeSpotlightID);
			auto angle = _fe3d->spotlight_getAngle(activeSpotlightID);
			auto distance = _fe3d->spotlight_getDistance(activeSpotlightID);

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

				_fe3d->spotlight_setPosition(activeSpotlightID, position);
				_fe3d->model_setBasePosition(_activeTorchID, position);
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

				_fe3d->spotlight_setColor(activeSpotlightID, color);
				_fe3d->model_setColor(_activeTorchID, "", color);
			}

			_handleValueChanging("spotlightPropertiesMenu", "yawPlus", "yaw", yaw, SPOTLIGHT_YAW_SPEED);
			_handleValueChanging("spotlightPropertiesMenu", "yawMinus", "yaw", yaw, -SPOTLIGHT_YAW_SPEED);
			_fe3d->spotlight_setYaw(activeSpotlightID, yaw);
			_fe3d->model_setBaseRotation(_activeTorchID, fvec3(0.0f, -yaw, _fe3d->model_getBaseRotation(_activeTorchID).z));

			_handleValueChanging("spotlightPropertiesMenu", "pitchPlus", "pitch", pitch, SPOTLIGHT_PITCH_SPEED);
			_handleValueChanging("spotlightPropertiesMenu", "pitchMinus", "pitch", pitch, -SPOTLIGHT_PITCH_SPEED);
			_fe3d->spotlight_setPitch(activeSpotlightID, pitch);
			_fe3d->model_setBaseRotation(_activeTorchID, fvec3(0.0f, _fe3d->model_getBaseRotation(_activeTorchID).y, pitch));

			_handleValueChanging("spotlightPropertiesMenu", "intensityPlus", "intensity", intensity, SPOTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_handleValueChanging("spotlightPropertiesMenu", "intensityMinus", "intensity", intensity, -SPOTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_fe3d->spotlight_setIntensity(activeSpotlightID, intensity);

			_handleValueChanging("spotlightPropertiesMenu", "anglePlus", "angle", angle, SPOTLIGHT_ANGLE_SPEED, 1.0f, 0.0f, 45.0f);
			_handleValueChanging("spotlightPropertiesMenu", "angleMinus", "angle", angle, -SPOTLIGHT_ANGLE_SPEED, 1.0f, 0.0f, 45.0f);
			_fe3d->spotlight_setAngle(activeSpotlightID, angle);

			_handleValueChanging("spotlightPropertiesMenu", "distancePlus", "distance", distance, (_editorSpeed / SPOTLIGHT_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleValueChanging("spotlightPropertiesMenu", "distanceMinus", "distance", distance, -(_editorSpeed / SPOTLIGHT_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_fe3d->spotlight_setDistance(activeSpotlightID, distance);
		}
	}
}