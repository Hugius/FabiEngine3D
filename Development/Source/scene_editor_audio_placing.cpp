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
				if (_fe3d.terrainEntity_getSelectedID() != "")
				{
					// Update preview audiocaster position
					newPosition = _fe3d.terrainEntity_getCursorPosition3D() + Vec3(0.0f, 1.0f, 0.0f);

					// Show & play preview audiocaster
					if (_fe3d.audioEntity_isPaused(_currentPreviewAudioName))
					{
						_fe3d.audioEntity_resume(_currentPreviewAudioName);
					}
					else
					{
						_fe3d.audioEntity_play(_currentPreviewAudioName, -1, 50, true);
					}
					_fe3d.audioEntity_setPosition(_currentPreviewAudioName, newPosition);
					_fe3d.audioEntity_setMaxDistance(_currentPreviewAudioName, _defaultAudioMaxDistance);
					_fe3d.gameEntity_show(_previewSpeakerID);
					_fe3d.gameEntity_setPosition(_previewSpeakerID, newPosition);
				}

				// Placing audiocaster
				if ((_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.terrainEntity_isValidMousePoint()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new audiocaster
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = to_string(randomSerial) + "@" + _currentPreviewAudioName.substr(1);

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
					_fe3d.gameEntity_add("@speaker_" + newID, _fe3d.gameEntity_getMeshPath(_previewSpeakerID), newPosition, Vec3(0.0f), _defaultSpeakerSize);
					_fe3d.gameEntity_setShadowed("@speaker_" + newID, false);
					_fe3d.aabbEntity_bindToGameEntity("@speaker_" + newID, Vec3(0.0f), _defaultSpeakerAabbSize, true);
					_fe3d.audioEntity_add3D(newID, _fe3d.audioEntity_getFilePath(_currentPreviewAudioName), newPosition, 0.5f, _defaultAudioMaxDistance);
					_fe3d.audioEntity_play(newID, -1, 0.5f);
					_loadedAudioIDs.push_back(newID);

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						// Hide preview speaker
						_fe3d.gameEntity_hide(_previewSpeakerID);

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
					_fe3d.gameEntity_hide(_previewSpeakerID);

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
				_fe3d.gameEntity_hide(_previewSpeakerID);

				// Pause audio playback
				if (_fe3d.audioEntity_isPlaying(_currentPreviewAudioName))
				{
					_fe3d.audioEntity_pause(_currentPreviewAudioName);
				}
			}
		}
	}
}