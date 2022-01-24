#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updatePointlightEditing()
{
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelID.empty() && _currentTemplateQuadID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedLamp)
		{
			_selectedLampID = "";
		}
		else
		{
			_dontResetSelectedLamp = false;
		}

		auto hoveredAabbID = _fe3d->raycast_checkCursorInAny().first;

		for(const auto& id : _fe3d->model_getIds())
		{
			if(id.substr(0, string("@@lamp").size()) == "@@lamp")
			{
				if(hoveredAabbID == id && _fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectPointlight(id.substr(string("@@lamp_").size()));

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedLampID != _activeLampID)
						{
							_activatePointlight(_selectedLampID.substr(string("@@lamp_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedLampID) && (id != _activeLampID))
					{
						_unselectPointlight(id);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeLampID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedLampID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeLampID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedLampID.empty())
		{
			_updateLampHighlighting(_activeLampID, _activeLampHighlightDirection);
		}
		else
		{
			_updateLampHighlighting(_selectedLampID, _selectedLampHighlightDirection);
		}

		if(!_activeLampID.empty())
		{
			const string activePointlightID = _activeLampID.substr(string("@@lamp_").size());
			auto screen = rightWindow->getScreen("pointlightPropertiesMenu");

			rightWindow->setActiveScreen("pointlightPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					screen->getButton("position")->setHoverable(false);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(true);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("radius")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(false);
					screen->getButton("color")->setHoverable(true);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("radius")->setHoverable(true);
					screen->getButton("color")->setHoverable(false);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("shape")->isHovered())
				{
					if(_fe3d->pointlight_getShape(activePointlightID) == PointlightShape::CIRCLE)
					{
						_fe3d->pointlight_setShape(activePointlightID, PointlightShape::SQUARE);
					}
					else
					{
						_fe3d->pointlight_setShape(activePointlightID, PointlightShape::CIRCLE);
					}
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->model_delete(_activeLampID);
					_fe3d->pointlight_delete(activePointlightID);
					_loadedPointlightIDs.erase(remove(_loadedPointlightIDs.begin(), _loadedPointlightIDs.end(), activePointlightID), _loadedPointlightIDs.end());
					_activeLampID = "";
					rightWindow->setActiveScreen("main");
					return;
				}
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeLampID);
				_fe3d->pointlight_delete(activePointlightID);
				_loadedPointlightIDs.erase(remove(_loadedPointlightIDs.begin(), _loadedPointlightIDs.end(), activePointlightID), _loadedPointlightIDs.end());
				_activeLampID = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->pointlight_getPosition(activePointlightID);
			auto radius = _fe3d->pointlight_getRadius(activePointlightID);
			auto color = _fe3d->pointlight_getColor(activePointlightID);
			auto intensity = _fe3d->pointlight_getIntensity(activePointlightID);

			if(!screen->getButton("position")->isHoverable())
			{
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("x")->changeTextContent("X");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("y")->changeTextContent("Y");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("z")->changeTextContent("Z");

				_handleValueChanging("pointlightPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("pointlightPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("pointlightPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("pointlightPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("pointlightPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
				_handleValueChanging("pointlightPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / POINTLIGHT_POSITION_DIVIDER));

				_fe3d->pointlight_setPosition(activePointlightID, position);
				_fe3d->model_setBasePosition(_activeLampID, position);
			}
			else if(!screen->getButton("radius")->isHoverable())
			{
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("x")->changeTextContent("X");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("y")->changeTextContent("Y");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("z")->changeTextContent("Z");

				_handleValueChanging("pointlightPropertiesMenu", "xPlus", "x", radius.x, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "xMinus", "x", radius.x, -(_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yPlus", "y", radius.y, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yMinus", "y", radius.y, -(_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zPlus", "z", radius.z, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zMinus", "z", radius.z, -(_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);

				_fe3d->pointlight_setRadius(activePointlightID, radius);
			}
			else if(!screen->getButton("color")->isHoverable())
			{
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("x")->changeTextContent("R");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("y")->changeTextContent("G");
				rightWindow->getScreen("pointlightPropertiesMenu")->getTextField("z")->changeTextContent("B");

				_handleValueChanging("pointlightPropertiesMenu", "xPlus", "x", color.r, POINTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "xMinus", "x", color.r, -POINTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yPlus", "y", color.g, POINTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "yMinus", "y", color.g, -POINTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zPlus", "z", color.b, POINTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointlightPropertiesMenu", "zMinus", "z", color.b, -POINTLIGHT_COLOR_SPEED, 255.0f, 0.0f, 1.0f);

				_fe3d->pointlight_setColor(activePointlightID, color);
				_fe3d->model_setColor(_activeLampID, "", color);
			}

			_handleValueChanging("pointlightPropertiesMenu", "intensityPlus", "intensity", intensity, POINTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_handleValueChanging("pointlightPropertiesMenu", "intensityMinus", "intensity", intensity, -POINTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_fe3d->pointlight_setIntensity(activePointlightID, intensity);

			const auto quad2dEntityID = screen->getButton("shape")->getRectangle()->getEntityID();
			if(_fe3d->pointlight_getShape(activePointlightID) == PointlightShape::CIRCLE)
			{
				_fe3d->quad2d_setDiffuseMap(quad2dEntityID, "engine\\assets\\image\\diffuse_map\\shape_circle.tga");
			}
			else
			{
				_fe3d->quad2d_setDiffuseMap(quad2dEntityID, "engine\\assets\\image\\diffuse_map\\shape_square.tga");
			}
		}
	}
}