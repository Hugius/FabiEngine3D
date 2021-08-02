#include "audio_editor.hpp"
#include "logger.hpp"

void AudioEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
		_updateChoiceMenu();
		_updateAudioCreating();
		_updateAudioChoosing();
		_updateAudioDeleting();
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
				_gui.getGlobalScreen()->addAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("add")->isHovered()) // Add audio button
			{
				_gui.getGlobalScreen()->addValueForm("newAudioName", "New Audio Name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingAudio = true;
			}
			else if (screen->getButton("edit")->isHovered()) // Edit audio button
			{
				_isChoosingAudio = true;
				_isEditingAudio = true;
				auto IDs = getLoadedAudioIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("audioList", "Select Audio", Vec2(0.0f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered()) // Delete audio button
			{
				_isChoosingAudio = true;
				_isDeletingAudio = true;
				auto IDs = getLoadedAudioIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("audioList", "Select Audio", Vec2(0.0f, 0.1f), IDs);
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
		string newAudioName = "";

		// Check if user filled in a new name
		if (_gui.getGlobalScreen()->hasValueFormChanged("newAudioName", newAudioName, { _currentAudioID }))
		{
			// Check if name starts with @ sign
			if (newAudioName[0] != '@')
			{
				// Check if name contains spaces
				if (newAudioName.find(' ') == string::npos)
				{
					// Add @ sign to new name
					newAudioName = "@" + newAudioName;

					// Check if name already exists
					if (std::find(_loadedAudioIDs.begin(), _loadedAudioIDs.end(), newAudioName) == _loadedAudioIDs.end()) // If name not existing yet
					{
						// Go to editor
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuChoice");

						// Select audio
						_currentAudioID = newAudioName;
						_loadedAudioIDs.push_back(newAudioName);

						// Miscellaneous
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID(), "Audio: " +
							_currentAudioID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID(), true);
						_isCreatingAudio = false;
						_isEditingAudio = true;
					}
					else // Name already exists
					{
						Logger::throwWarning("Audio name \"" + newAudioName.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Audio name cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("New audio name cannot begin with '@'!");
			}
		}
	}
}

void AudioEditor::_updateAudioChoosing()
{
	if (_isChoosingAudio)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("audioList");

		// Check if a audio name is hovered
		if (selectedButtonID != "")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
			{
				// Select audio
				_currentAudioID = "@" + selectedButtonID;

				// Go to editor
				if (_isEditingAudio)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID(), "Audio: " +
						_currentAudioID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID(), true);
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
			_gui.getGlobalScreen()->addAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Check if form is answered
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");

			// Delete soundEntity
			if (_fe3d.soundEntity_isExisting(_currentAudioID))
			{
				_fe3d.soundEntity_delete(_currentAudioID);
			}

			// Miscellaneous
			_loadedAudioIDs.erase(std::remove(_loadedAudioIDs.begin(), _loadedAudioIDs.end(), _currentAudioID), _loadedAudioIDs.end());
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