#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateQuad3dPlacing()
{
	if(!_currentTemplateQuadID.empty())
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->quad3d_getPosition(_currentTemplateQuadID);

			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});

			_fe3d->quad3d_setPosition(_currentTemplateQuadID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				BEGIN1:;
				int randomSerial = Math::getRandomNumber(0, INT_MAX);
				const auto newID = (_currentTemplateQuadID.substr(1) + "_" + to_string(randomSerial));

				if(_fe3d->quad3d_isExisting(newID))
				{
					goto BEGIN1;
				}

				_copyTemplateQuad3d(newID, _currentTemplateQuadID, newPosition, false);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadID, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), false);
				_currentTemplateQuadID = "";
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
						_fe3d->quad3d_setVisible(_currentTemplateQuadID, true);

						_fe3d->quad3d_setPosition(_currentTemplateQuadID, (_fe3d->raycast_getPointOnTerrain() + QUAD3D_TERRAIN_OFFSET));
					}
					else
					{
						_fe3d->quad3d_setVisible(_currentTemplateQuadID, false);
					}

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->raycast_isPointOnTerrainValid())
					{
						const auto newPosition = _fe3d->quad3d_getPosition(_currentTemplateQuadID);

						BEGIN2:;
						const auto newID = (_currentTemplateQuadID.substr(1) + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						if(_fe3d->quad3d_isExisting(newID))
						{
							goto BEGIN2;
						}

						_copyTemplateQuad3d(newID, _currentTemplateQuadID, newPosition, false);
					}
					else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_fe3d->quad3d_setVisible(_currentTemplateQuadID, false);
						_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), false);
						_currentTemplateQuadID = "";
					}
				}
				else
				{
					_fe3d->quad3d_setVisible(_currentTemplateQuadID, false);
				}
			}
			else
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadID, false);
			}
		}
	}
}