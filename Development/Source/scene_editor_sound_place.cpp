#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateSoundPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewSoundID.empty())
		{
			// Check if mouse behavior isn't being invalid
			if ((_fe3d.misc_isCursorInsideViewport() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && 
				!_gui.getGlobalScreen()->isFocused()) || _fe3d.terrainEntity_getSelectedID() == "")
			{
				// Default placement position
				Vec3 newPosition = Vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "" && _fe3d.misc_isRaycastPointOnTerrainValid())
				{
					// Update preview soundcaster position
					newPosition = _fe3d.misc_getRaycastPointOnTerrain() + Vec3(0.0f, 1.0f, 0.0f);

					// Play preview soundcaster
					if (!_fe3d.soundEntity_isStarted(_currentPreviewSoundID))
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
					_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, true);
					_fe3d.modelEntity_setPosition(PREVIEW_SPEAKER_ID, newPosition);
				}
				else
				{
					// Hide preview speaker
					_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

					// Pause sound playback
					if (_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_pause(_currentPreviewSoundID);
					}
				}

				// Placing soundcaster
				if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new soundcaster
				BEGIN:
					int randomSerial = Tools::getRandomInteger(0, INT_MAX);
					string newID = _currentPreviewSoundID.substr(1) + "_" + to_string(randomSerial);

					// Check if ID not already exists
					if (_fe3d.soundEntity_isExisting(newID))
					{
						goto BEGIN;
					}

					// Stop sound playback
					if (_fe3d.soundEntity_isStarted(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_stop(_currentPreviewSoundID, 0);
					}

					// Create model
					const string newModelID = ("@speaker_" + newID);
					_fe3d.modelEntity_create(newModelID, _fe3d.modelEntity_getMeshPath(PREVIEW_SPEAKER_ID));
					_fe3d.modelEntity_setPosition(newModelID, newPosition);
					_fe3d.modelEntity_setSize(newModelID, DEFAULT_SPEAKER_SIZE);
					_fe3d.modelEntity_setShadowed(newModelID, false);
					_fe3d.modelEntity_setReflected(newModelID, false);
					_fe3d.modelEntity_setBright(newModelID, true);

					// Create AABB
					_fe3d.aabbEntity_create(newModelID);
					_fe3d.aabbEntity_bindToModelEntity(newModelID, newModelID);
					_fe3d.aabbEntity_setSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);

					// Create sound
					_fe3d.soundEntity_create(newID, _fe3d.soundEntity_getFilePath(_currentPreviewSoundID));
					_fe3d.soundEntity_make3D(newID, newPosition, DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
					_fe3d.soundEntity_play(newID, -1, 0);
					_loadedSoundIDs.insert(make_pair(newID, _currentPreviewSoundID));

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						// Hide preview speaker
						_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

						// Stop placing
						_currentPreviewSoundID = "";
					}
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling soundcaster placement
				{
					// Hide preview speaker
					_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

					// Stop sound playback
					if (_fe3d.soundEntity_isStarted(_currentPreviewSoundID))
					{
						_fe3d.soundEntity_stop(_currentPreviewSoundID, 0);
					}

					// Stop placing
					_currentPreviewSoundID = "";

					// Hide soundcaster name
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundName")->getEntityID();
					_fe3d.textEntity_setVisible(textEntityID, false);
				}
			}
			else
			{
				// Hide preview speaker
				_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

				// Pause sound playback
				if (_fe3d.soundEntity_isPlaying(_currentPreviewSoundID))
				{
					_fe3d.soundEntity_pause(_currentPreviewSoundID);
				}
			}
		}
	}
}