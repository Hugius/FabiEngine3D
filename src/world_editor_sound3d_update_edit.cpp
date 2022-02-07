#include "world_editor.hpp"

void WorldEditor::_updateSoundEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedSpeaker)
		{
			_selectedSpeakerId = "";
		}
		else
		{
			_dontResetSelectedSpeaker = false;
		}

		auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		for(const auto& id : _fe3d->model_getIds())
		{
			if(id.substr(0, string("@@speaker").size()) == "@@speaker")
			{
				if(hoveredAabbId == id && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectSound(id.substr(string("@@speaker_").size()));

					_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedSpeakerId != _activeSpeakerId)
						{
							_activateSound(_selectedSpeakerId.substr(string("@@speaker_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedSpeakerId) && (id != _activeSpeakerId))
					{
						_unselectSound(id);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSpeakerId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedSpeakerId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeSpeakerId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedSpeakerId.empty())
		{
			_updateSpeakerHighlighting(_activeSpeakerId, _activeSpeakerHighlightDirection);
		}
		else
		{
			_updateSpeakerHighlighting(_selectedSpeakerId, _selectedSpeakerHighlightDirection);
		}

		if(!_activeSpeakerId.empty())
		{
			const string activeSoundId = _activeSpeakerId.substr(string("@@speaker_").size());
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			rightWindow->setActiveScreen("soundPropertiesMenu");

			if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeSpeakerId);
				_fe3d->sound3d_delete(activeSoundId);
				_loadedSoundIds.erase(activeSoundId);
				_activeSpeakerId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->sound3d_getPosition(activeSoundId);
			auto maxDistance = _fe3d->sound3d_getMaxDistance(activeSoundId);
			auto maxVolume = _fe3d->sound3d_getMaxVolume(activeSoundId);

			_handleValueChanging("soundPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_fe3d->sound3d_setPosition(activeSoundId, position);
			_fe3d->model_setBasePosition(_activeSpeakerId, position);

			_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, (_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -(_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_fe3d->sound3d_setMaxDistance(activeSoundId, maxDistance);

			_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_fe3d->sound3d_setMaxVolume(activeSoundId, maxVolume);
		}

		if(_selectedSpeakerId.empty() && _activeSpeakerId.empty())
		{
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundId")->getEntityId(), false);
		}
	}
}