#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::_updatePointlightEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedPointlight)
		{
			_selectedPointlightId = "";
		}
		else
		{
			_dontResetSelectedPointlight = false;
		}

		auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		for(const auto& id : _fe3d->model_getIds())
		{
			if(id.substr(0, string("@@lamp").size()) == "@@lamp")
			{
				if(hoveredAabbId == id && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectPointlight(id.substr(string("@@lamp_").size()));

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedPointlightId != _activePointlightId)
						{
							_activatePointlight(_selectedPointlightId.substr(string("@@lamp_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedPointlightId) && (id != _activePointlightId))
					{
						_deselectPointlight(id);
					}
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
			const string activePointlightId = _activePointlightId.substr(string("@@lamp_").size());
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
				if(_fe3d->pointlight_getShape(activePointlightId) == PointlightShape::CIRCLE)
				{
					_fe3d->pointlight_setShape(activePointlightId, PointlightShape::SQUARE);
				}
				else
				{
					_fe3d->pointlight_setShape(activePointlightId, PointlightShape::CIRCLE);
				}
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activePointlightId);
				_fe3d->pointlight_delete(activePointlightId);
				_loadedPointlightIds.erase(remove(_loadedPointlightIds.begin(), _loadedPointlightIds.end(), activePointlightId), _loadedPointlightIds.end());
				_activePointlightId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->pointlight_getPosition(activePointlightId);
			auto radius = _fe3d->pointlight_getRadius(activePointlightId);
			auto color = _fe3d->pointlight_getColor(activePointlightId);
			auto intensity = _fe3d->pointlight_getIntensity(activePointlightId);

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

				_fe3d->pointlight_setPosition(activePointlightId, position);
				_fe3d->model_setBasePosition(_activePointlightId, position);
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

				_fe3d->pointlight_setRadius(activePointlightId, radius);
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

				_fe3d->pointlight_setColor(activePointlightId, color);
				_fe3d->model_setColor(_activePointlightId, "", color);
			}

			_handleValueChanging("pointlightPropertiesMenu", "intensityPlus", "intensity", intensity, POINTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_handleValueChanging("pointlightPropertiesMenu", "intensityMinus", "intensity", intensity, -POINTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);
			_fe3d->pointlight_setIntensity(activePointlightId, intensity);

			const auto quad2dEntityId = screen->getButton("shape")->getRectangle()->getEntityId();
			if(_fe3d->pointlight_getShape(activePointlightId) == PointlightShape::CIRCLE)
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