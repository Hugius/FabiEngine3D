#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateBillboardPlacing()
{
	if(!_currentTemplateQuad3dID.empty())
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->quad3d_getPosition(_currentTemplateQuad3dID);

			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});

			_fe3d->quad3d_setPosition(_currentTemplateQuad3dID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				BEGIN1:;
				int randomSerial = Math::getRandomNumber(0, INT_MAX);
				const auto newID = (_currentTemplateQuad3dID.substr(1) + "_" + to_string(randomSerial));

				if(_fe3d->quad3d_isExisting(newID))
				{
					goto BEGIN1;
				}

				_copyTemplateBillboard(newID, _currentTemplateQuad3dID, newPosition, false);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), false);
				_currentTemplateQuad3dID = "";
			}
		}
		else
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					if(_fe3d->raycast_isPointOnTerrainValid())
					{
						_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, true);

						_fe3d->quad3d_setPosition(_currentTemplateQuad3dID, (_fe3d->raycast_getPointOnTerrain() + BILLBOARD_TERRAIN_OFFSET));
					}
					else
					{
						_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, false);
					}

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->raycast_isPointOnTerrainValid())
					{
						const auto newPosition = _fe3d->quad3d_getPosition(_currentTemplateQuad3dID);

						BEGIN2:;
						const auto newID = (_currentTemplateQuad3dID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						if(_fe3d->quad3d_isExisting(newID))
						{
							goto BEGIN2;
						}

						_copyTemplateBillboard(newID, _currentTemplateQuad3dID, newPosition, false);
					}
					else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, false);
						_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), false);
						_currentTemplateQuad3dID = "";
					}
				}
				else
				{
					_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, false);
				}
			}
			else
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, false);
			}
		}
	}
}