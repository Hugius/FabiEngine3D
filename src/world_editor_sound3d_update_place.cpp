#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSoundPlacing()
{
	if(!_currentTemplateSoundId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->sound3d_getPosition(_currentTemplateSoundId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->sound3d_setPosition(_currentTemplateSoundId, fvec3(content, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, fvec3(content, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->sound3d_setPosition(_currentTemplateSoundId, fvec3(newPosition.x, content, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, fvec3(newPosition.x, content, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));
				const auto newId = (_currentTemplateSoundId.substr(1) + "_" + to_string(_idCounter));
				const auto newModelId = ("@@speaker_" + newId);

				_idCounter++;

				_loadedSoundIds.insert({newId, _currentTemplateSoundId});

				_worldUtilities->copyTemplateSound(newId, _currentTemplateSoundId);
				_loadedSoundIds.insert({newId, _currentTemplateSoundId});

				_fe3d->sound3d_setPosition(newId, fvec3(newPosition.x, newPosition.y, content));
				_fe3d->sound3d_setMaxVolume(newId, DEFAULT_SOUND_MAX_VOLUME);
				_fe3d->sound3d_setMaxDistance(newId, DEFAULT_SOUND_MAX_DISTANCE);
				_fe3d->sound3d_start(newId, -1);

				_fe3d->model_create(newModelId, _fe3d->model_getMeshPath(TEMPLATE_SPEAKER_ID));
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, content));
				_fe3d->model_setBaseSize(newModelId, DEFAULT_SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_SPEAKER_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				_fe3d->sound3d_stop(_currentTemplateSoundId, 0);

				_currentTemplateSoundId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				_fe3d->sound3d_stop(_currentTemplateSoundId, 0);

				_currentTemplateSoundId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				if(_fe3d->sound3d_isStarted(_currentTemplateSoundId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundId, 0);
				}
				return;
			}

			if(!_fe3d->misc_isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				if(_fe3d->sound3d_isStarted(_currentTemplateSoundId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundId, 0);
				}
				return;
			}

			if(_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				if(_fe3d->sound3d_isStarted(_currentTemplateSoundId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundId, 0);
				}
				return;
			}

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				if(_fe3d->sound3d_isStarted(_currentTemplateSoundId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSoundId, 0);
				}
				_currentTemplateSoundId = "";
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SOUND_TERRAIN_OFFSET);
			if(!_fe3d->sound3d_isStarted(_currentTemplateSoundId, 0))
			{
				_fe3d->sound3d_start(_currentTemplateSoundId, -1);
			}
			_fe3d->sound3d_setPosition(_currentTemplateSoundId, newPosition);
			_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, newPosition);

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
			{
				auto newId = (_currentTemplateSoundId.substr(1) + "_" + to_string(_idCounter));
				auto newModelId = ("@@speaker_" + newId);

				_idCounter++;

				_loadedSoundIds.insert({newId, _currentTemplateSoundId});

				_worldUtilities->copyTemplateSound(newId, _currentTemplateSoundId);
				_loadedSoundIds.insert({newId, _currentTemplateSoundId});

				_fe3d->sound3d_setPosition(newId, newPosition);
				_fe3d->sound3d_setMaxVolume(newId, DEFAULT_SOUND_MAX_VOLUME);
				_fe3d->sound3d_setMaxDistance(newId, DEFAULT_SOUND_MAX_DISTANCE);
				_fe3d->sound3d_start(newId, -1);

				_fe3d->model_create(newModelId, _fe3d->model_getMeshPath(TEMPLATE_SPEAKER_ID));
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseSize(newModelId, DEFAULT_SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_SPEAKER_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}