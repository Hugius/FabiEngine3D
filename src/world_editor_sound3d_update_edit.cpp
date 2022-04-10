#include "world_editor.hpp"

void WorldEditor::_updateSoundEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedSound)
		{
			_selectedSoundId = "";
		}
		else
		{
			_dontResetSelectedSound = false;
		}

		for(const auto & [soundId, templateId] : _loadedSoundIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@speaker_" + soundId));

			if(isHovered && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_selectSound(soundId);

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

				if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
				{
					if(_selectedSoundId != _activeSoundId)
					{
						_activateSound(_selectedSoundId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((soundId != _selectedSoundId) && (soundId != _activeSoundId))
				{
					_deselectSound(soundId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSoundId.empty())
				{
					if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && _selectedSoundId.empty()) || _fe3d->input_isMouseHeld(ButtonType::BUTTON_MIDDLE))
					{
						_activeSoundId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedSoundId.empty())
		{
			_updateSoundHighlighting(_activeSoundId, _activeSoundHighlightDirection);
		}
		else
		{
			_updateSoundHighlighting(_selectedSoundId, _selectedSoundHighlightDirection);
		}

		if(!_activeSoundId.empty())
		{
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			rightWindow->setActiveScreen("soundPropertiesMenu");

			if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyType::KEY_DELETE))
			{
				_fe3d->model_delete("@@speaker_" + _activeSoundId);
				_fe3d->sound3d_delete(_activeSoundId);
				_loadedSoundIds.erase(_activeSoundId);
				_activeSoundId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->sound3d_getPosition(_activeSoundId);
			auto maxDistance = _fe3d->sound3d_getMaxDistance(_activeSoundId);
			auto maxVolume = _fe3d->sound3d_getMaxVolume(_activeSoundId);

			_handleInputBox("soundPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleInputBox("soundPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleInputBox("soundPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleInputBox("soundPropertiesMenu", "distanceMinus", "distance", "distancePlus", maxDistance, (_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleInputBox("soundPropertiesMenu", "volumeMinus", "volume", "volumePlus", maxVolume, SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);

			_fe3d->sound3d_setPosition(_activeSoundId, position);
			_fe3d->sound3d_setMaxDistance(_activeSoundId, maxDistance);
			_fe3d->sound3d_setMaxVolume(_activeSoundId, maxVolume);
			_fe3d->model_setBasePosition(("@@speaker_" + _activeSoundId), position);
		}
	}
}