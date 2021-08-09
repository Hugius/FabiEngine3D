#include "scene_editor.hpp"

#define SELECTED_SPEAKER_ID _selectedSpeakerID
#define SELECTED_SOUND_ID _selectedSpeakerID.substr(string("@speaker_").size())
#define ACTIVE_SPEAKER_ID _activeSpeakerID
#define ACTIVE_SOUND_ID _activeSpeakerID.substr(string("@speaker_").size())

void SceneEditor::_updateSoundEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected sound from last frame
	if (!_dontResetSelectedSpeaker)
	{
		SELECTED_SPEAKER_ID = "";
	}
	else
	{
		_dontResetSelectedSpeaker = false;
	}

	// User must not be in placement mode
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && !_isPlacingPointLight && _currentPreviewSoundID.empty())
	{
		// Check which entity is selected
		auto hoveredAabbID = _fe3d.collision_checkCursorInAny().first;

		// Check if user selected a speaker model
		for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
		{
			// Must be sound preview entity
			if (entityID.substr(0, string("@@speaker").size()) == "@@speaker")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if (hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
					!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Set new selected speaker
					SELECTED_SPEAKER_ID = entityID;
					_selectSound(SELECTED_SOUND_ID);

					// Change cursor
					_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

					// Check if user clicked speaker
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same speaker is clicked again
						if (SELECTED_SPEAKER_ID != ACTIVE_SPEAKER_ID)
						{
							ACTIVE_SPEAKER_ID = SELECTED_SPEAKER_ID;
							_activateSound(ACTIVE_SOUND_ID);
						}
					}
				}
				else
				{
					// Don't reset if speaker is active
					if (entityID != ACTIVE_SPEAKER_ID && SELECTED_SPEAKER_ID.empty())
					{
						_fe3d.modelEntity_setSize(entityID, DEFAULT_SPEAKER_SIZE);
						_fe3d.aabbEntity_setSize(entityID, DEFAULT_SPEAKER_AABB_SIZE);
					}
				}
			}
		}

		// Check if user made the active speaker inactive
		if (SELECTED_SPEAKER_ID.empty() && ACTIVE_SPEAKER_ID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				ACTIVE_SPEAKER_ID = "";
				rightWindow->setActiveScreen("sceneEditorControls");
			}
		}

		// Update speaker animations
		if (SELECTED_SPEAKER_ID != ACTIVE_SPEAKER_ID)
		{
			_updateSpeakerAnimation(SELECTED_SPEAKER_ID, _selectedSpeakerSizeDirection);
		}
		_updateSpeakerAnimation(ACTIVE_SPEAKER_ID, _activeSpeakerSizeDirection);

		// Update properties screen
		if (ACTIVE_SPEAKER_ID != "")
		{
			// Temporary values
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("soundPropertiesMenu");

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("delete")->isHovered()) // Delete button
				{
					_fe3d.modelEntity_delete(ACTIVE_SPEAKER_ID);
					_fe3d.soundEntity_delete(ACTIVE_SOUND_ID);
					rightWindow->setActiveScreen("sceneEditorControls");
					ACTIVE_SPEAKER_ID = "";
					return;
				}
			}

			// Get current values
			Vec3 position = _fe3d.soundEntity_getPosition(ACTIVE_SOUND_ID);
			float maxVolume = _fe3d.soundEntity_getMaxVolume(ACTIVE_SOUND_ID);
			float maxDistance = _fe3d.soundEntity_getMaxDistance(ACTIVE_SOUND_ID);

			// Update value filling and changing
			_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, (_editorSpeed / 100.0f), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));

			// Apply new values
			_fe3d.modelEntity_setPosition(ACTIVE_SPEAKER_ID, position);
			_fe3d.soundEntity_setPosition(ACTIVE_SOUND_ID, position);
			_fe3d.soundEntity_setMaxVolume(ACTIVE_SOUND_ID, maxVolume);
			_fe3d.soundEntity_setMaxDistance(ACTIVE_SOUND_ID, maxDistance);
		}

		// Check if sound is still selected or active
		string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundName")->getEntityID();
		if (SELECTED_SPEAKER_ID.empty() && ACTIVE_SPEAKER_ID.empty())
		{
			_fe3d.textEntity_setVisible(textEntityID, false);
		}
		else
		{
			if (_selectedModelID.empty() && _activeModelID.empty() && _selectedBillboardID.empty() && _activeBillboardID.empty()
				&& _selectedLampID.empty() && _activeLampID.empty())
			{
				_fe3d.textEntity_setVisible(textEntityID, true);
			}
		}
	}
}