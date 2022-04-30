#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSound3dPlacing()
{
	if(!_currentTemplateSound3dId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->sound3d_getPosition(_currentTemplateSound3dId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->sound3d_setPosition(_currentTemplateSound3dId, fvec3(content, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, fvec3(content, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->sound3d_setPosition(_currentTemplateSound3dId, fvec3(newPosition.x, content, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, fvec3(newPosition.x, content, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));
				const auto newId = (_currentTemplateSound3dId.substr(1) + "_" + to_string(_idCounter));
				const auto newModelId = ("@@speaker_" + newId);

				_idCounter++;

				_loadedSound3dIds.insert({newId, _currentTemplateSound3dId});

				_worldHelper->copyTemplateSound2d(newId, _currentTemplateSound3dId);
				_loadedSound3dIds.insert({newId, _currentTemplateSound3dId});

				_fe3d->sound3d_setPosition(newId, fvec3(newPosition.x, newPosition.y, content));
				_fe3d->sound3d_setMaxVolume(newId, DEFAULT_SOUND3D_MAX_VOLUME);
				_fe3d->sound3d_setMaxDistance(newId, DEFAULT_SOUND3D_MAX_DISTANCE);
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
				_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);

				_currentTemplateSound3dId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);
				_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);

				_currentTemplateSound3dId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				_currentTemplateSound3dId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SOUND3D_TERRAIN_OFFSET);
			if(!_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
			{
				_fe3d->sound3d_start(_currentTemplateSound3dId, -1);
			}
			_fe3d->sound3d_setPosition(_currentTemplateSound3dId, newPosition);
			_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_SPEAKER_ID, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				auto newId = (_currentTemplateSound3dId.substr(1) + "_" + to_string(_idCounter));
				auto newModelId = ("@@speaker_" + newId);

				_idCounter++;

				_loadedSound3dIds.insert({newId, _currentTemplateSound3dId});

				_worldHelper->copyTemplateSound2d(newId, _currentTemplateSound3dId);
				_loadedSound3dIds.insert({newId, _currentTemplateSound3dId});

				_fe3d->sound3d_setPosition(newId, newPosition);
				_fe3d->sound3d_setMaxVolume(newId, DEFAULT_SOUND3D_MAX_VOLUME);
				_fe3d->sound3d_setMaxDistance(newId, DEFAULT_SOUND3D_MAX_DISTANCE);
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