#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void SkyEditor::_updateCamera()
{
	if(_currentSkyId.empty())
	{
		_fe3d->camera_setFirstPersonEnabled(false);
	}
	else
	{
		if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->camera_setFirstPersonEnabled(!_fe3d->camera_isFirstPersonEnabled());
			}
		}
	}

	_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), !_fe3d->camera_isFirstPersonEnabled());
}

void SkyEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(!_currentSkyId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->sky_setWireframed(_currentSkyId, !_fe3d->sky_isWireframed(_currentSkyId));
			}
		}
	}
}

void SkyEditor::_updateSkyCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createSky") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto skyId = _gui->getOverlay()->getValueFormContent();

		if(skyId.empty())
		{
			Logger::throwWarning("Sky ID cannot be empty");

			return;
		}

		if(any_of(skyId.begin(), skyId.end(), isspace))
		{
			Logger::throwWarning("Sky ID cannot contain any spaces");

			return;
		}

		if(any_of(skyId.begin(), skyId.end(), isupper))
		{
			Logger::throwWarning("Sky ID cannot contain any capitals");

			return;
		}

		if(skyId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Sky ID cannot contain any specials");

			return;
		}

		skyId = ("@" + skyId);

		if(find(_loadedSkyIds.begin(), _loadedSkyIds.end(), skyId) != _loadedSkyIds.end())
		{
			Logger::throwWarning("Sky already exists");

			return;
		}

		_fe3d->sky_create(skyId);
		_fe3d->sky_select(skyId);

		_loadedSkyIds.push_back(skyId);

		sort(_loadedSkyIds.begin(), _loadedSkyIds.end());

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
		_gui->getOverlay()->getTextField(SKY_TITLE_ID)->setTextContent("Sky: " + skyId.substr(1));
		_gui->getOverlay()->getTextField(SKY_TITLE_ID)->setVisible(true);

		_currentSkyId = skyId;
	}
}

void SkyEditor::_updateSkyChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editSky") || (_gui->getOverlay()->getChoiceFormId() == "deleteSky"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(_isSkyHovered)
			{
				_fe3d->sky_select("");

				_isSkyHovered = false;
			}
		}
		else
		{
			if(!_isSkyHovered)
			{
				_isSkyHovered = true;

				_fe3d->sky_select("@" + selectedOptionId);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentSkyId = _fe3d->sky_getSelectedId();
				_isSkyHovered = false;

				if(_gui->getOverlay()->getChoiceFormId() == "deleteSky")
				{
					_gui->getOverlay()->openAnswerForm("deleteSky", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

					_gui->getOverlay()->getTextField(SKY_TITLE_ID)->setTextContent("Sky: " + _currentSkyId.substr(1));
					_gui->getOverlay()->getTextField(SKY_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(_isSkyHovered)
		{
			_fe3d->sky_select("");

			_isSkyHovered = false;
		}
	}
}

void SkyEditor::_updateSkyDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteSky") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->sky_delete(_currentSkyId);

			_loadedSkyIds.erase(remove(_loadedSkyIds.begin(), _loadedSkyIds.end(), _currentSkyId), _loadedSkyIds.end());

			_currentSkyId = "";

		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->sky_select("");

			_currentSkyId = "";
		}
	}
}