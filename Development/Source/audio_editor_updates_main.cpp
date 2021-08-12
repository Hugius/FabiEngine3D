#include "audio_editor.hpp"
#include "logger.hpp"

void AudioEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if (_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if (_isEditorLoaded)
	{
		_updateAudioCreating();
	}
	if (_isEditorLoaded)
	{
		_updateAudioChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateAudioDeleting();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void AudioEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "audioEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
			{
				_gui.getGlobalScreen()->createAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("create")->isHovered()) // Add audio button
			{
				_gui.getGlobalScreen()->createValueForm("audioCreate", "Create Audio", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingAudio = true;
			}
			else if (screen->getButton("edit")->isHovered()) // Edit audio button
			{
				_isChoosingAudio = true;
				_isEditingAudio = true;
				auto IDs = getLoadedAudioIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("audioList", "Edit Audio", Vec2(0.0f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered()) // Delete audio button
			{
				_isChoosingAudio = true;
				_isDeletingAudio = true;
				auto IDs = getLoadedAudioIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("audioList", "Delete Audio", Vec2(0.0f, 0.1f), IDs);
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
		{
			saveAudioEntitiesToFile();
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
		{
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
	}
}

void AudioEditor::_updateAudioCreating()
{
	if (_isCreatingAudio)
	{
		string newAudioID = "";

		// Check if user filled in a new ID
		if (_gui.getGlobalScreen()->checkValueForm("audioCreate", newAudioID, { _currentAudioID }))
		{
			// Check if ID starts with @ sign
			if (newAudioID[0] != '@')
			{
				// Check if ID contains spaces
				if (newAudioID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newAudioID = ("@" + newAudioID);

					// Check if audio not already exists
					if (find(_loadedAudioIDs.begin(), _loadedAudioIDs.end(), newAudioID) == _loadedAudioIDs.end())
					{
						// Get the chosen filename
						const string rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("game_assets\\audio\\");
						const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "WAV");

						// Check if user chose a filename
						if (filePath.empty())
						{
							_isCreatingAudio = false;
							return;
						}
						else
						{
							// Check if user did not switch directory
							if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
								filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
							{
								const string newFilePath = filePath.substr(rootDirectory.size());
								_fe3d.misc_clearAudioChunkCache(newFilePath);
								_fe3d.sound_create(newAudioID, newFilePath);
							}
							else
							{
								Logger::throwWarning("Invalid filepath, directory switching not allowed!");
								_isCreatingAudio = false;
								return;
							}
						}

						// Check if sound creation went well
						if (_fe3d.sound_isExisting(newAudioID))
						{
							// Go to editor
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuChoice");

							// Select audio
							_currentAudioID = newAudioID;
							_loadedAudioIDs.push_back(newAudioID);

							// Miscellaneous
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("audioID")->getEntityID(), "Audio: " + newAudioID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("audioID")->getEntityID(), true);
							_isCreatingAudio = false;
							_isEditingAudio = true;
						}
					}
					else // ID already exists
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
	if (_isChoosingAudio)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("audioList");

		// Check if a audio ID is hovered
		if (selectedButtonID != "")
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select audio
				_currentAudioID = ("@" + selectedButtonID);

				// Go to editor
				if (_isEditingAudio)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("audioID")->getEntityID(), "Audio: " + _currentAudioID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("audioID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("audioList");
				_isChoosingAudio = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("audioList")) // Cancelled choosing
		{
			_isChoosingAudio = false;
			_isEditingAudio = false;
			_isDeletingAudio = false;
			_gui.getGlobalScreen()->deleteChoiceForm("audioList");
		}
	}
}


void AudioEditor::_updateAudioDeleting()
{
	if (_isDeletingAudio && _currentAudioID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Check if form is answered
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");

			// Delete sound
			if (_fe3d.sound_isExisting(_currentAudioID))
			{
				_fe3d.sound_delete(_currentAudioID);
			}

			// Miscellaneous
			_loadedAudioIDs.erase(remove(_loadedAudioIDs.begin(), _loadedAudioIDs.end(), _currentAudioID), _loadedAudioIDs.end());
			_currentAudioID = "";
			_isDeletingAudio = false;
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isChoosingAudio = true;
			_currentAudioID = "";
		}
	}
}