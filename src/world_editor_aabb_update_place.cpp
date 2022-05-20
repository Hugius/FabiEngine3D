#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateAabbPlacing()
{
	if(!_currentTemplateAabbId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->aabb_getBasePosition(_currentTemplateAabbId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->aabb_setBasePosition(_currentTemplateAabbId, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->aabb_setBasePosition(_currentTemplateAabbId, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newId = (_currentTemplateAabbId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_duplicator->copyTemplateAabb(newId, _currentTemplateAabbId);

				_fe3d->aabb_setBasePosition(newId, fvec3(newPosition.x, newPosition.y, value));

				_loadedAabbIds.push_back(newId);

				_fe3d->aabb_setVisible(_currentTemplateAabbId, false);

				_currentTemplateAabbId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->aabb_setVisible(_currentTemplateAabbId, false);

				_currentTemplateAabbId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->aabb_setVisible(_currentTemplateAabbId, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->aabb_setVisible(_currentTemplateAabbId, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->aabb_setVisible(_currentTemplateAabbId, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->aabb_setVisible(_currentTemplateAabbId, false);

				_currentTemplateAabbId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + AABB_TERRAIN_OFFSET);

			_fe3d->aabb_setVisible(_currentTemplateAabbId, true);
			_fe3d->aabb_setBasePosition(_currentTemplateAabbId, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newId = (_currentTemplateAabbId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_duplicator->copyTemplateAabb(newId, _currentTemplateAabbId);

				_fe3d->aabb_setBasePosition(newId, newPosition);

				_loadedAabbIds.push_back(newId);
			}
		}
	}
}