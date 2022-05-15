#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updatePointlightEditing()
{
	if(_currentTemplateModelId.empty() &&
	   _currentTemplateQuad3dId.empty() &&
	   _currentTemplateText3dId.empty() &&
	   _currentTemplateAabbId.empty() &&
	   _currentTemplatePointlightId.empty() &&
	   !_isPlacingSpotlight &&
	   _currentTemplatePointlightId.empty() &&
	   !_isPlacingCaptor)
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

		for(const auto & [placedPointlightId, templatePointlightId] : _loadedPointlightIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@pointlight_" + placedPointlightId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectPointlight(placedPointlightId);

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), POINTING_CURSOR_TEXTURE_PATH);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedPointlightId != _activePointlightId)
					{
						_activatePointlight(_selectedPointlightId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), POINTING_CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((placedPointlightId != _selectedPointlightId) && (placedPointlightId != _activePointlightId))
				{
					_deselectPointlight(placedPointlightId);
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
						window->setActiveScreen("empty");

						_activePointlightId = "";
					}
				}
			}
		}

		if(!_activePointlightId.empty())
		{
			const auto screen = window->getScreen("pointlightPropertiesMenu");

			window->setActiveScreen("pointlightPropertiesMenu");

			if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->model_delete("@@pointlight_" + _activePointlightId);
				_fe3d->pointlight_delete(_activePointlightId);
				_loadedPointlightIds.erase(_activePointlightId);
				_activePointlightId = "";
				window->setActiveScreen("empty");

				return;
			}

			auto position = _fe3d->pointlight_getPosition(_activePointlightId);
			auto radius = _fe3d->pointlight_getRadius(_activePointlightId);

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

				_handleInputBox("pointlightPropertiesMenu", "xMinus", "x", "xPlus", radius.x, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER));
				_handleInputBox("pointlightPropertiesMenu", "yMinus", "y", "yPlus", radius.y, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER));
				_handleInputBox("pointlightPropertiesMenu", "zMinus", "z", "zPlus", radius.z, (_editorSpeed / POINTLIGHT_RADIUS_DIVIDER));
			}

			_fe3d->pointlight_setPosition(_activePointlightId, position);
			_fe3d->pointlight_setRadius(_activePointlightId, radius);

			_fe3d->model_setBasePosition(("@@pointlight_" + _activePointlightId), position);
		}
	}
}