#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updatePointlightEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuad3dId.empty() && _currentTemplateSound3dId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingCaptor)
	{
		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedPointlight)
		{
			_selectedPointlightId = "";
		}
		else
		{
			_dontResetSelectedPointlight = false;
		}

		for(const auto & pointlightId : _loadedPointlightIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@pointlight_" + pointlightId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectPointlight(pointlightId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedPointlightId != _activePointlightId)
					{
						_activatePointlight(_selectedPointlightId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((pointlightId != _selectedPointlightId) && (pointlightId != _activePointlightId))
				{
					_deselectPointlight(pointlightId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activePointlightId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedPointlightId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						_activePointlightId = "";
						window->setActiveScreen("empty");
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
			const auto screen = window->getScreen("pointlightPropertiesMenu");

			window->setActiveScreen("pointlightPropertiesMenu");

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("radius")->setHoverable(true);
				screen->getButton("color")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("radius")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("radius")->setHoverable(false);
				screen->getButton("color")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("radius")->setHoverable(true);
				screen->getButton("color")->setHoverable(false);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("shape")->isHovered())
			{
				switch(_fe3d->pointlight_getShape(_activePointlightId))
				{
					case PointlightShapeType::CIRCLE:
					{
						_fe3d->pointlight_setShape(_activePointlightId, PointlightShapeType::SQUARE);

						break;
					}
					case PointlightShapeType::SQUARE:
					{
						_fe3d->pointlight_setShape(_activePointlightId, PointlightShapeType::CIRCLE);

						break;
					}
				}
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->model_delete("@@pointlight_" + _activePointlightId);
				_fe3d->pointlight_delete(_activePointlightId);
				_loadedPointlightIds.erase(remove(_loadedPointlightIds.begin(), _loadedPointlightIds.end(), _activePointlightId), _loadedPointlightIds.end());
				_activePointlightId = "";
				window->setActiveScreen("empty");

				return;
			}

			auto position = _fe3d->pointlight_getPosition(_activePointlightId);
			auto radius = _fe3d->pointlight_getRadius(_activePointlightId);
			auto color = _fe3d->pointlight_getColor(_activePointlightId);
			auto intensity = _fe3d->pointlight_getIntensity(_activePointlightId);

			if(!screen->getButton("position")->isHoverable())
			{
				window->getScreen("pointlightPropertiesMenu")->getTextField("x")->setTextContent("X");
				window->getScreen("pointlightPropertiesMenu")->getTextField("y")->setTextContent("Y");
				window->getScreen("pointlightPropertiesMenu")->getTextField("z")->setTextContent("Z");

				_handleInputBox("pointlightPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
				_handleInputBox("pointlightPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
				_handleInputBox("pointlightPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / POINTLIGHT_POSITION_DIVIDER));
			}
			else if(!screen->getButton("radius")->isHoverable())
			{
				window->getScreen("pointlightPropertiesMenu")->getTextField("x")->setTextContent("X");
				window->getScreen("pointlightPropertiesMenu")->getTextField("y")->setTextContent("Y");
				window->getScreen("pointlightPropertiesMenu")->getTextField("z")->setTextContent("Z");

				_handleInputBox("pointlightPropertiesMenu", "xMinus", "x", "xPlus", radius.x, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
				_handleInputBox("pointlightPropertiesMenu", "yMinus", "y", "yPlus", radius.y, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
				_handleInputBox("pointlightPropertiesMenu", "zMinus", "z", "zPlus", radius.z, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER), 1.0f, 0.0f);
			}
			else if(!screen->getButton("color")->isHoverable())
			{
				window->getScreen("pointlightPropertiesMenu")->getTextField("x")->setTextContent("R");
				window->getScreen("pointlightPropertiesMenu")->getTextField("y")->setTextContent("G");
				window->getScreen("pointlightPropertiesMenu")->getTextField("z")->setTextContent("B");

				_handleInputBox("pointlightPropertiesMenu", "xMinus", "x", "xPlus", color.r, POINTLIGHT_COLOR_SPEED, COLOR_MULTIPLIER, 0.0f, 1.0f);
				_handleInputBox("pointlightPropertiesMenu", "yMinus", "y", "yPlus", color.g, POINTLIGHT_COLOR_SPEED, COLOR_MULTIPLIER, 0.0f, 1.0f);
				_handleInputBox("pointlightPropertiesMenu", "zMinus", "z", "zPlus", color.b, POINTLIGHT_COLOR_SPEED, COLOR_MULTIPLIER, 0.0f, 1.0f);
			}

			_handleInputBox("pointlightPropertiesMenu", "intensityMinus", "intensity", "intensityPlus", intensity, POINTLIGHT_INTENSITY_SPEED, 10.0f, 0.0f);

			_fe3d->pointlight_setPosition(_activePointlightId, position);
			_fe3d->pointlight_setRadius(_activePointlightId, radius);
			_fe3d->pointlight_setColor(_activePointlightId, color);
			_fe3d->pointlight_setIntensity(_activePointlightId, intensity);

			_fe3d->model_setBasePosition(("@@pointlight_" + _activePointlightId), position);
			_fe3d->model_setColor(("@@pointlight_" + _activePointlightId), "", color);

			if(_fe3d->pointlight_getShape(_activePointlightId) == PointlightShapeType::CIRCLE)
			{
				screen->getButton("shape")->setDiffuseMap("engine\\assets\\image\\diffuse_map\\shape_circle.tga");
			}
			else
			{
				screen->getButton("shape")->setDiffuseMap("engine\\assets\\image\\diffuse_map\\shape_square.tga");
			}
		}
	}
}