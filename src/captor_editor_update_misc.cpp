#include "captor_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void CaptorEditor::_updateCaptorCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createCaptor") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto captorId = _gui->getOverlay()->getValueFormContent();

		if(captorId.empty())
		{
			Logger::throwWarning("Captor ID cannot be empty");

			return;
		}

		if(any_of(captorId.begin(), captorId.end(), isspace))
		{
			Logger::throwWarning("Captor ID cannot contain any spaces");

			return;
		}

		if(any_of(captorId.begin(), captorId.end(), isupper))
		{
			Logger::throwWarning("Captor ID cannot contain any capitals");

			return;
		}

		if(captorId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Captor ID cannot contain any specials");

			return;
		}

		captorId = ("@" + captorId);

		if(find(_loadedCaptorIds.begin(), _loadedCaptorIds.end(), captorId) != _loadedCaptorIds.end())
		{
			Logger::throwWarning("Captor already exists");

			return;
		}

		_fe3d->captor_create(captorId);

		_loadedCaptorIds.push_back(captorId);

		sort(_loadedCaptorIds.begin(), _loadedCaptorIds.end());

		_gui->getRightViewport()->getWindow("main")->setActiveScreen("captorEditorMenuChoice");
		_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setTextContent("Captor: " + captorId.substr(1));
		_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setVisible(true);

		_currentCaptorId = captorId;
	}
}

void CaptorEditor::_updateCaptorChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editCaptor") || (_gui->getOverlay()->getChoiceFormId() == "deleteCaptor"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentCaptorId = ("@" + selectedOptionId);

				if(_gui->getOverlay()->getChoiceFormId() == "deleteCaptor")
				{
					_gui->getOverlay()->openAnswerForm("deleteCaptor", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getRightViewport()->getWindow("main")->setActiveScreen("captorEditorMenuChoice");

					_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setTextContent("Captor: " + _currentCaptorId.substr(1));
					_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
}

void CaptorEditor::_updateCaptorDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteCaptor") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->captor_delete(_currentCaptorId);

			_loadedCaptorIds.erase(remove(_loadedCaptorIds.begin(), _loadedCaptorIds.end(), _currentCaptorId), _loadedCaptorIds.end());

			_currentCaptorId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentCaptorId = "";
		}
	}
}