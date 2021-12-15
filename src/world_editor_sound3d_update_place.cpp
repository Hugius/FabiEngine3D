#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSoundPlacing()
{
	// Only if user is in placement mode
	if(!_currentTemplateSoundID.empty())
	{
		if(_fe3d.terrain_getSelectedID().empty()) // Placing without terrain
		{
			// Retrieve current position
			auto newPosition = _fe3d.sound3d_getPosition(_currentTemplateSoundID);

			// Update value forms
			_gui.getGlobalScreen()->checkValueForm("positionX", newPosition.x, {});
			_gui.getGlobalScreen()->checkValueForm("positionY", newPosition.y, {});
			_gui.getGlobalScreen()->checkValueForm("positionZ", newPosition.z, {});

			// Update position
			_fe3d.sound3d_setPosition(_currentTemplateSoundID, newPosition);

			// Check if sound must be placed
			if(_gui.getGlobalScreen()->isValueFormConfirmed())
			{
				// Adding a number to make it unique
				BEGIN1:
				const string newID = (_currentTemplateSoundID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				// Check if sound already exists
				if(_fe3d.sound3d_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Create model
				const string newModelID = ("@@speaker_" + newID);
				_fe3d.model_create(newModelID, _fe3d.model_getMeshPath(TEMPLATE_SPEAKER_ID));
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
				_fe3d.sound3d_create(newID, _fe3d.sound3d_getAudioPath(_currentTemplateSoundID));
				_fe3d.sound3d_setPosition(newID, newPosition);
				_fe3d.sound3d_setMaxVolume(newID, DEFAULT_SOUND_MAX_VOLUME);
				_fe3d.sound3d_setMaxDistance(newID, DEFAULT_SOUND_MAX_DISTANCE);
				_fe3d.sound3d_play(newID, -1, 0, false);
				_loadedSoundIDs.insert(make_pair(newID, _currentTemplateSoundID));
			}

			// Check if placement mode must be disabled
			if(_gui.getGlobalScreen()->isValueFormConfirmed() || _gui.getGlobalScreen()->isValueFormCancelled())
			{
				// Hide template speaker
				_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, false);

				// Stop template sound playback
				_fe3d.sound3d_stop(_currentTemplateSoundID, 0);

				// Miscellaneous
				_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
				_currentTemplateSoundID = "";
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
						// Play template sound
						if(!_fe3d.sound3d_isStarted(_currentTemplateSoundID))
						{
							_fe3d.sound3d_play(_currentTemplateSoundID, -1, 0, false);
						}

						// Show template speaker
						_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, true);

						// Update position
						_fe3d.sound3d_setPosition(_currentTemplateSoundID, (_fe3d.raycast_getPointOnTerrain() + SOUND_TERRAIN_OFFSET));
					}
					else
					{
						// Hide template speaker
						_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, false);

						// Stop template sound playback
						if(_fe3d.sound3d_isStarted(_currentTemplateSoundID))
						{
							_fe3d.sound3d_stop(_currentTemplateSoundID, 0);
						}
					}

					// Check if model must be placed
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.raycast_isPointOnTerrainValid())
					{
						// Temporary values
						const auto newPosition = _fe3d.sound3d_getPosition(_currentTemplateSoundID);

						// Adding a number to make it unique
						BEGIN2:
						const string newID = (_currentTemplateSoundID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						// Check if model already exists
						if(_fe3d.sound3d_isExisting(newID))
						{
							goto BEGIN2;
						}

						// Stop template sound playback
						_fe3d.sound3d_stop(_currentTemplateSoundID, 0);

						// Create model
						const string newModelID = ("@@speaker_" + newID);
						_fe3d.model_create(newModelID, _fe3d.model_getMeshPath(TEMPLATE_SPEAKER_ID));
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
						_fe3d.sound3d_create(newID, _fe3d.sound3d_getAudioPath(_currentTemplateSoundID));
						_fe3d.sound3d_setPosition(newID, newPosition);
						_fe3d.sound3d_setMaxVolume(newID, DEFAULT_SOUND_MAX_VOLUME);
						_fe3d.sound3d_setMaxDistance(newID, DEFAULT_SOUND_MAX_DISTANCE);
						_fe3d.sound3d_play(newID, -1, 0, false);
						_loadedSoundIDs.insert(make_pair(newID, _currentTemplateSoundID));
					}
					else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
					{
						// Hide template speaker
						_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, false);

						// Stop template sound playback
						_fe3d.sound3d_stop(_currentTemplateSoundID, 0);

						// Miscellaneous
						_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
						_currentTemplateSoundID = "";
					}
				}
				else
				{
					// Hide template speaker
					_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, false);

					// Stop template sound playback
					if(_fe3d.sound3d_isStarted(_currentTemplateSoundID))
					{
						_fe3d.sound3d_stop(_currentTemplateSoundID, 0);
					}
				}
			}
			else
			{
				// Hide template speaker
				_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, false);

				// Stop template sound playback
				if(_fe3d.sound3d_isStarted(_currentTemplateSoundID))
				{
					_fe3d.sound3d_stop(_currentTemplateSoundID, 0);
				}
			}
		}

		// Update template speaker position
		if(!_currentTemplateSoundID.empty())
		{
			auto soundPosition = _fe3d.sound3d_getPosition(_currentTemplateSoundID);
			soundPosition -= SPEAKER_OFFSET;
			_fe3d.model_setBasePosition(TEMPLATE_SPEAKER_ID, soundPosition);
		}
	}

	// Update speaker positions
	for(const auto& entityID : _fe3d.model_getIDs())
	{
		if(entityID.substr(0, string("@@speaker").size()) == "@@speaker")
		{
			auto soundPosition = _fe3d.sound3d_getPosition(entityID.substr(string("@@speaker_").size()));
			soundPosition -= SPEAKER_OFFSET;
			_fe3d.model_setBasePosition(entityID, soundPosition);
		}
	}
}