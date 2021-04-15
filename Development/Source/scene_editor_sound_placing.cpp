#include "scene_editor.hpp"

void SceneEditor::_updateSoundPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewSoundID.empty())
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
					// Update preview soundcaster position
					newPosition = _fe3d.misc_getRaycastPositionOnTerrain() + Vec3(0.0f, 1.0f, 0.0f);

					// Play preview soundcaster
					if (!_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_play(_currentPreviewSoundID, -1, 0);
					}
					else if (_fe3d.soundEntity_isPaused(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_resume(_currentPreviewSoundID);
					}

					// Show preview soundcaster
					_fe3d.soundEntity_setPosition(_currentPreviewSoundID, newPosition);
					_fe3d.soundEntity_setMaxDistance(_currentPreviewSoundID, DEFAULT_SOUND_MAX_DISTANCE);
					_fe3d.modelEntity_show(PREVIEW_SPEAKER_ID);
					_fe3d.modelEntity_setPosition(PREVIEW_SPEAKER_ID, newPosition);
				}
				else
				{
					// Hide preview speaker
					_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

					// Pause sound playback
					if (_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_pause(_currentPreviewSoundID);
					}
				}

				// Placing soundcaster
				if ((_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPositionOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new soundcaster
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = _currentPreviewSoundID.substr(1) + "_" + to_string(randomSerial);

					// Check if ID not already exists
					if (_fe3d.soundEntity_isExisting(newID))
					{
						goto begin;
					}

					// Stop sound playback
					if (_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_stop(_currentPreviewSoundID, 0);
					}

					// Add soundEntity
					_fe3d.modelEntity_add("@speaker_" + newID, _fe3d.modelEntity_getMeshPath(PREVIEW_SPEAKER_ID), newPosition, Vec3(0.0f), DEFAULT_SPEAKER_SIZE);
					_fe3d.modelEntity_setShadowed("@speaker_" + newID, false);
					_fe3d.aabbEntity_bindToModelEntity("@speaker_" + newID, Vec3(0.0f), DEFAULT_SPEAKER_AABB_SIZE, true, true);
					_fe3d.soundEntity_add(newID, _fe3d.soundEntity_getFilePath(_currentPreviewSoundID));
					_fe3d.soundEntity_make3D(newID, newPosition, DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
					_fe3d.soundEntity_play(newID, -1, 0);
					_loadedSoundIDs.insert(make_pair(newID, _currentPreviewSoundID));

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						// Hide preview speaker
						_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

						// Stop sound playback
						if (_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
						{
							_fe3d.soundEntity_stop(_currentPreviewSoundID, 0);
						}

						// Stop placing
						_currentPreviewSoundID = "";
					}
				}
				else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling soundcaster placement
				{
					// Hide preview speaker
					_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

					// Stop sound playback
					if (_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_stop(_currentPreviewSoundID, 0);
					}

					// Stop placing
					_currentPreviewSoundID = "";

					// Hide soundcaster name
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview speaker
				_fe3d.modelEntity_hide(PREVIEW_SPEAKER_ID);

				// Pause sound playback
				if (_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
				{
					_fe3d.soundEntity_pause(_currentPreviewSoundID);
				}
			}
		}
	}
}