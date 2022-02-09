#include "world_editor.hpp"

void WorldEditor::_updateSoundEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedSound)
		{
			_selectedSoundId = "";
		}
		else
		{
			_dontResetSelectedSound = false;
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
						if(_selectedSoundId != _activeSoundId)
						{
							_activateSound(_selectedSoundId.substr(string("@@speaker_").size()));
						}
					}
				}
				else
				{
					if((id != _selectedSoundId) && (id != _activeSoundId))
					{
						_deselectSound(id);
					}
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
			const string activeSoundId = _activeSoundId.substr(string("@@speaker_").size());
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			rightWindow->setActiveScreen("soundPropertiesMenu");

			if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeSoundId);
				_fe3d->sound3d_delete(activeSoundId);
				_loadedSoundIds.erase(activeSoundId);
				_activeSoundId = "";
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
			_fe3d->model_setBasePosition(_activeSoundId, position);

			_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, (_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -(_editorSpeed / SOUND_DISTANCE_DIVIDER), 1.0f, 0.0f);
			_fe3d->sound3d_setMaxDistance(activeSoundId, maxDistance);

			_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_SPEED, SOUND_VOLUME_MULTIPLIER, 0.0f, 1.0f);
			_fe3d->sound3d_setMaxVolume(activeSoundId, maxVolume);
		}
	}
}