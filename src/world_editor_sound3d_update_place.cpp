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
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->sound3d_setPosition(_currentTemplateSound3dId, fvec3(value, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(SPEAKER_ID, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->sound3d_setPosition(_currentTemplateSound3dId, fvec3(newPosition.x, value, newPosition.z));
				_fe3d->model_setBasePosition(SPEAKER_ID, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newId = (_currentTemplateSound3dId.substr(1) + "_" + to_string(_idCounter));
				const auto newModelId = ("@@speaker_" + newId);

				_idCounter++;

				_duplicator->copyTemplateSound3d(newId, _currentTemplateSound3dId);

				_loadedSound3dIds.push_back(newId);

				_fe3d->sound3d_setPosition(newId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->sound3d_setMaxVolume(newId, SOUND3D_MAX_VOLUME);
				_fe3d->sound3d_setMaxDistance(newId, SOUND3D_MAX_DISTANCE);
				_fe3d->sound3d_start(newId, -1);

				_loadedSound3dIds.push_back(newId);

				_fe3d->model_create(newModelId, SPEAKER_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->model_setBaseSize(newModelId, SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, SPEAKER_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				_fe3d->model_setVisible(SPEAKER_ID, false);

				_currentTemplateSound3dId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				_fe3d->model_setVisible(SPEAKER_ID, false);

				_currentTemplateSound3dId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				if(_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentTemplateSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				_currentTemplateSound3dId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SOUND3D_TERRAIN_OFFSET);

			if(!_fe3d->sound3d_isStarted(_currentTemplateSound3dId, 0))
			{
				_fe3d->sound3d_start(_currentTemplateSound3dId, -1);
			}

			_fe3d->sound3d_setPosition(_currentTemplateSound3dId, newPosition);
			_fe3d->model_setVisible(SPEAKER_ID, true);
			_fe3d->model_setBasePosition(SPEAKER_ID, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newId = (_currentTemplateSound3dId.substr(1) + "_" + to_string(_idCounter));
				const auto newModelId = ("@@speaker_" + newId);

				_idCounter++;

				_duplicator->copyTemplateSound3d(newId, _currentTemplateSound3dId);

				_fe3d->sound3d_setPosition(newId, newPosition);
				_fe3d->sound3d_setMaxVolume(newId, SOUND3D_MAX_VOLUME);
				_fe3d->sound3d_setMaxDistance(newId, SOUND3D_MAX_DISTANCE);
				_fe3d->sound3d_start(newId, -1);

				_loadedSound3dIds.push_back(newId);

				_fe3d->model_create(newModelId, SPEAKER_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseSize(newModelId, SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, SPEAKER_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}