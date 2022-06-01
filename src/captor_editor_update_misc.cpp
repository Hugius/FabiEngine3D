#include "captor_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void CaptorEditor::_updateCaptorCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createCaptor") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newCaptorId = _gui->getOverlay()->getValueFormContent();

		if(newCaptorId.empty())
		{
			Logger::throwWarning("Captor ID cannot be empty");

			return;
		}

		if(any_of(newCaptorId.begin(), newCaptorId.end(), isspace))
		{
			Logger::throwWarning("Captor ID cannot contain any spaces");

			return;
		}

		if(any_of(newCaptorId.begin(), newCaptorId.end(), isupper))
		{
			Logger::throwWarning("Captor ID cannot contain any capitals");

			return;
		}

		newCaptorId = ("@" + newCaptorId);

		if(find(_loadedCaptorIds.begin(), _loadedCaptorIds.end(), newCaptorId) != _loadedCaptorIds.end())
		{
			Logger::throwWarning("Captor already exists");

			return;
		}

		_fe3d->captor_create(newCaptorId);

		_loadedCaptorIds.push_back(newCaptorId);

		sort(_loadedCaptorIds.begin(), _loadedCaptorIds.end());

		_gui->getRightViewport()->getWindow("main")->setActiveScreen("captorEditorMenuChoice");
		_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setTextContent("Captor: " + newCaptorId.substr(1));
		_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setVisible(true);

		_currentCaptorId = newCaptorId;
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