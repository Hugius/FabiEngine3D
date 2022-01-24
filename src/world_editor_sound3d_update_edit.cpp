#include "world_editor.hpp"

void WorldEditor::_updateSoundEditing()
{
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelID.empty() && _currentTemplateQuadID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedSpeaker)
		{
			_selectedSpeakerID = "";
		}
		else
		{
			_dontResetSelectedSpeaker = false;
		}

		auto hoveredAabbID = _fe3d->raycast_checkCursorInAny().first;

		for(const auto& id : _fe3d->model_getIds())
		{
			if(id.substr(0, string("@@speaker").size()) == "@@speaker")
			{
				if(hoveredAabbID == id && _fe3d->misc_isCursorInsideViewport() &&
				   !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectSound(id.substr(string("@@speaker_").size()));

					_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedSpeakerID != _activeSpeakerID)
						{
							_activateSound(_selectedSpeakerID.substr(string("@@speaker_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedSpeakerID) && (id != _activeSpeakerID))
					{
						_unselectSound(id);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeSpeakerID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedSpeakerID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeSpeakerID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedSpeakerID.empty())
		{
			_updateSpeakerHighlighting(_activeSpeakerID, _activeSpeakerHighlightDirection);
		}
		else
		{
			_updateSpeakerHighlighting(_selectedSpeakerID, _selectedSpeakerHighlightDirection);
		}

		if(!_activeSpeakerID.empty())
		{
			const string activeSoundID = _activeSpeakerID.substr(string("@@speaker_").size());
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			rightWindow->setActiveScreen("soundPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->model_delete(_activeSpeakerID);
					_fe3d->sound3d_delete(activeSoundID);
					_loadedSoundIDs.erase(activeSoundID);
					_activeSpeakerID = "";
					rightWindow->setActiveScreen("main");
					return;
				}
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeSpeakerID);
				_fe3d->sound3d_delete(activeSoundID);
				_loadedSoundIDs.erase(activeSoundID);
				_activeSpeakerID = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->sound3d_getPosition(activeSoundID);
			auto maxDistance = _fe3d->sound3d_getMaxDistance(activeSoundID);
			auto maxVolume = _fe3d->sound3d_getMaxVolume(activeSoundID);

			_handleValueChanging("soundPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / SOUND_POSITION_DIVIDER));
			_handleValueChanging("soundPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / SOUND_POSITION_DIVIDER));
			_fe3d->sound3d_setPosition(activeSoundID, position);
			_fe3d->model_setBasePosition(_activeSpeakerID, position);

			_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, (_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -(_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_fe3d->sound3d_setMaxDistance(activeSoundID, maxDistance);

			_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_fe3d->sound3d_setMaxVolume(activeSoundID, maxVolume);
		}

		if(_selectedSpeakerID.empty() && _activeSpeakerID.empty())
		{
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityId(), false);
		}
	}
}