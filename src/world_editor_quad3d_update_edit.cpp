#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateQuad3dEditing()
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
		if(!_dontResetSelectedQuad3d)
		{
			_selectedQuad3dId = "";
		}
		else
		{
			_dontResetSelectedQuad3d = false;
		}

		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		for(const auto & [placedQuad3dId, templateQuad3dId] : _loadedQuad3dIds)
		{
			const auto isHovered = (hoveredAabbId == placedQuad3dId);

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectQuad3d(placedQuad3dId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedQuad3dId != _activeQuad3dId)
					{
						_activateQuad3d(_selectedQuad3dId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((placedQuad3dId != _selectedQuad3dId) && (placedQuad3dId != _activeQuad3dId))
				{
					_deselectQuad3d(placedQuad3dId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeQuad3dId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedQuad3dId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						window->setActiveScreen("empty");

						_activeQuad3dId = "";
					}
				}
			}
		}

		if(!_activeQuad3dId.empty())
		{
			const auto screen = window->getScreen("quad3dPropertiesMenu");
			const auto currentAnimation2dIds = _fe3d->quad3d_getAnimationIds(_activeQuad3dId);

			window->setActiveScreen("quad3dPropertiesMenu");

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(false);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(false);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
			{
				_fe3d->quad3d_setFrozen(_activeQuad3dId, !_fe3d->quad3d_isFrozen(_activeQuad3dId));
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("animation2d")->isHovered())
			{
				if(currentAnimation2dIds.empty())
				{
					auto animation2dIds = _animation2dEditor->getLoadedAnimation2dIds();

					for(auto & animation2dId : animation2dIds)
					{
						animation2dId = animation2dId.substr(1);
					}

					_gui->getOverlay()->openChoiceForm("selectAnimation", "Select Animation2D", fvec2(0.0f, 0.1f), animation2dIds);
				}
				else
				{
					_fe3d->quad3d_stopAnimation(_activeQuad3dId, currentAnimation2dIds[0]);
					_fe3d->quad3d_setUvMultiplier(_activeQuad3dId, fvec2(1.0f));
					_fe3d->quad3d_setUvOffset(_activeQuad3dId, fvec2(0.0f));
				}
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				if(!currentAnimation2dIds.empty())
				{
					_fe3d->quad3d_stopAnimation(_activeQuad3dId, currentAnimation2dIds[0]);
				}

				_fe3d->quad3d_delete(_activeQuad3dId);

				window->setActiveScreen("empty");

				_loadedQuad3dIds.erase(_activeQuad3dId);

				_activeQuad3dId = "";

				return;
			}

			auto position = _fe3d->quad3d_getPosition(_activeQuad3dId);
			auto rotation = _fe3d->quad3d_getRotation(_activeQuad3dId);
			auto size = _fe3d->quad3d_getSize(_activeQuad3dId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("quad3dPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleInputBox("quad3dPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleInputBox("quad3dPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleInputBox("quad3dPropertiesMenu", "xMinus", "x", "xPlus", rotation.x, QUAD3D_ROTATION_SPEED, 1.0f, 0.0f, 360.0f);
				_handleInputBox("quad3dPropertiesMenu", "yMinus", "y", "yPlus", rotation.y, QUAD3D_ROTATION_SPEED, 1.0f, 0.0f, 360.0f);
				_handleInputBox("quad3dPropertiesMenu", "zMinus", "z", "zPlus", rotation.z, QUAD3D_ROTATION_SPEED, 1.0f, 0.0f, 360.0f);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("quad3dPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleInputBox("quad3dPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
			}

			_fe3d->quad3d_setPosition(_activeQuad3dId, position);
			_fe3d->quad3d_setRotation(_activeQuad3dId, rotation);
			_fe3d->quad3d_setSize(_activeQuad3dId, size);

			screen->getInputBox("z")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("zMinus")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("zPlus")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("animation2d")->setTextContent(currentAnimation2dIds.empty() ? "Start Animation2D" : "Stop Animation2D");
			screen->getButton("freeze")->setTextContent(_fe3d->quad3d_isFrozen(_activeQuad3dId) ? "Unfreeze" : "Freeze");
		}
	}
}