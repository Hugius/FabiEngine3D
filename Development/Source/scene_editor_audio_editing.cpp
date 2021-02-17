#include "scene_editor.hpp"

#define SELECTED_AUDIO_ID _selectedSpeakerID.substr(string("@speaker_").size())
#define ACTIVE_AUDIO_ID _activeSpeakerID.substr(string("@speaker_").size())

void SceneEditor::_updateAudioEditing()
{
	if (_isEditorLoaded)
	{
		// Reset selected billboard from last frame
		if (!_dontResetSelectedAudio)
		{
			_selectedSpeakerID = "";
		}
		else
		{
			_dontResetSelectedAudio = false;
		}

		// User must not be in placement mode
		if (_currentPreviewModelName == "" && _currentPreviewBillboardName == "" && !_isPlacingPointlight && _currentPreviewAudioName == "")
		{
			string hoveredAabbID = _fe3d.collision_checkCursorInAny().first;

			// Check if user selected a speaker model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				// Must be audio preview entity
				if (entityID.substr(0, string("@speaker").size()) == "@speaker")
				{
					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
						!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
					{
						// Set new selected speaker
						_selectedSpeakerID = entityID;
						_selectAudio(SELECTED_AUDIO_ID);

						// Change cursor
						_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_pointing.png");

						// Check if user clicked speaker
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							// Check if same speaker is clicked again
							if (_selectedSpeakerID != _activeSpeakerID)
							{
								// Set new active audio
								_activeSpeakerID = _selectedSpeakerID;
								_activateAudio(ACTIVE_AUDIO_ID);
								_transformation = TransformationType::TRANSLATION;

								// Filling writefields
								Vec3 position = _fe3d.gameEntity_getPosition(_activeSpeakerID);
								_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("x")->setTextContent(to_string(static_cast<int>(position.x)));
								_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("y")->setTextContent(to_string(static_cast<int>(position.y)));
								_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getWriteField("z")->setTextContent(to_string(static_cast<int>(position.z)));
							}
						}
					}
					else
					{
						// Don't reset if speaker is active
						if (entityID != _activeSpeakerID && _selectedSpeakerID == "")
						{
							_fe3d.gameEntity_setSize(entityID, _defaultSpeakerSize);
							_fe3d.aabbEntity_setSize(entityID, _defaultSpeakerAabbSize);
						}
					}
				}
			}
			
			// Check if user made the active speaker inactive
			if (_selectedSpeakerID == "" && _activeSpeakerID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_activeSpeakerID = "";
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
				}
			}

			// Update speaker animations
			if (_selectedSpeakerID != _activeSpeakerID)
			{
				_updateSpeakerAnimation(_selectedSpeakerID, _selectedAudioSizeMultiplier);
			}
			_updateSpeakerAnimation(_activeSpeakerID, _activeAudioSizeMultiplier);

			// Update properties screen
			if (_activeSpeakerID != "")
			{
				_gui.getViewport("right")->getWindow("main")->setActiveScreen("audioPropertiesMenu");

				// GUI management (pressed)
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (_gui.getViewport("right")->getWindow("main")->getScreen("audioPropertiesMenu")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.gameEntity_delete(_activeSpeakerID);
						_fe3d.audioEntity_delete(ACTIVE_AUDIO_ID);
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
						_activeSpeakerID = "";
						return;
					}
				}

				// Get current values
				Vec3 position = _fe3d.audioEntity_getPosition(ACTIVE_AUDIO_ID);
				float maxVolume = _fe3d.audioEntity_getMaxVolume(ACTIVE_AUDIO_ID);
				float maxDistance = _fe3d.audioEntity_getMaxDistance(ACTIVE_AUDIO_ID);
				
				// Update value filling and changing
				_handleValueChanging("audioPropertiesMenu", "distancePlus", "distance", maxDistance, _audioDistanceChangingSpeed, 1.0f, 0.0f);
				_handleValueChanging("audioPropertiesMenu", "distanceMinus", "distance", maxDistance, -_audioDistanceChangingSpeed, 1.0f, 0.0f);
				_handleValueChanging("audioPropertiesMenu", "volumePlus", "volume", maxVolume, _audioVolumeChangingSpeed, 100.0f, 0.0f, 1.0f);
				_handleValueChanging("audioPropertiesMenu", "volumeMinus", "volume", maxVolume, -_audioVolumeChangingSpeed, 100.0f, 0.0f, 1.0f);
				_handleValueChanging("audioPropertiesMenu", "xPlus", "x", position.x, _customEditorSpeed / 100.0f);
				_handleValueChanging("audioPropertiesMenu", "xMinus", "x", position.x, -_customEditorSpeed / 100.0f);
				_handleValueChanging("audioPropertiesMenu", "yPlus", "y", position.y, _customEditorSpeed / 100.0f);
				_handleValueChanging("audioPropertiesMenu", "yMinus", "y", position.y, -_customEditorSpeed / 100.0f);
				_handleValueChanging("audioPropertiesMenu", "zPlus", "z", position.z, _customEditorSpeed / 100.0f);
				_handleValueChanging("audioPropertiesMenu", "zMinus", "z", position.z, -_customEditorSpeed / 100.0f);
				
				// Apply new values
				_fe3d.gameEntity_setPosition(_activeSpeakerID, position);
				_fe3d.audioEntity_setPosition(ACTIVE_AUDIO_ID, position);
				_fe3d.audioEntity_setMaxVolume(ACTIVE_AUDIO_ID, maxVolume);
				_fe3d.audioEntity_setMaxDistance(ACTIVE_AUDIO_ID, maxDistance);
			}

			// Check if audio is still selected or active
			string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID();
			if (_selectedSpeakerID == "" && _activeSpeakerID == "")
			{
				_fe3d.textEntity_hide(textEntityID);
			}
			else
			{
				if (_selectedModelID == "" && _activeModelID == "" && _selectedBillboardID == "" && _activeBillboardID == ""
					&& _selectedLightBulbID == "" && _activeLightBulbID == "")
				{
					_fe3d.textEntity_show(textEntityID);
				}
			}
		}
	}
}