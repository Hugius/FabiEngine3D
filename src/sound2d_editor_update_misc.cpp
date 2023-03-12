#include "sound2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Sound2dEditor::_updateMiscellaneous()
{
	if(_fe3d->sound2d_isExisting(_currentSound2dId))
	{
		if(_fe3d->sound2d_isStarted(_currentSound2dId, 0))
		{
			if(_fe3d->sound2d_isPaused(_currentSound2dId, 0))
			{
				_fe3d->quad3d_setDiffuseMap(STATUS_ID, STATUS_PAUSE_TEXTURE_PATH);
			}
			else
			{
				_fe3d->quad3d_setDiffuseMap(STATUS_ID, STATUS_START_TEXTURE_PATH);
			}
		}
		else
		{
			_fe3d->quad3d_setDiffuseMap(STATUS_ID, STATUS_STOP_TEXTURE_PATH);
		}
	}

	_fe3d->quad3d_setVisible(STATUS_ID, _fe3d->sound2d_isExisting(_currentSound2dId));
	_fe3d->quad3d_rotate(STATUS_ID, fvec3(0.0f, 0.5f, 0.0f));
}

void Sound2dEditor::_updateSound2dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createSound2d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto sound2dId = _gui->getOverlay()->getValueFormContent();

		if(sound2dId.empty())
		{
			Logger::throwWarning("Sound2D ID cannot be empty");

			return;
		}

		if(any_of(sound2dId.begin(), sound2dId.end(), isspace))
		{
			Logger::throwWarning("Sound2D ID cannot contain any spaces");

			return;
		}

		if(any_of(sound2dId.begin(), sound2dId.end(), isupper))
		{
			Logger::throwWarning("Sound2D ID cannot contain any capitals");

			return;
		}

		if(sound2dId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Sound2D ID cannot contain any specials");

			return;
		}

		sound2dId = ("@" + sound2dId);

		if(find(_loadedSound2dIds.begin(), _loadedSound2dIds.end(), sound2dId) != _loadedSound2dIds.end())
		{
			Logger::throwWarning("Sound2D already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\audio\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

			return;
		}

		const auto filePath = Tools::chooseWindowsExplorerFile((rootPath + targetDirectoryPath), "WAV");

		if(filePath.empty())
		{
			return;
		}

		if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

			return;
		}

		const auto finalFilePath = filePath.substr(rootPath.size());

		_fe3d->misc_clearAudioCache(finalFilePath);

		_fe3d->sound2d_create(sound2dId, finalFilePath);

		if(_fe3d->sound2d_isExisting(sound2dId))
		{
			_loadedSound2dIds.push_back(sound2dId);

			sort(_loadedSound2dIds.begin(), _loadedSound2dIds.end());

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound2dEditorMenuChoice");
			_gui->getOverlay()->getTextField(SOUND2D_TITLE_ID)->setTextContent("Sound2D: " + sound2dId.substr(1));
			_gui->getOverlay()->getTextField(SOUND2D_TITLE_ID)->setVisible(true);

			_currentSound2dId = sound2dId;
		}
	}
}

void Sound2dEditor::_updateSound2dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editSound2d") || (_gui->getOverlay()->getChoiceFormId() == "deleteSound2d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(_gui->getOverlay()->isChoiceFormConfirmed())
		{
			_currentSound2dId = ("@" + selectedOptionId);

			if(_gui->getOverlay()->getChoiceFormId() == "deleteSound2d")
			{
				_gui->getOverlay()->openAnswerForm("deleteSound2d", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
			}
			else
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound2dEditorMenuChoice");
				_gui->getOverlay()->getTextField(SOUND2D_TITLE_ID)->setTextContent("Sound2D: " + _currentSound2dId.substr(1));
				_gui->getOverlay()->getTextField(SOUND2D_TITLE_ID)->setVisible(true);
			}
		}
	}
}

void Sound2dEditor::_updateSound2dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteSound2d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->sound2d_delete(_currentSound2dId);

			_loadedSound2dIds.erase(remove(_loadedSound2dIds.begin(), _loadedSound2dIds.end(), _currentSound2dId), _loadedSound2dIds.end());

			_currentSound2dId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentSound2dId = "";
		}
	}
}