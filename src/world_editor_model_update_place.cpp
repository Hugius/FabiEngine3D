#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updateModelPlacing()
{
	if(!_currentTemplateModelID.empty())
	{
		if(_fe3d->terrain_getSelectedID().empty())
		{
			auto newPosition = _fe3d->model_getBasePosition(_currentTemplateModelID);

			_gui->getOverlay()->checkValueForm("positionX", newPosition.x, {});
			_gui->getOverlay()->checkValueForm("positionY", newPosition.y, {});
			_gui->getOverlay()->checkValueForm("positionZ", newPosition.z, {});

			_fe3d->model_setBasePosition(_currentTemplateModelID, newPosition);

			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				const string rawID = _currentTemplateModelID.substr(1);

				BEGIN1:;
				const string newID = (rawID + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

				if(_fe3d->model_isExisting(newID))
				{
					goto BEGIN1;
				}

				_copyTemplateModel(newID, _currentTemplateModelID, newPosition, false);
			}

			if(_gui->getOverlay()->isValueFormConfirmed() || _gui->getOverlay()->isValueFormCancelled())
			{
				_fe3d->model_setVisible(_currentTemplateModelID, false);
				_fe3d->text_setVisible(_gui->getOverlay()->getTextField("modelID")->getEntityID(), false);
				_currentTemplateModelID = "";
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
						_fe3d->model_setVisible(_currentTemplateModelID, true);

						_fe3d->model_setBasePosition(_currentTemplateModelID, (_fe3d->raycast_getPointOnTerrain() + MODEL_TERRAIN_OFFSET));
					}
					else
					{
						_fe3d->model_setVisible(_currentTemplateModelID, false);
					}

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->raycast_isPointOnTerrainValid())
					{
						const string rawID = _currentTemplateModelID.substr(1);
						const auto newPosition = _fe3d->model_getBasePosition(_currentTemplateModelID);

						BEGIN2:;
						const string newID = (rawID + "_" + to_string(Math::getRandomNumber(0, INT_MAX)));

						if(_fe3d->model_isExisting(newID))
						{
							goto BEGIN2;
						}

						_copyTemplateModel(newID, _currentTemplateModelID, newPosition, false);
					}
					else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_fe3d->model_setVisible(_currentTemplateModelID, false);
						_fe3d->text_setVisible(_gui->getOverlay()->getTextField("modelID")->getEntityID(), false);
						_currentTemplateModelID = "";
					}
				}
				else
				{
					_fe3d->model_setVisible(_currentTemplateModelID, false);
				}
			}
			else
			{
				_fe3d->model_setVisible(_currentTemplateModelID, false);
			}
		}
	}
}