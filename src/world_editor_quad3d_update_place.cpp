#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateQuad3dPlacing()
{
	if(!_currentTemplateQuadId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->quad3d_getPosition(_currentTemplateQuadId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->quad3d_setPosition(_currentTemplateQuadId, fvec3(content, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->quad3d_setPosition(_currentTemplateQuadId, fvec3(newPosition.x, content, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));
				const auto newId = (_currentTemplateQuadId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_worldHelper->copyTemplateQuad(newId, _currentTemplateQuadId);
				_loadedQuadIds.insert({newId, _currentTemplateQuadId});

				_fe3d->quad3d_setPosition(newId, fvec3(newPosition.x, newPosition.y, content));

				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);

				_currentTemplateQuadId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);

				_currentTemplateQuadId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				return;
			}

			if(_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				return;
			}

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_MIDDLE))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_currentTemplateQuadId = "";
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + QUAD3D_TERRAIN_OFFSET);
			_fe3d->quad3d_setVisible(_currentTemplateQuadId, true);
			_fe3d->quad3d_setPosition(_currentTemplateQuadId, newPosition);

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
			{
				auto newId = (_currentTemplateQuadId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_worldHelper->copyTemplateQuad(newId, _currentTemplateQuadId);
				_loadedQuadIds.insert({newId, _currentTemplateQuadId});

				_fe3d->quad3d_setPosition(newId, newPosition);
			}
		}
	}
}