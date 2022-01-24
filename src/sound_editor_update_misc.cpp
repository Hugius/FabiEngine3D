#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void SoundEditor::_updateMiscellaneous()
{
	bool isExisting = _fe3d->sound2d_isExisting(_currentSoundID);
	bool isPlaying = isExisting && _fe3d->sound2d_isPlaying(_currentSoundID);
	bool isPaused = isExisting && _fe3d->sound2d_isPaused(_currentSoundID);

	if(isPlaying)
	{
		_fe3d->quad3d_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\start.tga");
	}
	else if(isPaused)
	{
		_fe3d->quad3d_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\pause.tga");
	}
	else
	{
		_fe3d->quad3d_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\stop.tga");
	}
	_fe3d->quad3d_rotate("@@icon", fvec3(0.0f, 0.5f, 0.0f));
}

void SoundEditor::_updateSoundCreating()
{
	if(_isCreatingSound)
	{
		string newSoundID;

		if(_gui->getOverlay()->checkValueForm("soundCreate", newSoundID, {_currentSoundID}))
		{
			if(newSoundID.find(' ') != string::npos)
			{
				Logger::throwWarning("Sound id cannot contain any spaces!");
				return;
			}

			if(newSoundID.find('@') != string::npos)
			{
				Logger::throwWarning("Sound id cannot contain '@'!");
				return;
			}

			newSoundID = ("@" + newSoundID);

			if(find(_loadedSoundIDs.begin(), _loadedSoundIDs.end(), newSoundID) != _loadedSoundIDs.end())
			{
				Logger::throwWarning("Sound with id \"" + newSoundID.substr(1) + "\" already exists!");
				return;
			}

			if(_currentProjectId.empty())
			{
				Logger::throwError("SoundEditor::_updateSoundCreating");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectId + "\\assets\\audio\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				_isCreatingSound = false;
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "WAV");
			if(filePath.empty())
			{
				_isCreatingSound = false;
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				_isCreatingSound = false;
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearAudioCache(finalFilePath);
			_fe3d->sound2d_create(newSoundID, finalFilePath);

			if(_fe3d->sound2d_isExisting(newSoundID))
			{
				_currentSoundID = newSoundID;
				_loadedSoundIDs.push_back(newSoundID);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("soundEditorMenuChoice");
				_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("soundID")->getEntityId(), "Sound: " + newSoundID.substr(1), 0.025f);
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityId(), true);
				_isCreatingSound = false;
			}
		}
	}
}

void SoundEditor::_updateSoundChoosing()
{
	if(_isChoosingSound)
	{
		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("soundList");

		if(!selectedButtonID.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentSoundID = ("@" + selectedButtonID);

				if(!_isDeletingSound)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("soundEditorMenuChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("soundID")->getEntityId(), "Sound: " + selectedButtonID.substr(1), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityId(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("soundList");
				_isChoosingSound = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("soundList"))
		{
			_gui->getOverlay()->deleteChoiceForm("soundList");
			_isChoosingSound = false;
			_isDeletingSound = false;
		}
	}
}

void SoundEditor::_updateSoundDeleting()
{
	if(_isDeletingSound && !_currentSoundID.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->sound2d_delete(_currentSoundID);

			_loadedSoundIDs.erase(remove(_loadedSoundIDs.begin(), _loadedSoundIDs.end(), _currentSoundID), _loadedSoundIDs.end());
			_currentSoundID = "";
			_isDeletingSound = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentSoundID = "";
			_isDeletingSound = false;
		}
	}
}