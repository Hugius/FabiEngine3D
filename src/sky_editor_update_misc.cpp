#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::_updateCamera()
{
	if(_fe3d->camera_isFirstPersonViewEnabled())
	{
		_fe3d->quad_setVisible("@@cursor", false);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->camera_isFirstPersonViewEnabled())
			{
				_fe3d->camera_disableFirstPersonView();
			}
			else
			{
				_fe3d->camera_enableFirstPersonView(_fe3d->camera_getFirstPersonYaw(), _fe3d->camera_getFirstPersonPitch());
			}
		}
	}

	if(_fe3d->camera_isFirstPersonViewEnabled())
	{
		if(_gui->getOverlay()->isFocused())
		{
			_fe3d->camera_disableFirstPersonView();
		}
	}
}

void SkyEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(!_currentSkyID.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d->sky_isWireframed(_currentSkyID))
				{
					_fe3d->sky_setWireframed(_currentSkyID, false);
				}
				else
				{
					_fe3d->sky_setWireframed(_currentSkyID, true);
				}
			}
		}
	}
}

void SkyEditor::_updateSkyCreating()
{
	if(_isCreatingSky)
	{
		string newSkyID;

		if(_gui->getOverlay()->checkValueForm("skyCreate", newSkyID, {}))
		{
			if(newSkyID.find(' ') != string::npos)
			{
				Logger::throwWarning("Sky ID cannot contain any spaces!");
				return;
			}

			if(newSkyID.find('@') != string::npos)
			{
				Logger::throwWarning("Sky ID cannot contain '@'!");
				return;
			}

			newSkyID = ("@" + newSkyID);

			if(find(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), newSkyID) != _loadedSkyIDs.end())
			{
				Logger::throwWarning("Sky with ID \"" + newSkyID.substr(1) + "\" already exists!");
				return;
			}

			_fe3d->sky_create(newSkyID);

			if(_fe3d->sky_isExisting(newSkyID))
			{
				_gui->getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

				_currentSkyID = newSkyID;
				_loadedSkyIDs.push_back(newSkyID);
				_fe3d->sky_selectMainSky(newSkyID);

				_fe3d->text_setContent(_gui->getOverlay()->getTextField("skyID")->getEntityID(), "Sky: " + newSkyID.substr(1), 0.025f);
				_fe3d->text_setVisible(_gui->getOverlay()->getTextField("skyID")->getEntityID(), true);
				_isCreatingSky = false;
			}
		}
	}
}

void SkyEditor::_updateSkyChoosing()
{
	if(_isChoosingSky)
	{
		_fe3d->sky_selectMainSky("");

		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("skyList");

		if(!selectedButtonID.empty())
		{
			_fe3d->sky_selectMainSky("@" + selectedButtonID);

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentSkyID = ("@" + selectedButtonID);

				if(!_isDeletingSky)
				{
					_gui->getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
					_fe3d->text_setContent(_gui->getOverlay()->getTextField("skyID")->getEntityID(), "Sky: " + _currentSkyID.substr(1), 0.025f);
					_fe3d->text_setVisible(_gui->getOverlay()->getTextField("skyID")->getEntityID(), true);
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
	}
}

void SkyEditor::_updateSkyDeleting()
{
	if(_isDeletingSky && !_currentSkyID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->sky_selectMainSky("");

			_fe3d->sky_delete(_currentSkyID);

			_loadedSkyIDs.erase(remove(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), _currentSkyID), _loadedSkyIDs.end());
			_currentSkyID = "";
			_isDeletingSky = false;

		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d->sky_selectMainSky("");

			_currentSkyID = "";
			_isDeletingSky = false;
		}
	}
}