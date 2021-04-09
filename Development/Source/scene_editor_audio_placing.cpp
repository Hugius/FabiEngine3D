#include "scene_editor.hpp"

void SceneEditor::_updateAudioPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewAudioName.empty())
		{
			// Check if mouse behavior isn't being invalid
			if ((_fe3d.misc_isCursorInsideViewport() && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && 
				!_gui.getGlobalScreen()->isFocused()) || _fe3d.terrainEntity_getSelectedID() == "")
			{
				// Default placement position
				Vec3 newPosition = Vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "" && _fe3d.misc_isRaycastPositionOnTerrainValid())
				{
					// Update preview audiocaster position
					newPosition = _fe3d.misc_getRaycastPositionOnTerrain() + Vec3(0.0f, 1.0f, 0.0f);

					// Play preview audiocaster
					if (!_fe3d.audioEntity_isPlaying(_currentPreviewAudioName))
					{
						_fe3d.audioEntity_play(_currentPreviewAudioName, -1, 50);
					}
					else if (_fe3d.audioEntity_isPaused(_currentPreviewAudioName))
					{
						_fe3d.audioEntity_resume(_currentPreviewAudioName);
					}

					// Show preview audiocaster
					_fe3d.audioEntity_setPosition(_currentPreviewAudioName, newPosition);
					_fe3d.audioEntity_setMaxDistance(_currentPreviewAudioName, DEFAULT_AUDIO_MAX_DISTANCE);
					_fe3d.modelEntity_show(PREVIEW_SPEAKER_ID);
					_fe3d.modelEntity_setPosition(PREVIEW_SPEAKER_ID, newPosition);
				}
				else
				{
					// Hide preview speaker
					_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

					// Pause audio playback
					if (_fe3d.audioEntity_isPlaying(_currentPreviewAudioName))
					{
						_fe3d.audioEntity_pause(_currentPreviewAudioName);
					}
				}

				// Placing audiocaster
				if ((_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPositionOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new audiocaster
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = _currentPreviewAudioName.substr(1) + "_" + to_string(randomSerial);

					// Check if ID not already exists
					if (_fe3d.audioEntity_isExisting(newID))
					{
						goto begin;
					}

					// Stop audio playback
					if (_fe3d.audioEntity_isPlaying(_currentPreviewAudioName))
					{
						_fe3d.audioEntity_stop(_currentPreviewAudioName);
					}

					// Add audio entity
					_fe3d.modelEntity_add("@speaker_" + newID, _fe3d.modelEntity_getMeshPath(PREVIEW_SPEAKER_ID), newPosition, Vec3(0.0f), DEFAULT_SPEAKER_SIZE);
					_fe3d.modelEntity_setShadowed("@speaker_" + newID, false);
					_fe3d.aabbEntity_bindToModelEntity("@speaker_" + newID, Vec3(0.0f), DEFAULT_SPEAKER_AABB_SIZE, true, true);
					_fe3d.audioEntity_add3D(newID, _fe3d.audioEntity_getFilePath(_currentPreviewAudioName), newPosition, 0.5f, DEFAULT_AUDIO_MAX_DISTANCE);
					_fe3d.audioEntity_play(newID, -1, 0.5f);
					_loadedAudioIDs.insert(make_pair(newID, _currentPreviewAudioName));

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						// Hide preview speaker
						_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

						// Stop audio playback
						if (_fe3d.audioEntity_isPlaying(_currentPreviewAudioName))
						{
							_fe3d.audioEntity_stop(_currentPreviewAudioName);
						}

						// Stop placing
						_currentPreviewAudioName = "";
					}
				}
				else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling audiocaster placement
				{
					// Hide preview speaker
					_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

					// Stop audio playback
					if (_fe3d.audioEntity_isPlaying(_currentPreviewAudioName))
					{
						_fe3d.audioEntity_stop(_currentPreviewAudioName);
					}

					// Stop placing
					_currentPreviewAudioName = "";

					// Hide audio name
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview speaker
				_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

				// Pause audio playback
				if (_fe3d.audioEntity_isPlaying(_currentPreviewAudioName))
				{
					_fe3d.audioEntity_pause(_currentPreviewAudioName);
				}
			}
		}
	}
}