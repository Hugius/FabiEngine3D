#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateBillboardPlacing()
{
	if(!_currentTemplateBillboardID.empty())
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->billboard_getPosition(_currentTemplateBillboardID);

			_gui.getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui.getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui.getOverlay()->checkValueForm("positionZ", newPosition.z, {});

			_fe3d->billboard_setPosition(_currentTemplateBillboardID, newPosition);

			if(_gui.getOverlay()->isValueFormConfirmed())
			{
				BEGIN1:;
				int randomSerial = Math::getRandomNumber(0, INT_MAX);
				const string newID = (_currentTemplateBillboardID.substr(1) + "_" + to_string(randomSerial));

				if(_fe3d->billboard_isExisting(newID))
				{
					goto BEGIN1;
				}

				_copyTemplateBillboard(newID, _currentTemplateBillboardID, newPosition, false);
			}

			if(_gui.getOverlay()->isValueFormConfirmed() || _gui.getOverlay()->isValueFormCancelled())
			{
				_fe3d->billboard_setVisible(_currentTemplateBillboardID, false);
				_fe3d->text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
				_currentTemplateBillboardID = "";
			}
		}
		else
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui.getOverlay()->isFocused())
			{
				if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					if(_fe3d->raycast_isPointOnTerrainValid())
					{
						_fe3d->billboard_setVisible(_currentTemplateBillboardID, true);

						_fe3d->billboard_setPosition(_currentTemplateBillboardID, (_fe3d->raycast_getPointOnTerrain() + BILLBOARD_TERRAIN_OFFSET));
					}
					else
					{
						_fe3d->billboard_setVisible(_currentTemplateBillboardID, false);
					}

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->raycast_isPointOnTerrainValid())
					{
						const auto newPosition = _fe3d->billboard_getPosition(_currentTemplateBillboardID);

						BEGIN2:;
						const string newID = (_currentTemplateBillboardID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						if(_fe3d->billboard_isExisting(newID))
						{
							goto BEGIN2;
						}

						_copyTemplateBillboard(newID, _currentTemplateBillboardID, newPosition, false);
					}
					else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_fe3d->billboard_setVisible(_currentTemplateBillboardID, false);
						_fe3d->text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
						_currentTemplateBillboardID = "";
					}
				}
				else
				{
					_fe3d->billboard_setVisible(_currentTemplateBillboardID, false);
				}
			}
			else
			{
				_fe3d->billboard_setVisible(_currentTemplateBillboardID, false);
			}
		}
	}
}