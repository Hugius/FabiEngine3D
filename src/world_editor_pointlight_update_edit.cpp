#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updatePointlightEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedPointlight)
		{
			_selectedPointlightId = "";
		}
		else
		{
			_dontResetSelectedPointlight = false;
		}

		for(const auto& pointlightId : _loadedPointlightIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@lamp_" + pointlightId));

			if(isHovered && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_selectPointlight(pointlightId);

				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if(_selectedPointlightId != _activePointlightId)
					{
						_activatePointlight(_selectedPointlightId);
					}
				}
			}
			else
			{
				if((pointlightId != _selectedPointlightId) && (pointlightId != _activePointlightId))
				{
					_deselectPointlight(pointlightId);
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activePointlightId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedPointlightId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activePointlightId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedPointlightId.empty())
		{
			_updatePointlightHighlighting(_activePointlightId, _activePointlightHighlightDirection);
		}
		else
		{
			_updatePointlightHighlighting(_selectedPointlightId, _selectedPointlightHighlightDirection);
		}

		if(!_activePointlightId.empty())
		{
			auto screen = rightWindow->getScreen("pointlightPropertiesMenu");

			rightWindow->setActiveScreen("pointlightPropertiesMenu");

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
				if(_fe3d->pointlight_getShape(_activePointlightId) == PointlightShape::CIRCLE)
				{
					_fe3d->pointlight_setShape(_activePointlightId, PointlightShape::SQUARE);
				}
				else
				{
					_fe3d->pointlight_setShape(_activePointlightId, PointlightShape::CIRCLE);
				}
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete("@@lamp_" + _activePointlightId);
				_fe3d->pointlight_delete(_activePointlightId);
				_loadedPointlightIds.erase(remove(_loadedPointlightIds.begin(), _loadedPointlightIds.end(), _activePointlightId), _loadedPointlightIds.end());
				_activePointlightId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->pointlight_getPosition(_activePointlightId);
			auto radius = _fe3d->pointlight_getRadius(_activePointlightId);
			auto color = _fe3d->pointlight_getColor(_activePointlightId);
			auto intensity = _fe3d->pointlight_getIntensity(_activePointlightId);

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

				_fe3d->pointlight_setPosition(_activePointlightId, position);
				_fe3d->model_setBasePosition(("@@lamp_" + _activePointlightId), position);
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

				_fe3d->pointlight_setRadius(_activePointlightId, radius);
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

				_fe3d->pointlight_setColor(_activePointlightId, color);
				_fe3d->model_setColor(("@@lamp_" + _activePointlightId), "", color);
			}

			_handleValueChanging("pointlightPropertiesMenu", "intensityPlus", "intensity", intensity, POINTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_handleValueChanging("pointlightPropertiesMenu", "intensityMinus", "intensity", intensity, -POINTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_fe3d->pointlight_setIntensity(_activePointlightId, intensity);

			const auto quad2dEntityId = screen->getButton("shape")->getRectangle()->getEntityId();
			if(_fe3d->pointlight_getShape(_activePointlightId) == PointlightShape::CIRCLE)
			{
				_fe3d->quad2d_setDiffuseMap(quad2dEntityId, "engine\\assets\\image\\diffuse_map\\shape_circle.tga");
			}
			else
			{
				_fe3d->quad2d_setDiffuseMap(quad2dEntityId, "engine\\assets\\image\\diffuse_map\\shape_square.tga");
			}
		}
	}
}