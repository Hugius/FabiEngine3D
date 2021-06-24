#include "audio_editor.hpp"

void AudioEditor::update()
{
	_updateMainMenu();
	_updateAudioCreation();
	_updateAudioChoosing();
	_updateAudioEditing();
	_updateAudioRemoval();
	_updateMiscellaneous();
}

void AudioEditor::_updateMainMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "audioEditorMenuMain")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getGlobalScreen()->addAnswerForm("exitAudioEditor", "Save changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("addAudio")->isHovered()) // Add audio button
				{
					_gui.getGlobalScreen()->addValueForm("newAudioName", "New audio name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
					_isCreatingAudio = true;
				}
				else if (screen->getButton("editAudio")->isHovered()) // Edit audio button
				{
					_isChoosingAudio = true;
					_isEditingAudio = true;
					auto IDs = getLoadedAudioIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("audioList", "Select audio", Vec2(-0.4f, 0.1f), IDs);
				}
				else if (screen->getButton("deleteAudio")->isHovered()) // Delete audio button
				{
					_isChoosingAudio = true;
					_isRemovingAudio = true;
					auto IDs = getLoadedAudioIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("audioList", "Select audio", Vec2(-0.4f, 0.1f), IDs);
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitAudioEditor"))
			{
				saveAudioEntitiesToFile();
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("exitAudioEditor"))
			{
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
		}
	}
}

void AudioEditor::_updateAudioCreation()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingAudio)
		{
			string newAudioName = "";

			// Check if user filled in a new name
			if (_gui.getGlobalScreen()->checkValueForm("newAudioName", newAudioName, { _currentAudioID }))
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
							_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID());
							_isCreatingAudio = false;
							_isEditingAudio = true;
						}
						else // Name already exists
						{
							_fe3d.logger_throwWarning("Audio name \"" + newAudioName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						_fe3d.logger_throwWarning("New audio name cannot contain any spaces!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New audio name cannot begin with '@'!");
				}
			}
		}
	}
}

void AudioEditor::_updateAudioChoosing()
{
	if (_isEditorLoaded)
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
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAudioName")->getEntityID());
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("audioList");
					_isChoosingAudio = false;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("audioList")) // Cancelled choosing
			{
				_isChoosingAudio = false;
				_isEditingAudio = false;
				_isRemovingAudio = false;
				_gui.getGlobalScreen()->removeChoiceForm("audioList");
			}
		}
	}
}

void AudioEditor::_updateAudioRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isRemovingAudio && _currentAudioID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeAudio", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeAudio"))
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
				_gui.getGlobalScreen()->removeAnswerForm("removeAudio");
				_isRemovingAudio = false;
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("removeAudio"))
			{
				_isChoosingAudio = true;
				_currentAudioID = "";
			}
		}
	}
}