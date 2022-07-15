#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dPlacing()
{
	if(!_currentEditorText3dId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->text3d_getPosition(_currentEditorText3dId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->text3d_setPosition(_currentEditorText3dId, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->text3d_setPosition(_currentEditorText3dId, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newText3dId = (_currentEditorText3dId.substr(1) + "_" + to_string(_text3dIdCounter));

				_text3dIdCounter++;

				_duplicator->copyEditorText3d(newText3dId, _currentEditorText3dId);

				_fe3d->text3d_setPosition(newText3dId, fvec3(newPosition.x, newPosition.y, value));

				_loadedText3dIds.push_back(newText3dId);

				sort(_loadedText3dIds.begin(), _loadedText3dIds.end());

				_fe3d->text3d_setVisible(_currentEditorText3dId, false);

				_currentEditorText3dId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->text3d_setVisible(_currentEditorText3dId, false);

				_currentEditorText3dId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->text3d_setVisible(_currentEditorText3dId, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->text3d_setVisible(_currentEditorText3dId, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->text3d_setVisible(_currentEditorText3dId, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->text3d_setVisible(_currentEditorText3dId, false);

				_currentEditorText3dId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + TEXT3D_TERRAIN_OFFSET);

			_fe3d->text3d_setVisible(_currentEditorText3dId, true);
			_fe3d->text3d_setPosition(_currentEditorText3dId, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newText3dId = (_currentEditorText3dId.substr(1) + "_" + to_string(_text3dIdCounter));

				_text3dIdCounter++;

				_duplicator->copyEditorText3d(newText3dId, _currentEditorText3dId);

				_fe3d->text3d_setPosition(newText3dId, newPosition);

				_loadedText3dIds.push_back(newText3dId);

				sort(_loadedText3dIds.begin(), _loadedText3dIds.end());
			}
		}
	}
}