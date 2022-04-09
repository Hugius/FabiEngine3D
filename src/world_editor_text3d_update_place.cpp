#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dPlacing()
{
	if(!_currentTemplateTextId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->text3d_getPosition(_currentTemplateTextId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->text3d_setPosition(_currentTemplateTextId, fvec3(content, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->text3d_setPosition(_currentTemplateTextId, fvec3(newPosition.x, content, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));
				const auto newId = (_currentTemplateTextId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_worldUtilities->copyTemplateText(newId, _currentTemplateTextId);
				_loadedTextIds.insert({newId, _currentTemplateTextId});

				_fe3d->text3d_setPosition(newId, fvec3(newPosition.x, newPosition.y, content));

				_fe3d->text3d_setVisible(_currentTemplateTextId, false);

				_currentTemplateTextId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->text3d_setVisible(_currentTemplateTextId, false);

				_currentTemplateTextId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->text3d_setVisible(_currentTemplateTextId, false);
				return;
			}

			if(!_fe3d->misc_isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->text3d_setVisible(_currentTemplateTextId, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->text3d_setVisible(_currentTemplateTextId, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->text3d_setVisible(_currentTemplateTextId, false);
				_currentTemplateTextId = "";
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + TEXT3D_TERRAIN_OFFSET);
			_fe3d->text3d_setVisible(_currentTemplateTextId, true);
			_fe3d->text3d_setPosition(_currentTemplateTextId, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				auto newId = (_currentTemplateTextId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_worldUtilities->copyTemplateText(newId, _currentTemplateTextId);
				_loadedTextIds.insert({newId, _currentTemplateTextId});

				_fe3d->text3d_setPosition(newId, newPosition);
			}
		}
	}
}