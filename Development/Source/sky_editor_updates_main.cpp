#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::update()
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
		_updateTexturingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if (_isEditorLoaded)
	{
		_updateSkyCreating();
	}
	if (_isEditorLoaded)
	{
		_updateSkyChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateSkyDeleting();
	}
	if (_isEditorLoaded)
	{
		_updateCamera();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void SkyEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "skyEditorMenuMain")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", Vec2(0.0f, 0.25f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("skyCreate", "Create Sky", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			_isCreatingSky = true;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedSkyIDs();
			for (auto& ID : IDs) { ID = ID.substr(1); }
			_gui.getGlobalScreen()->createChoiceForm("skyList", "Edit Sky", Vec2(0.0f, 0.1f), IDs);
			_isChoosingSky = true;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedSkyIDs();
			for (auto& ID : IDs) { ID = ID.substr(1); }
			_gui.getGlobalScreen()->createChoiceForm("skyList", "Delete Sky", Vec2(0.0f, 0.1f), IDs);
			_isChoosingSky = true;
			_isDeletingSky = true;
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveSkyEntitiesToFile();
			unload();
			return;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void SkyEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "skyEditorMenuChoice")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMain");
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("skyID")->getEntityID(), false);
			_fe3d.skyEntity_setWireFramed(_currentSkyID, false);
			_fe3d.skyEntity_selectMainSky("@@engineBackground");
			_currentSkyID = "";
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuTexturing");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMiscellaneous");
		}

		// Update buttons hoverability
		screen->getButton("miscellaneous")->setHoverable(_fe3d.skyEntity_isExisting(_currentSkyID));
	}
}

void SkyEditor::_updateSkyCreating()
{
	if (_isCreatingSky)
	{
		string newSkyID;

		// Check if user filled in a new ID
		if (_gui.getGlobalScreen()->checkValueForm("skyCreate", newSkyID, {}))
		{
			// @ sign not allowed
			if (newSkyID.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newSkyID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newSkyID = ("@" + newSkyID);

					// If sky not existing yet
					if (find(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), newSkyID) == _loadedSkyIDs.end())
					{
						// Create sky
						_fe3d.skyEntity_create(newSkyID);

						// Check if sky creation went well
						if (_fe3d.skyEntity_isExisting(newSkyID))
						{
							// Go to next screen
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

							// Select sky
							_currentSkyID = newSkyID;
							_loadedSkyIDs.push_back(newSkyID);
							_fe3d.skyEntity_selectMainSky(newSkyID);
							
							// Miscellaneous
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("skyID")->getEntityID(), "Sky: " + newSkyID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("skyID")->getEntityID(), true);
							_isCreatingSky = false;
						}
					}
					else
					{
						Logger::throwWarning("Sky with ID \"" + newSkyID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Sky ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Sky ID cannot contain '@'!");
			}
		}
	}
}

void SkyEditor::_updateSkyChoosing()
{
	if (_isChoosingSky)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("skyList");

		// Hide last sky
		_fe3d.skyEntity_selectMainSky("@@engineBackground");

		// Check if a sky ID is hovered
		if (!selectedButtonID.empty())
		{
			// Show sky
			_fe3d.skyEntity_selectMainSky("@" + selectedButtonID);

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select sky
				_currentSkyID = ("@" + selectedButtonID);

				// Go to next screen
				if (!_isDeletingSky)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("skyID")->getEntityID(), "Sky: " + _currentSkyID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("skyID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("skyList");
				_isChoosingSky = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList")) // Cancelled choosing
		{
			_isChoosingSky = false;
			_isDeletingSky = false;
			_gui.getGlobalScreen()->deleteChoiceForm("skyList");
		}
	}
}

void SkyEditor::_updateSkyDeleting()
{
	if (_isDeletingSky && _currentSkyID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Update answer form
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Delete entity
			_fe3d.skyEntity_delete(_currentSkyID);

			// Delete from ID record
			_loadedSkyIDs.erase(remove(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), _currentSkyID), _loadedSkyIDs.end());
			_isDeletingSky = false;
			_currentSkyID = "";

			// Enable engine background
			_fe3d.skyEntity_selectMainSky("@@engineBackground");
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			// Enable engine background
			_fe3d.skyEntity_selectMainSky("@@engineBackground");

			// Miscellaneous
			_isDeletingSky = false;
			_currentSkyID = "";
		}
	}
}