#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::_updateCamera()
{
	if(_fe3d->camera_isFirstPersonEnabled())
	{
		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			_fe3d->camera_setFirstPersonEnabled(!_fe3d->camera_isFirstPersonEnabled());
		}
	}

	if(_fe3d->camera_isFirstPersonEnabled())
	{
		if(_gui->getOverlay()->isFocused())
		{
			_fe3d->camera_setFirstPersonEnabled(false);
		}
	}
}

void SkyEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(!_currentSkyId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				_fe3d->sky_setWireframed(_currentSkyId, !_fe3d->sky_isWireframed(_currentSkyId));
			}
		}
	}
}

void SkyEditor::_updateSkyCreating()
{
	if(_isCreatingSky)
	{
		string newSkyId;

		if(_gui->getOverlay()->checkValueForm("skyCreate", newSkyId, {}))
		{
			if(newSkyId.empty())
			{
				Logger::throwWarning("Sky ID cannot be empty");
				return;
			}

			if(any_of(newSkyId.begin(), newSkyId.end(), isspace))
			{
				Logger::throwWarning("Sky ID cannot contain any spaces");
				return;
			}

			if(any_of(newSkyId.begin(), newSkyId.end(), isupper))
			{
				Logger::throwWarning("Sky ID cannot contain any capitals");
				return;
			}

			newSkyId = ("@" + newSkyId);

			if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newSkyId) != _loadedEntityIds.end())
			{
				Logger::throwWarning("Sky already exists");
				return;
			}

			_currentSkyId = newSkyId;
			_loadedEntityIds.push_back(newSkyId);
			sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

			_fe3d->sky_create(newSkyId);
			_fe3d->sky_select(newSkyId);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			_gui->getOverlay()->getTextField("skyId")->setTextContent("Sky: " + newSkyId.substr(1));
			_gui->getOverlay()->getTextField("skyId")->setVisible(true);
			_isCreatingSky = false;
		}
	}
}

void SkyEditor::_updateSkyChoosing()
{
	if(_isChoosingSky)
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			_fe3d->sky_select("@" + selectedOptionId);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentSkyId = _fe3d->sky_getSelectedId();

				if(_isDeletingSky)
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

					_gui->getOverlay()->getTextField("skyId")->setTextContent("Sky: " + _currentSkyId.substr(1));
					_gui->getOverlay()->getTextField("skyId")->setVisible(true);
				}


				_isChoosingSky = false;
			}
		}
		//else if(_gui->getOverlay()->isChoiceFormCancelled())
		{

			_isChoosingSky = false;
			_isDeletingSky = false;
		}
		//else
		//{
		//	_fe3d->sky_select("");
		//}
	}
}

void SkyEditor::_updateSkyDeleting()
{
	if(_isDeletingSky && !_isChoosingSky)
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->sky_delete(_currentSkyId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentSkyId), _loadedEntityIds.end());
			_currentSkyId = "";
			_isDeletingSky = false;


		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->sky_select("");

			_currentSkyId = "";
			_isDeletingSky = false;


		}
	}
}