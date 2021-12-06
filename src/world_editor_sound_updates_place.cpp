#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSoundPlacing()
{
	// Only if user is in placement mode
	if(!_currentPreviewSoundID.empty())
	{
		if(_fe3d.terrain_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.sound3D_getPosition(_currentPreviewSoundID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.sound3D_setPosition(_currentPreviewSoundID, newPosition);

			// Check if sound must be placed
			if(_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
			BEGIN1:
				const string newID = (_currentPreviewSoundID.substr(1) + "_" + to_string(Math::getRandomInteger(0, INT_MAX)));

				// Check if sound already exists
				if(_fe3d.sound3D_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Create model
				const string newModelID = ("@@speaker_" + newID);
				_fe3d.model_create(newModelID, _fe3d.model_getMeshPath(PREVIEW_SPEAKER_ID));
				_fe3d.model_setBaseSize(newModelID, DEFAULT_SPEAKER_SIZE);
				_fe3d.model_setShadowed(newModelID, false);
				_fe3d.model_setReflected(newModelID, false);
				_fe3d.model_setBright(newModelID, true);

				// Create AABB
				_fe3d.aabb_create(newModelID);
				_fe3d.aabb_setParentEntityID(newModelID, newModelID);
				_fe3d.aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
				_fe3d.aabb_setLocalSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);
				_fe3d.aabb_setCollisionResponsive(newModelID, false);

				// Create sound
				_fe3d.sound3D_create(newID, _fe3d.sound3D_getAudioPath(_currentPreviewSoundID));
				_fe3d.sound3D_setPosition(newID, newPosition);
				_fe3d.sound3D_setMaxVolume(newID, DEFAULT_SOUND_MAX_VOLUME);
				_fe3d.sound3D_setMaxDistance(newID, DEFAULT_SOUND_MAX_DISTANCE);
				_fe3d.sound3D_play(newID, -1, 0, false);
				_loadedSoundIDs.insert(make_pair(newID, _currentPreviewSoundID));
			}

			// Check if placement mode must be disabled
			if(_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				// Hide preview speaker
				_fe3d.model_setVisible(PREVIEW_SPEAKER_ID, false);

				// Stop preview sound playback
				_fe3d.sound3D_stop(_currentPreviewSoundID, 0);

				// Miscellaneous
				_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
				_currentPreviewSoundID = "";
			}
		}
		else // Placing on terrain
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if allowed by mouse
				if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check if a terrain is loaded
					if(_fe3d.raycast_isPointOnTerrainValid())
					{
						// Play preview sound
						if(!_fe3d.sound3D_isStarted(_currentPreviewSoundID))
						{
							_fe3d.sound3D_play(_currentPreviewSoundID, -1, 0, false);
						}

						// Show preview speaker
						_fe3d.model_setVisible(PREVIEW_SPEAKER_ID, true);

						// Update position
						_fe3d.sound3D_setPosition(_currentPreviewSoundID, (_fe3d.raycast_getPointOnTerrain() + SOUND_TERRAIN_OFFSET));
					}
					else
					{
						// Hide preview speaker
						_fe3d.model_setVisible(PREVIEW_SPEAKER_ID, false);

						// Stop preview sound playback
						if(_fe3d.sound3D_isStarted(_currentPreviewSoundID))
						{
							_fe3d.sound3D_stop(_currentPreviewSoundID, 0);
						}
					}

					// Check if model must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						const auto newPosition = _fe3d.sound3D_getPosition(_currentPreviewSoundID);

						// Adding a number to make it unique
					BEGIN2:
						const string newID = (_currentPreviewSoundID.substr(1) + "_" + to_string(Math::getRandomInteger(0, INT_MAX)));

						// Check if model already exists
						if(_fe3d.sound3D_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Stop preview sound playback
						_fe3d.sound3D_stop(_currentPreviewSoundID, 0);

						// Create model
						const string newModelID = ("@@speaker_" + newID);
						_fe3d.model_create(newModelID, _fe3d.model_getMeshPath(PREVIEW_SPEAKER_ID));
						_fe3d.model_setBaseSize(newModelID, DEFAULT_SPEAKER_SIZE);
						_fe3d.model_setShadowed(newModelID, false);
						_fe3d.model_setReflected(newModelID, false);
						_fe3d.model_setBright(newModelID, true);

						// Create AABB
						_fe3d.aabb_create(newModelID);
						_fe3d.aabb_setParentEntityID(newModelID, newModelID);
						_fe3d.aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
						_fe3d.aabb_setLocalSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);
						_fe3d.aabb_setCollisionResponsive(newModelID, false);

						// Create sound
						_fe3d.sound3D_create(newID, _fe3d.sound3D_getAudioPath(_currentPreviewSoundID));
						_fe3d.sound3D_setPosition(newID, newPosition);
						_fe3d.sound3D_setMaxVolume(newID, DEFAULT_SOUND_MAX_VOLUME);
						_fe3d.sound3D_setMaxDistance(newID, DEFAULT_SOUND_MAX_DISTANCE);
						_fe3d.sound3D_play(newID, -1, 0, false);
						_loadedSoundIDs.insert(make_pair(newID, _currentPreviewSoundID));
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						// Hide preview speaker
						_fe3d.model_setVisible(PREVIEW_SPEAKER_ID, false);

						// Stop preview sound playback
						_fe3d.sound3D_stop(_currentPreviewSoundID, 0);

						// Miscellaneous
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
						_currentPreviewSoundID = "";
					}
				}
				else
				{
					// Hide preview speaker
					_fe3d.model_setVisible(PREVIEW_SPEAKER_ID, false);

					// Stop preview sound playback
					if(_fe3d.sound3D_isStarted(_currentPreviewSoundID))
					{
						_fe3d.sound3D_stop(_currentPreviewSoundID, 0);
					}
				}
			}
			else
			{
				// Hide preview speaker
				_fe3d.model_setVisible(PREVIEW_SPEAKER_ID, false);

				// Stop preview sound playback
				if(_fe3d.sound3D_isStarted(_currentPreviewSoundID))
				{
					_fe3d.sound3D_stop(_currentPreviewSoundID, 0);
				}
			}
		}

		// Update preview speaker position
		if(!_currentPreviewSoundID.empty())
		{
			auto soundPosition = _fe3d.sound3D_getPosition(_currentPreviewSoundID);
			soundPosition -= SPEAKER_OFFSET;
			_fe3d.model_setBasePosition(PREVIEW_SPEAKER_ID, soundPosition);
		}
	}

	// Update speaker positions
	for(const auto& entityID : _fe3d.model_getAllIDs())
	{
		if(entityID.substr(0, string("@@speaker").size()) == "@@speaker")
		{
			auto soundPosition = _fe3d.sound3D_getPosition(entityID.substr(string("@@speaker_").size()));
			soundPosition -= SPEAKER_OFFSET;
			_fe3d.model_setBasePosition(entityID, soundPosition);
		}
	}
}