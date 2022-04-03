#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void SoundEditor::_updateMiscellaneous()
{
	if(_fe3d->sound2d_isExisting(_currentSoundId))
	{
		if(_fe3d->sound2d_isStarted(_currentSoundId, 0))
		{
			if(_fe3d->sound2d_isPaused(_currentSoundId, 0))
			{
				_fe3d->quad3d_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\pause.tga");
			}
			else
			{
				_fe3d->quad3d_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\start.tga");
			}
		}
		else
		{
			_fe3d->quad3d_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\stop.tga");
		}
	}

	_fe3d->quad3d_setVisible("@@icon", _fe3d->sound2d_isExisting(_currentSoundId));
	_fe3d->quad3d_rotate("@@icon", fvec3(0.0f, 0.5f, 0.0f));
}

void SoundEditor::_updateSoundCreating()
{
	if(_isCreatingSound)
	{
		string newSoundId;

		//if(_gui->getOverlay()->checkValueForm("soundCreate", newSoundId, {_currentSoundId}))
		{
			if(newSoundId.empty())
			{
				Logger::throwWarning("Sound ID cannot be empty");
				return;
			}

			if(any_of(newSoundId.begin(), newSoundId.end(), isspace))
			{
				Logger::throwWarning("Sound ID cannot contain any spaces");
				return;
			}

			if(any_of(newSoundId.begin(), newSoundId.end(), isupper))
			{
				Logger::throwWarning("Sound ID cannot contain any capitals");
				return;
			}

			newSoundId = ("@" + newSoundId);

			if(find(_loadedSoundIds.begin(), _loadedSoundIds.end(), newSoundId) != _loadedSoundIds.end())
			{
				Logger::throwWarning("Sound already exists");
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
				_isCreatingSound = false;
				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "WAV");
			if(filePath.empty())
			{
				_isCreatingSound = false;
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
				_isCreatingSound = false;
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearAudioCache(finalFilePath);

			_fe3d->sound2d_create(newSoundId, finalFilePath);

			if(_fe3d->sound2d_isExisting(newSoundId))
			{
				_currentSoundId = newSoundId;
				_loadedSoundIds.push_back(newSoundId);
				sort(_loadedSoundIds.begin(), _loadedSoundIds.end());

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("soundEditorMenuChoice");
				_gui->getOverlay()->getTextField("soundId")->setTextContent("Sound: " + newSoundId.substr(1));
				_gui->getOverlay()->getTextField("soundId")->setVisible(true);
				_isCreatingSound = false;
			}
		}
	}
}

void SoundEditor::_updateSoundChoosing()
{
	if(_isChoosingSound)
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentSoundId = ("@" + selectedOptionId);

				if(_isDeletingSound)
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("soundEditorMenuChoice");

					_gui->getOverlay()->getTextField("soundId")->setTextContent("Sound: " + _currentSoundId.substr(1));
					_gui->getOverlay()->getTextField("soundId")->setVisible(true);
				}

				_gui->getOverlay()->closeChoiceForm();
				_isChoosingSound = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled())
		{
			_gui->getOverlay()->closeChoiceForm();
			_isChoosingSound = false;
			_isDeletingSound = false;
		}
	}
}

void SoundEditor::_updateSoundDeleting()
{
	if(_isDeletingSound && !_isChoosingSound)
	{
		if(_gui->getOverlay()->isAnswerFormAccepted())
		{
			_fe3d->sound2d_delete(_currentSoundId);

			_loadedSoundIds.erase(remove(_loadedSoundIds.begin(), _loadedSoundIds.end(), _currentSoundId), _loadedSoundIds.end());
			_currentSoundId = "";
			_isDeletingSound = false;

			_gui->getOverlay()->closeAnswerForm();
		}
		if(_gui->getOverlay()->isAnswerFormDenied())
		{
			_currentSoundId = "";
			_isDeletingSound = false;

			_gui->getOverlay()->closeAnswerForm();
		}
	}
}