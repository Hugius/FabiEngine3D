#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateAabbEditing()
{
	if(_currentEditorModelId.empty() &&
	   _currentEditorQuad3dId.empty() &&
	   _currentEditorText3dId.empty() &&
	   _currentEditorAabbId.empty() &&
	   _currentEditorPointlightId.empty() &&
	   _currentEditorSpotlightId.empty() &&
	   _currentEditorCaptorId.empty() &&
	   _currentEditorSound3dId.empty())
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

		for(const auto & aabbId : _loadedAabbIds)
		{
			const auto isHovered = (hoveredAabbId == aabbId);

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectAabb(aabbId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedAabbId != _activeAabbId)
					{
						_activateAabb(_selectedAabbId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((aabbId != _selectedAabbId) && (aabbId != _activeAabbId))
				{
					_deselectAabb(aabbId);
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
						window->setActiveScreen("empty");

						_activeAabbId = "";
					}
				}
			}
		}

		if(!_activeAabbId.empty())
		{
			const auto screen = window->getScreen("aabbPropertiesMenu");

			window->setActiveScreen("aabbPropertiesMenu");

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false, true);
				screen->getButton("size")->setHoverable(true, true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true, true);
				screen->getButton("size")->setHoverable(false, true);
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_duplicator->deleteCopiedAabb(_activeAabbId);

				window->setActiveScreen("empty");

				_loadedAabbIds.erase(remove(_loadedAabbIds.begin(), _loadedAabbIds.end(), _activeAabbId), _loadedAabbIds.end());

				_activeAabbId = "";

				return;
			}

			auto position = _fe3d->aabb_getBasePosition(_activeAabbId);
			auto size = _fe3d->aabb_getBaseSize(_activeAabbId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("aabbPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / AABB_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
				_handleInputBox("aabbPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / AABB_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
				_handleInputBox("aabbPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / AABB_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("aabbPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / AABB_SIZE_SPEED_DIVIDER), AABB_SIZE_FACTOR, 0.0f, FLT_MAX);
				_handleInputBox("aabbPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / AABB_SIZE_SPEED_DIVIDER), AABB_SIZE_FACTOR, 0.0f, FLT_MAX);
				_handleInputBox("aabbPropertiesMenu", "zMinus", "z", "zPlus", size.z, (_editorSpeed / AABB_SIZE_SPEED_DIVIDER), AABB_SIZE_FACTOR, 0.0f, FLT_MAX);
			}

			_fe3d->aabb_setBasePosition(_activeAabbId, position);
			_fe3d->aabb_setBaseSize(_activeAabbId, size);
		}
	}
}