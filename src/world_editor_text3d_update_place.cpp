#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dPlacing()
{
	if(!_currentTemplateText3dId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->text3d_getPosition(_currentTemplateText3dId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->text3d_setPosition(_currentTemplateText3dId, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->text3d_setPosition(_currentTemplateText3dId, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newId = (_currentTemplateText3dId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_duplicator->copyTemplateText3d(newId, _currentTemplateText3dId);

				_fe3d->text3d_setPosition(newId, fvec3(newPosition.x, newPosition.y, value));

				_loadedText3dIds.push_back({newId, _currentTemplateText3dId});

				_fe3d->text3d_setVisible(_currentTemplateText3dId, false);

				_currentTemplateText3dId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->text3d_setVisible(_currentTemplateText3dId, false);

				_currentTemplateText3dId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->text3d_setVisible(_currentTemplateText3dId, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->text3d_setVisible(_currentTemplateText3dId, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->text3d_setVisible(_currentTemplateText3dId, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->text3d_setVisible(_currentTemplateText3dId, false);

				_currentTemplateText3dId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + TEXT3D_TERRAIN_OFFSET);

			_fe3d->text3d_setVisible(_currentTemplateText3dId, true);
			_fe3d->text3d_setPosition(_currentTemplateText3dId, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newId = (_currentTemplateText3dId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_duplicator->copyTemplateText3d(newId, _currentTemplateText3dId);

				_fe3d->text3d_setPosition(newId, newPosition);

				_loadedText3dIds.push_back({newId, _currentTemplateText3dId});
			}
		}
	}
}