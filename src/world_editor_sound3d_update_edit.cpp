#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSoundEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuad3dId.empty() && _currentTemplateSound3dId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingCaptor)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedSound)
		{
			_selectedSound3dId = "";
		}
		else
		{
			_dontResetSelectedSound = false;
		}

		for(const auto & [placedSound3dId, templateSound3dId] : _loadedSound3dIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@speaker_" + placedSound3dId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectSound3d(placedSound3dId);

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedSound3dId != _activeSound3dId)
					{
						_activateSound3d(_selectedSound3dId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
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
						_activeSound3dId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedSound3dId.empty())
		{
			_updateSound3dHighlighting(_activeSound3dId, _activeSoundHighlightDirection);
		}
		else
		{
			_updateSound3dHighlighting(_selectedSound3dId, _selectedSoundHighlightDirection);
		}

		if(!_activeSound3dId.empty())
		{
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			rightWindow->setActiveScreen("soundPropertiesMenu");

			if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->model_delete("@@speaker_" + _activeSound3dId);
				_fe3d->sound3d_delete(_activeSound3dId);
				_loadedSound3dIds.erase(_activeSound3dId);
				_activeSound3dId = "";
				rightWindow->setActiveScreen("main");

				return;
			}

			auto position = _fe3d->sound3d_getPosition(_activeSound3dId);
			auto maxDistance = _fe3d->sound3d_getMaxDistance(_activeSound3dId);
			auto maxVolume = _fe3d->sound3d_getMaxVolume(_activeSound3dId);

			_handleInputBox("soundPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleInputBox("soundPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleInputBox("soundPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleInputBox("soundPropertiesMenu", "distanceMinus", "distance", "distancePlus", maxDistance, (_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleInputBox("soundPropertiesMenu", "volumeMinus", "volume", "volumePlus", maxVolume, SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);

			_fe3d->sound3d_setPosition(_activeSound3dId, position);
			_fe3d->sound3d_setMaxDistance(_activeSound3dId, maxDistance);
			_fe3d->sound3d_setMaxVolume(_activeSound3dId, maxVolume);
			_fe3d->model_setBasePosition(("@@speaker_" + _activeSound3dId), position);
		}
	}
}