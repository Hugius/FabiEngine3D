#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dPlacing()
{
	if(!_currentTemplateTextID.empty())
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->text3d_getPosition(_currentTemplateTextID);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->text3d_setPosition(_currentTemplateTextID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				auto newID = (_currentTemplateTextID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				while(_fe3d->text3d_isExisting(newID))
				{
					newID = (_currentTemplateTextID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				}

				_copyTemplateText3d(newID, _currentTemplateTextID, newPosition, false);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->text3d_setVisible(_currentTemplateTextID, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), false);
				_currentTemplateTextID = "";
			}
		}
		else
		{
			if(!_fe3d->misc_isCursorInsideViewport() || _gui->getOverlay()->isFocused())
			{
				_fe3d->text3d_setVisible(_currentTemplateTextID, false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->text3d_setVisible(_currentTemplateTextID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->text3d_setVisible(_currentTemplateTextID, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), false);
				_currentTemplateTextID = "";
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->text3d_setVisible(_currentTemplateTextID, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + TEXT3D_TERRAIN_OFFSET);
			_fe3d->text3d_setVisible(_currentTemplateTextID, true);
			_fe3d->text3d_setPosition(_currentTemplateTextID, newPosition);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				auto newID = (_currentTemplateTextID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				while(_fe3d->text3d_isExisting(newID))
				{
					newID = (_currentTemplateTextID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));
				}

				_copyTemplateText3d(newID, _currentTemplateTextID, newPosition, false);
			}
		}
	}
}