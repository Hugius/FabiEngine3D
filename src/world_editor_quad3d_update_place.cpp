#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateQuad3dPlacing()
{
	if(!_currentTemplateQuadId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			auto newPosition = _fe3d->quad3d_getPosition(_currentTemplateQuadId);
			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});
			_fe3d->quad3d_setPosition(_currentTemplateQuadId, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				auto newId = string(_currentTemplateQuadId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_copyTemplateQuad3d(newId, _currentTemplateQuadId, newPosition, false);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
				_currentTemplateQuadId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
				return;
			}

			if(!_fe3d->misc_isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
				return;
			}

			if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
				return;
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
			{
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
				_currentTemplateQuadId = "";
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + QUAD3D_TERRAIN_OFFSET);
			_fe3d->quad3d_setVisible(_currentTemplateQuadId, true);
			_fe3d->quad3d_setPosition(_currentTemplateQuadId, newPosition);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				auto newId = string(_currentTemplateQuadId.substr(1) + "_" + to_string(_idCounter));

				_idCounter++;

				_copyTemplateQuad3d(newId, _currentTemplateQuadId, newPosition, false);
			}
		}
	}
}