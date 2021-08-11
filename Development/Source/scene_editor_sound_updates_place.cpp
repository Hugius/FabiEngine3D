#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateSoundPlacing()
{
	// Only if user is in placement mode
	if (!_currentPreviewSoundID.empty())
	{
		if (_fe3d.terrainEntity_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.modelEntity_getPosition(PREVIEW_SPEAKER_ID);

			// Update position change
			bool filledX = _gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, { });
			bool filledY = _gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, { });
			bool filledZ = _gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, { });

			// Update position
			_fe3d.modelEntity_setPosition(PREVIEW_SPEAKER_ID, _fe3d.misc_getRaycastPointOnTerrain());
			_fe3d.sound_setPosition(_currentPreviewSoundID, _fe3d.misc_getRaycastPointOnTerrain());

			// Check if model must be placed
			if (_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
			BEGIN1:
				const string newID = (_currentPreviewSoundID.substr(1) + "_" + to_string(Tools::getRandomInteger(0, INT_MAX)));

				// Check if sound already exists
				if (_fe3d.sound_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Stop sound playback
				if (_fe3d.sound_isStarted(_currentPreviewSoundID))
				{
					_fe3d.sound_stop(_currentPreviewSoundID, 0);
				}

				// Create model
				const string newModelID = ("@@speaker_" + newID);
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
				_fe3d.sound_create(newID, _fe3d.sound_getFilePath(_currentPreviewSoundID));
				_fe3d.sound_make3D(newID, newPosition, DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
				_fe3d.sound_play(newID, -1, 0);
				_loadedSoundIDs.insert(make_pair(newID, _currentPreviewSoundID));
			}

			// Check if placement mode must be disabled
			if (_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);
				auto textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID();
				_fe3d.textEntity_setVisible(textEntityID, false);
				_currentPreviewSoundID = "";
			}
		}
		else // Placing on terrain
		{
			// Check if allowed by GUI
			if (_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if allowed by mouse
				if (!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check if a terrain is loaded
					if (_fe3d.misc_isRaycastPointOnTerrainValid())
					{
						// Play preview soundcaster
						if (!_fe3d.sound_isStarted(_currentPreviewSoundID))
						{
							_fe3d.sound_play(_currentPreviewSoundID, -1, 0);
						}
						else if (_fe3d.sound_isPaused(_currentPreviewSoundID))
						{
							_fe3d.sound_resume(_currentPreviewSoundID);
						}

						// Show preview sound
						_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, true);

						// Update position
						_fe3d.modelEntity_setPosition(PREVIEW_SPEAKER_ID, _fe3d.misc_getRaycastPointOnTerrain());
						_fe3d.sound_setPosition(_currentPreviewSoundID, _fe3d.misc_getRaycastPointOnTerrain());
					}
					else
					{
						// Hide preview sound
						_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

						// Pause sound playback
						if (_fe3d.sound_isPlaying(_currentPreviewSoundID))
						{
							_fe3d.sound_pause(_currentPreviewSoundID);
						}
					}

					// Check if model must be placed
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid())
					{
						// Temporary values
						const auto newPosition = _fe3d.modelEntity_getPosition(PREVIEW_SPEAKER_ID);

						// Adding a number to make it unique
					BEGIN2:
						const string newID = (_currentPreviewSoundID.substr(1) + "_" + to_string(Tools::getRandomInteger(0, INT_MAX)));

						// Check if model already exists
						if (_fe3d.sound_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Stop sound playback
						if (_fe3d.sound_isStarted(_currentPreviewSoundID))
						{
							_fe3d.sound_stop(_currentPreviewSoundID, 0);
						}

						// Create model
						const string newModelID = ("@@speaker_" + newID);
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
						_fe3d.sound_create(newID, _fe3d.sound_getFilePath(_currentPreviewSoundID));
						_fe3d.sound_make3D(newID, newPosition, DEFAULT_SOUND_MAX_VOLUME, DEFAULT_SOUND_MAX_DISTANCE);
						_fe3d.sound_play(newID, -1, 0);
						_loadedSoundIDs.insert(make_pair(newID, _currentPreviewSoundID));
					}
					else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						// Hide preview speaker
						_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

						// Stop sound playback
						if (_fe3d.sound_isStarted(_currentPreviewSoundID))
						{
							_fe3d.sound_stop(_currentPreviewSoundID, 0);
						}

						// Stop placing
						_currentPreviewSoundID = "";

						// Hide soundcaster ID
						auto textEntityID = _gui.getGlobalScreen()->getTextfield("selectedSoundID")->getEntityID();
						_fe3d.textEntity_setVisible(textEntityID, false);
					}
				}
				else
				{
					// Hide preview sound
					_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

					// Pause sound playback
					if (_fe3d.sound_isPlaying(_currentPreviewSoundID))
					{
						_fe3d.sound_pause(_currentPreviewSoundID);
					}
				}
			}
			else
			{
				// Hide preview sound
				_fe3d.modelEntity_setVisible(PREVIEW_SPEAKER_ID, false);

				// Pause sound playback
				if (_fe3d.sound_isPlaying(_currentPreviewSoundID))
				{
					_fe3d.sound_pause(_currentPreviewSoundID);
				}
			}
		}
	}
}