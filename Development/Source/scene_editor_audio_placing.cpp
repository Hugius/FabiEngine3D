#include "scene_editor.hpp"

void SceneEditor::_updateAudioPlacing()
{
	if (_isLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewAudiocasterName.empty())
		{
			// Check if mouse behavior isn't being invalid
			if (_fe3d.misc_isCursorInsideViewport() && 
				!_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && 
				!_gui.getGlobalScreen()->isFocused())
			{
				// Default placement position
				Vec3 newPosition = Vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "")
				{
					// Update preview audiocaster position
					newPosition = _fe3d.terrainEntity_getMousePoint() + Vec3(0.0f, 1.0f, 0.0f);

					// Show & play preview audiocaster
					if (_fe3d.audioEntity_isPaused(_currentPreviewAudiocasterName))
					{
						_fe3d.audioEntity_resume(_currentPreviewAudiocasterName);
					}
					else
					{
						_fe3d.audioEntity_play(_currentPreviewAudiocasterName, -1, 50, true);
					}
					_fe3d.audioEntity_setCasterPosition(_currentPreviewAudiocasterName, newPosition);
					_fe3d.audioEntity_setMaxDistance(_currentPreviewAudiocasterName, _defaultAudiocasterDistance);
					_fe3d.gameEntity_show(_previewSpeakerID);
					_fe3d.gameEntity_setPosition(_previewSpeakerID, newPosition);
				}

				// Placing audiocaster
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new audiocaster
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = _currentPreviewAudiocasterName + "@" + to_string(randomSerial);

					// Check if ID not already exists
					if (_fe3d.audioEntity_isExisting(newID))
					{
						goto begin;
					}

					// Add audio entity
					_fe3d.gameEntity_add("@speaker" + newID, _fe3d.gameEntity_getObjPath(_previewSpeakerID), newPosition, Vec3(0.0f), _defaultSpeakerSize);
					_fe3d.gameEntity_setColor("@speaker" + newID, Vec3(1.0f));
					_fe3d.gameEntity_setShadowed("@speaker" + newID, false);
					_fe3d.gameEntity_setDepthMapIncluded("@speaker" + newID, false);
					_fe3d.aabbEntity_bindToGameEntity("@speaker" + newID, Vec3(0.0f), _defaultSpeakerAabbSize, true);
					_fe3d.audioEntity_add3D(newID, _fe3d.audioEntity_getFilePath(_currentPreviewAudiocasterName), newPosition, _defaultAudiocasterDistance);
					_fe3d.audioEntity_play(newID, -1, 50);

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_currentPreviewAudiocasterName = "";
					}
				}
				else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling audiocaster placement
				{
					// Hide preview speaker
					_fe3d.gameEntity_hide(_previewSpeakerID);

					// Stop audio playback
					if (_fe3d.audioEntity_isPlaying(_currentPreviewAudiocasterName))
					{
						_fe3d.audioEntity_pause(_currentPreviewAudiocasterName);
					}

					// Stop placing
					_currentPreviewAudiocasterName = "";

					// Hide audio name
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedAudiocasterName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview speaker
				_fe3d.gameEntity_hide(_previewSpeakerID);

				// Stop audio playback
				if (_fe3d.audioEntity_isPlaying(_currentPreviewAudiocasterName))
				{
					_fe3d.audioEntity_pause(_currentPreviewAudiocasterName);
				}
			}
		}
	}
}