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

		for(const auto& [soundId, templateId] : _loadedSoundIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@speaker_" + soundId));

			if(isHovered && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_selectSound(soundId);

				_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if(_selectedSoundId != _activeSoundId)
					{
						_activateSound(_selectedSoundId);
					}
				}
			}
			else
			{
				if((soundId != _selectedSoundId) && (soundId != _activeSoundId))
				{
					_deselectSound(soundId);
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSoundId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedSoundId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
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

			if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
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

			_handleValueChanging("soundPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_fe3d->sound3d_setPosition(_activeSoundId, position);
			_fe3d->model_setBasePosition(("@@speaker_" + _activeSoundId), position);

			_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, (_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -(_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_fe3d->sound3d_setMaxDistance(_activeSoundId, maxDistance);

			_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_fe3d->sound3d_setMaxVolume(_activeSoundId, maxVolume);
		}
	}
}