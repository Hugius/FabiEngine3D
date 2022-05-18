#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSound3dEditing()
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
		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedSound3d)
		{
			_selectedSound3dId = "";
		}
		else
		{
			_dontResetSelectedSound3d = false;
		}

		for(const auto & [placedSound3dId, templateSound3dId] : _loadedSound3dIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@speaker_" + placedSound3dId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectSound3d(placedSound3dId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedSound3dId != _activeSound3dId)
					{
						_activateSound3d(_selectedSound3dId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((placedSound3dId != _selectedSound3dId) && (placedSound3dId != _activeSound3dId))
				{
					_deselectSound3d(placedSound3dId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSound3dId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedSound3dId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						window->setActiveScreen("empty");

						_activeSound3dId = "";
					}
				}
			}
		}

		if(!_activeSound3dId.empty())
		{
			const auto screen = window->getScreen("sound3dPropertiesMenu");

			window->setActiveScreen("sound3dPropertiesMenu");

			if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->sound3d_delete(_activeSound3dId);
				_fe3d->model_delete("@@speaker_" + _activeSound3dId);

				window->setActiveScreen("empty");

				_loadedSound3dIds.erase(_activeSound3dId);

				_activeSound3dId = "";

				return;
			}

			auto position = _fe3d->sound3d_getPosition(_activeSound3dId);

			_handleInputBox("sound3dPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / SOUND3D_POSITION_SPEED_DIVIDER));
			_handleInputBox("sound3dPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / SOUND3D_POSITION_SPEED_DIVIDER));
			_handleInputBox("sound3dPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / SOUND3D_POSITION_SPEED_DIVIDER));

			_fe3d->sound3d_setPosition(_activeSound3dId, position);
			_fe3d->model_setBasePosition(("@@speaker_" + _activeSound3dId), position);
		}
	}
}