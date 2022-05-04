#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateAabbEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateAabbId.empty() && _currentTemplateSound3dId.empty() && !_isPlacingPointlight && !_isPlacingCaptor)
	{
		if(!_dontResetSelectedAabb)
		{
			_selectedAabbId = "";
		}
		else
		{
			_dontResetSelectedAabb = false;
		}

		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		for(const auto & [placedAabbId, templateAabbId] : _loadedAabbIds)
		{
			const auto isHovered = (hoveredAabbId == placedAabbId);

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectAabb(placedAabbId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedAabbId != _activeAabbId)
					{
						_activateAabb(_selectedAabbId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((placedAabbId != _selectedAabbId) && (placedAabbId != _activeAabbId))
				{
					_deselectAabb(placedAabbId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeAabbId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedAabbId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						_activeAabbId = "";
						window->setActiveScreen("empty");
					}
				}
			}
		}

		if(_selectedAabbId.empty())
		{
			_updateAabbHighlighting(_activeAabbId, _activeAabbHighlightDirection);
		}
		else
		{
			_updateAabbHighlighting(_selectedAabbId, _selectedAabbHighlightDirection);
		}

		if(!_activeAabbId.empty())
		{
			const auto screen = window->getScreen("aabbPropertiesMenu");

			window->setActiveScreen("aabbPropertiesMenu");

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("size")->setHoverable(false);
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->aabb_delete(_activeAabbId);
				_loadedAabbIds.erase(_activeAabbId);
				_activeAabbId = "";
				window->setActiveScreen("empty");

				return;
			}

			auto position = _fe3d->aabb_getBasePosition(_activeAabbId);
			auto size = _fe3d->aabb_getBaseSize(_activeAabbId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("aabbPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / AABB_POSITION_DIVIDER));
				_handleInputBox("aabbPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / AABB_POSITION_DIVIDER));
				_handleInputBox("aabbPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / AABB_POSITION_DIVIDER));
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("aabbPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / AABB_SIZE_DIVIDER), AABB_SIZE_MULTIPLIER, 0.0f);
				_handleInputBox("aabbPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / AABB_SIZE_DIVIDER), AABB_SIZE_MULTIPLIER, 0.0f);
			}

			_fe3d->aabb_setBasePosition(_activeAabbId, position);
			_fe3d->aabb_setBaseSize(_activeAabbId, size);

			screen->getInputBox("x")->setHoverable(true);
			screen->getInputBox("y")->setHoverable(true);
			screen->getInputBox("z")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("xPlus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(screen->getButton("size")->isHoverable());
		}
	}
}