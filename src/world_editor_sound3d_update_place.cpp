#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSoundPlacing()
{
	if(!_currentTemplateSoundID.empty())
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->sound3d_getPosition(_currentTemplateSoundID);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->sound3d_setPosition(_currentTemplateSoundID, newPosition);
			_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				BEGIN1:;
				const auto newID = (_currentTemplateSoundID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				const string newModelID = ("@@speaker_" + newID);

				if(_fe3d->sound3d_isExisting(newID))
				{
					goto BEGIN1;
				}

				_fe3d->sound3d_create(newID, _fe3d->sound3d_getAudioPath(_currentTemplateSoundID));

				if(_fe3d->sound3d_isExisting(newID))
				{
					_loadedSoundIDs.insert(make_pair(newID, _currentTemplateSoundID));

					_fe3d->sound3d_setPosition(newID, newPosition);
					_fe3d->sound3d_setMaxVolume(newID, DEFAULT_SOUND_MAX_VOLUME);
					_fe3d->sound3d_setMaxDistance(newID, DEFAULT_SOUND_MAX_DISTANCE);
					_fe3d->sound3d_start(newID, -1, 0, false);

					_fe3d->model_create(newModelID, _fe3d->model_getMeshPath(TEMPLATE_SPEAKER_ID));
					_fe3d->model_setBasePosition(newModelID, newPosition);
					_fe3d->model_setBaseSize(newModelID, DEFAULT_SPEAKER_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, "", true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityID(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				_fe3d->sound3d_stop(_currentTemplateSoundID, 0);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityID(), false);
				_currentTemplateSoundID = "";
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideViewport() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				if(_fe3d->sound3d_isStarted(_currentTemplateSoundID))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundID, 0);
				}
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				if(_fe3d->sound3d_isStarted(_currentTemplateSoundID))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundID, 0);
				}
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				_fe3d->sound3d_stop(_currentTemplateSoundID, 0);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityID(), false);
				_currentTemplateSoundID = "";
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				if(_fe3d->sound3d_isStarted(_currentTemplateSoundID))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundID, 0);
				}
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SOUND_TERRAIN_OFFSET);
			if(!_fe3d->sound3d_isStarted(_currentTemplateSoundID))
			{
				_fe3d->sound3d_start(_currentTemplateSoundID, -1, 0, false);
			}
			_fe3d->sound3d_setPosition(_currentTemplateSoundID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				BEGIN2:;
				const auto newID = (_currentTemplateSoundID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				const string newModelID = ("@@speaker_" + newID);
				if(_fe3d->sound3d_isExisting(newID))
				{
					goto BEGIN2;
				}

				_fe3d->sound3d_create(newID, _fe3d->sound3d_getAudioPath(_currentTemplateSoundID));

				if(_fe3d->sound3d_isExisting(newID))
				{
					_loadedSoundIDs.insert(make_pair(newID, _currentTemplateSoundID));

					_fe3d->sound3d_setPosition(newID, newPosition);
					_fe3d->sound3d_setMaxVolume(newID, DEFAULT_SOUND_MAX_VOLUME);
					_fe3d->sound3d_setMaxDistance(newID, DEFAULT_SOUND_MAX_DISTANCE);
					_fe3d->sound3d_start(newID, -1, 0, false);

					_fe3d->model_create(newModelID, _fe3d->model_getMeshPath(TEMPLATE_SPEAKER_ID));
					_fe3d->model_setBasePosition(newModelID, newPosition);
					_fe3d->model_setBaseSize(newModelID, DEFAULT_SPEAKER_SIZE);
					_fe3d->model_setShadowed(newModelID, false);
					_fe3d->model_setReflected(newModelID, false);
					_fe3d->model_setBright(newModelID, "", true);

					_fe3d->aabb_create(newModelID, true);
					_fe3d->aabb_setParentEntityID(newModelID, newModelID);
					_fe3d->aabb_setParentEntityType(newModelID, AabbParentEntityType::MODEL);
					_fe3d->aabb_setLocalSize(newModelID, DEFAULT_SPEAKER_AABB_SIZE);
					_fe3d->aabb_setCollisionResponsive(newModelID, false);
				}
			}
		}
	}
}