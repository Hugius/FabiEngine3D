#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateQuad3dPlacing()
{
	if(!_currentTemplateQuad3dId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->quad3d_getPosition(_currentTemplateQuad3dId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->quad3d_setPosition(_currentTemplateQuad3dId, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->quad3d_setPosition(_currentTemplateQuad3dId, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newQuad3dId = (_currentTemplateQuad3dId.substr(1) + "_" + to_string(_quad3dIdCounter));

				_quad3dIdCounter++;

				_duplicator->copyTemplateQuad3d(newQuad3dId, _currentTemplateQuad3dId);

				_fe3d->quad3d_setPosition(newQuad3dId, fvec3(newPosition.x, newPosition.y, value));

				_loadedQuad3dIds.push_back(newQuad3dId);

				sort(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end());

				_fe3d->quad3d_setVisible(_currentTemplateQuad3dId, false);

				_currentTemplateQuad3dId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dId, false);

				_currentTemplateQuad3dId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dId, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dId, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dId, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dId, false);

				_currentTemplateQuad3dId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + QUAD3D_TERRAIN_OFFSET);

			_fe3d->quad3d_setVisible(_currentTemplateQuad3dId, true);
			_fe3d->quad3d_setPosition(_currentTemplateQuad3dId, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newQuad3dId = (_currentTemplateQuad3dId.substr(1) + "_" + to_string(_quad3dIdCounter));

				_quad3dIdCounter++;

				_duplicator->copyTemplateQuad3d(newQuad3dId, _currentTemplateQuad3dId);

				_fe3d->quad3d_setPosition(newQuad3dId, newPosition);

				_loadedQuad3dIds.push_back(newQuad3dId);

				sort(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end());
			}
		}
	}
}