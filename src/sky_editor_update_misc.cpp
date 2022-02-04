#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::_updateCamera()
{
	if(_fe3d->camera_isFirstPersonEnabled())
	{
		_fe3d->quad2d_setVisible("@@cursor", false);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
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
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
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
			if(any_of(newSkyId.begin(), newSkyId.end(), isspace))
			{
				Logger::throwWarning("Sky ID cannot contain any spaces");
				return;
			}

			if(!all_of(newSkyId.begin(), newSkyId.end(), isalnum))
			{
				Logger::throwWarning("Sky ID cannot contain any specials");
				return;
			}

			if(any_of(newSkyId.begin(), newSkyId.end(), isupper))
			{
				Logger::throwWarning("Sky ID cannot contain any capitals");
				return;
			}

			newSkyId = ("@" + newSkyId);

			if(find(_loadedSkyIds.begin(), _loadedSkyIds.end(), newSkyId) != _loadedSkyIds.end())
			{
				Logger::throwWarning("Sky already exists");
				return;
			}

			_fe3d->sky_create(newSkyId);

			if(_fe3d->sky_isExisting(newSkyId))
			{
				_fe3d->sky_select(newSkyId);

				_currentSkyId = newSkyId;
				_loadedSkyIds.push_back(newSkyId);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("skyId")->getEntityId(), "Sky: " + newSkyId.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("skyId")->getEntityId(), true);
				_isCreatingSky = false;
			}
		}
	}
}

void SkyEditor::_updateSkyChoosing()
{
	if(_isChoosingSky)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("skyList");

		if(!selectedButtonId.empty())
		{
			_fe3d->sky_select("@" + selectedButtonId);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentSkyId = _fe3d->sky_getSelectedId();

				if(!_isDeletingSky)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("skyId")->getEntityId(), "Sky: " + _currentSkyId.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("skyId")->getEntityId(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("skyList");
				_isChoosingSky = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("skyList"))
		{
			_gui->getOverlay()->deleteChoiceForm("skyList");
			_isChoosingSky = false;
			_isDeletingSky = false;
		}
		else
		{
			_fe3d->sky_select("");
		}
	}
}

void SkyEditor::_updateSkyDeleting()
{
	if(_isDeletingSky && !_currentSkyId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->sky_delete(_currentSkyId);

			_loadedSkyIds.erase(remove(_loadedSkyIds.begin(), _loadedSkyIds.end(), _currentSkyId), _loadedSkyIds.end());
			_currentSkyId = "";
			_isDeletingSky = false;

		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->sky_select("");

			_currentSkyId = "";
			_isDeletingSky = false;
		}
	}
}