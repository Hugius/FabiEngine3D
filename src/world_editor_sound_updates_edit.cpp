#include "world_editor.hpp"

void WorldEditor::_updateSoundEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected speaker from last frame
	if(!_dontResetSelectedSpeaker)
	{
		_selectedSpeakerID = "";
	}
	else
	{
		_dontResetSelectedSpeaker = false;
	}

	// User must not be in placement mode
	if(_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		// Check which entity is selected
		auto hoveredAabbID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a speaker model
		for(const auto& entityID : _fe3d.modelEntity_getAllIDs())
		{
			// Must be sound preview entity
			if(entityID.substr(0, string("@@speaker").size()) == "@@speaker")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if(hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
				   !_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered speaker
					_selectSound(entityID.substr(string("@@speaker_").size()));

					// Change cursor
					_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\assets\\textures\\cursor_pointing.png");

					// Check if user clicked speaker
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same speaker is not clicked again
						if(_selectedSpeakerID != _activeSpeakerID)
						{
							_activateSound(_selectedSpeakerID.substr(string("@@speaker_").size()));
						}
					}
				}
				else
				{
					// Don't reset if speaker is active or selected
					if((entityID != _activeSpeakerID) && (entityID != _selectedSpeakerID))
					{
						_fe3d.modelEntity_setBaseSize(entityID, DEFAULT_SPEAKER_SIZE);
						_fe3d.aabbEntity_setLocalSize(entityID, DEFAULT_SPEAKER_AABB_SIZE);
					}
				}
			}
		}

		// Check if RMB not down
		if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if speaker is active
				if(_activeSpeakerID != "")
				{
					// Check if active speaker cancelled
					if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedSpeakerID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeSpeakerID = "";
						rightWindow->setActiveScreen("worldEditorControls");
					}
				}
			}
		}

		// Update speaker animations
		if(_selectedSpeakerID != _activeSpeakerID)
		{
			_updateSpeakerAnimation(_selectedSpeakerID, _selectedSpeakerSizeDirection);
		}
		_updateSpeakerAnimation(_activeSpeakerID, _activeSpeakerSizeDirection);

		// Update properties screen
		if(_activeSpeakerID != "")
		{
			// Temporary values
			const string activeSoundID = _activeSpeakerID.substr(string("@@speaker_").size());
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("soundPropertiesMenu");

			// Button management
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.modelEntity_delete(_activeSpeakerID);
					_fe3d.sound_delete(activeSoundID);
					rightWindow->setActiveScreen("worldEditorControls");
					_activeSpeakerID = "";
					return;
				}
			}

			// Alternative way of deleting
			if(_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.modelEntity_delete(_activeSpeakerID);
				_fe3d.sound_delete(activeSoundID);
				rightWindow->setActiveScreen("worldEditorControls");
				_activeSpeakerID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.sound_getPosition(activeSoundID);
			auto maxDistance = _fe3d.sound_getMaxDistance(activeSoundID);
			auto maxVolume = _fe3d.sound_getMaxVolume(activeSoundID);

			// Handle position
			_handleValueChanging("soundPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
			_fe3d.sound_setPosition(activeSoundID, position);

			// Handle distance
			_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, (_editorSpeed / 100.0f), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
			_fe3d.sound_setMaxDistance(activeSoundID, maxDistance);

			// Handle volume
			_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
			_fe3d.sound_setMaxVolume(activeSoundID, maxVolume);
		}

		// Check if sound is still selected or active
		if(_selectedSpeakerID.empty() && _activeSpeakerID.empty())
		{
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
		}
	}
}