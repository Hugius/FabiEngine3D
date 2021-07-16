#include "scene_editor.hpp"

#define SELECTED_SOUND_ID _selectedSpeakerID.substr(string("@speaker_").size())
#define ACTIVE_SOUND_ID _activeSpeakerID.substr(string("@speaker_").size())

void SceneEditor::_updateSoundEditing()
{
	if (_isEditorLoaded)
	{
		// Reset selected billboard from last frame
		if (!_dontResetSelectedSpeaker)
		{
			_selectedSpeakerID = "";
		}
		else
		{
			_dontResetSelectedSpeaker = false;
		}

		// User must not be in placement mode
		if (_currentPreviewModelID == "" && _currentPreviewBillboardID == "" && !_isPlacingPointLight && _currentPreviewSoundID == "")
		{
			// Check which entity is selected
			auto hoveredAabbID = _fe3d.collision_checkCursorInAny().first;

			// Check if user selected a speaker model
			for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
			{
				// Must be sound preview entity
				if (entityID.substr(0, string("@speaker").size()) == "@speaker")
				{
					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
						!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
					{
						// Set new selected speaker
						_selectedSpeakerID = entityID;
						_selectSound(SELECTED_SOUND_ID);

						// Change cursor
						_fe3d.imageEntity_changeDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

						// Check if user clicked speaker
						if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							// Check if same speaker is clicked again
							if (_selectedSpeakerID != _activeSpeakerID)
							{
								// Set new active sound
								_activeSpeakerID = _selectedSpeakerID;
								_activateSound(ACTIVE_SOUND_ID);
								_transformation = TransformationType::TRANSLATION;

								// Filling writefields
								Vec3 position = _fe3d.modelEntity_getPosition(_activeSpeakerID);
								_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("x")->changeTextContent(to_string(static_cast<int>(position.x)));
								_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("y")->changeTextContent(to_string(static_cast<int>(position.y)));
								_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWritefield("z")->changeTextContent(to_string(static_cast<int>(position.z)));
							}
						}
					}
					else
					{
						// Don't reset if speaker is active
						if (entityID != _activeSpeakerID && _selectedSpeakerID == "")
						{
							_fe3d.modelEntity_setSize(entityID, DEFAULT_SPEAKER_SIZE);
							_fe3d.aabbEntity_setSize(entityID, DEFAULT_SPEAKER_AABB_SIZE);
						}
					}
				}
			}
			
			// Check if user made the active speaker inactive
			if (_selectedSpeakerID == "" && _activeSpeakerID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_activeSpeakerID = "";
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
				}
			}

			// Update speaker animations
			if (_selectedSpeakerID != _activeSpeakerID)
			{
				_updateSpeakerAnimation(_selectedSpeakerID, _selectedSpeakerSizeDirection);
			}
			_updateSpeakerAnimation(_activeSpeakerID, _activeSpeakerSizeDirection);

			// Update properties screen
			if (_activeSpeakerID != "")
			{
				_gui.getViewport("right")->getWindow("main")->setActiveScreen("soundPropertiesMenu");

				// Check if input received
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.modelEntity_delete(_activeSpeakerID);
						_fe3d.soundEntity_delete(ACTIVE_SOUND_ID);
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
						_activeSpeakerID = "";
						return;
					}
				}

				// Get current values
				Vec3 position = _fe3d.soundEntity_getPosition(ACTIVE_SOUND_ID);
				float maxVolume = _fe3d.soundEntity_getMaxVolume(ACTIVE_SOUND_ID);
				float maxDistance = _fe3d.soundEntity_getMaxDistance(ACTIVE_SOUND_ID);
				
				// Update value filling and changing
				_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, SOUND_DISTANCE_CHANGING_SPEED, 1.0f, 0.0f);
				_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -SOUND_DISTANCE_CHANGING_SPEED, 1.0f, 0.0f);
				_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
				_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
				_handleValueChanging("soundPropertiesMenu", "xPlus", "x", position.x, _editorSpeed / 100.0f);
				_handleValueChanging("soundPropertiesMenu", "xMinus", "x", position.x, -_editorSpeed / 100.0f);
				_handleValueChanging("soundPropertiesMenu", "yPlus", "y", position.y, _editorSpeed / 100.0f);
				_handleValueChanging("soundPropertiesMenu", "yMinus", "y", position.y, -_editorSpeed / 100.0f);
				_handleValueChanging("soundPropertiesMenu", "zPlus", "z", position.z, _editorSpeed / 100.0f);
				_handleValueChanging("soundPropertiesMenu", "zMinus", "z", position.z, -_editorSpeed / 100.0f);
				
				// Apply new values
				_fe3d.modelEntity_setPosition(_activeSpeakerID, position);
				_fe3d.soundEntity_setPosition(ACTIVE_SOUND_ID, position);
				_fe3d.soundEntity_setMaxVolume(ACTIVE_SOUND_ID, maxVolume);
				_fe3d.soundEntity_setMaxDistance(ACTIVE_SOUND_ID, maxDistance);
			}

			// Check if sound is still selected or active
			string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundName")->getEntityID();
			if (_selectedSpeakerID == "" && _activeSpeakerID == "")
			{
				_fe3d.textEntity_setVisible(textEntityID, false);
			}
			else
			{
				if (_selectedModelID == "" && _activeModelID == "" && _selectedBillboardID == "" && _activeBillboardID == ""
					&& _selectedLightBulbID == "" && _activeLightBulbID == "")
				{
					_fe3d.textEntity_setVisible(textEntityID, true);
				}
			}
		}
	}
}