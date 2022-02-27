#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dPlacing()
{
	if(!_currentTemplateTextId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			auto newPosition = _fe3d->text3d_getPosition(_currentTemplateTextId);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->text3d_setPosition(_currentTemplateTextId, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				auto newId = (_currentTemplateTextId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_worldUtilities->copyTemplateText3d(newId, _currentTemplateTextId);
				_loadedTextIds.insert({newId, _currentTemplateTextId});

				_fe3d->text3d_setPosition(newId, newPosition);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
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

				_worldUtilities->copyTemplateText3d(newId, _currentTemplateTextId);
				_loadedTextIds.insert({newId, _currentTemplateTextId});

				_fe3d->text3d_setPosition(newId, newPosition);
			}
		}
	}
}