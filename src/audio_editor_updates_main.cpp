#include "audio_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void AudioEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateAudioCreating();
	}
	if(_isEditorLoaded)
	{
		_updateAudioChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateAudioDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void AudioEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "audioEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("audioCreate", "Create Audio", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAudio = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedAudioIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("audioList", "Edit Audio", fvec2(0.0f, 0.1f), IDs);
			_isChoosingAudio = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedAudioIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("audioList", "Delete Audio", fvec2(0.0f, 0.1f), IDs);
			_isChoosingAudio = true;
			_isDeletingAudio = true;
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveAudioEntitiesToFile();
			unload();
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void AudioEditor::_updateAudioCreating()
{
	if(_isCreatingAudio)
	{
		string newAudioID = "";

		// Check if user filled in a new ID
		if(_gui.getGlobalScreen()->checkValueForm("audioCreate", newAudioID, {_currentAudioID}))
		{
			// Check if ID starts with @ sign
			if(newAudioID[0] != '@')
			{
				// Check if ID contains spaces
				if(newAudioID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newAudioID = ("@" + newAudioID);

					// Check if audio not already exists
					if(find(_loadedAudioIDs.begin(), _loadedAudioIDs.end(), newAudioID) == _loadedAudioIDs.end())
					{
						// Get the chosen file name
						const auto rootDirectoryPath = Tools::getRootDirectoryPath();
						const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\audio\\");

						// Validate target directory
						if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
						{
							Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
							_isCreatingAudio = false;
							return;
						}

						// Validate chosen file
						const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "WAV");
						if(filePath.empty())
						{
							_isCreatingAudio = false;
							return;
						}

						// Validate directory of file
						if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
						   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
						{
							Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
							_isCreatingAudio = false;
							return;
						}

						// Create audio
						const string finalFilePath = filePath.substr(rootDirectoryPath.size());
						_fe3d.misc_clearAudioCache(finalFilePath);
						_fe3d.sound2D_create(newAudioID, finalFilePath);

						// Check if audio creation went well
						if(_fe3d.sound2D_isExisting(newAudioID))
						{
							// Go to next screen
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuChoice");

							// Select audio
							_currentAudioID = newAudioID;
							_loadedAudioIDs.push_back(newAudioID);

							// Miscellaneous
							_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("audioID")->getEntityID(), "Audio: " + newAudioID.substr(1), 0.025f);
							_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("audioID")->getEntityID(), true);
							_isCreatingAudio = false;
						}
					}
					else
					{
						Logger::throwWarning("Audio with ID \"" + newAudioID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Audio ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Audio ID cannot begin with '@'!");
			}
		}
	}
}

void AudioEditor::_updateAudioChoosing()
{
	if(_isChoosingAudio)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("audioList");

		// Check if a audio ID is hovered
		if(!selectedButtonID.empty())
		{
			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select audio
				_currentAudioID = ("@" + selectedButtonID);

				// Go to next screen
				if(!_isDeletingAudio)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuChoice");
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("audioID")->getEntityID(), "Audio: " + selectedButtonID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("audioID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("audioList");
				_isChoosingAudio = false;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("audioList")) // Cancelled choosing
		{
			_isChoosingAudio = false;
			_isDeletingAudio = false;
			_gui.getGlobalScreen()->deleteChoiceForm("audioList");
		}
	}
}


void AudioEditor::_updateAudioDeleting()
{
	if(_isDeletingAudio && _currentAudioID != "")
	{
		// Add answer form
		if(!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");

			// Delete audio
			if(_fe3d.sound2D_isExisting(_currentAudioID))
			{
				_fe3d.sound2D_delete(_currentAudioID);
			}

			// Miscellaneous
			_loadedAudioIDs.erase(remove(_loadedAudioIDs.begin(), _loadedAudioIDs.end(), _currentAudioID), _loadedAudioIDs.end());
			_currentAudioID = "";
			_isDeletingAudio = false;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isChoosingAudio = true;
			_currentAudioID = "";
		}
	}
}