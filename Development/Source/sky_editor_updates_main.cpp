#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
		_updateChoiceMenu();
		_updateMeshMenu();
		_updateOptionsMenu();
		_updateSkyCreating();
		_updateSkyChoosing();
		_updateSkyDeleting();
		_updateCamera();
		_updateMiscellaneous();
	}
}

void SkyEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "skyEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getGlobalScreen()->createAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("add")->isHovered())
			{
				_isCreatingSky = true;
				_gui.getGlobalScreen()->createValueForm("skyCreate", "Create Sky", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_isChoosingSky = true;
				_isEditingSky = true;
				auto IDs = getLoadedSkyIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("skyList", "Edit Sky", Vec2(0.0f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isChoosingSky = true;
				_isDeletingSky = true;
				auto IDs = getLoadedSkyIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("skyList", "Delete Sky", Vec2(0.0f, 0.1f), IDs);
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
		{
			saveSkyEntitiesToFile();
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

void SkyEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "skyEditorMenuChoice")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMain");
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedSkyID")->getEntityID(), false);
				_fe3d.skyEntity_setWireFramed(_currentSkyID, false);
				_fe3d.skyEntity_selectMainSky("@@engineBackground");
				_currentSkyID = "";
				_isEditingSky = false;
				return;
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMesh");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuOptions");
			}
		}

		// Options screen hoverability
		screen->getButton("options")->setHoverable(_fe3d.skyEntity_isExisting(_currentSkyID));
	}
}

void SkyEditor::_updateSkyCreating()
{
	if (_isCreatingSky)
	{
		string newSkyID;

		// Create new sky
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
						_currentSkyID = newSkyID;
						_loadedSkyIDs.push_back(_currentSkyID);
						_fe3d.skyEntity_create(_currentSkyID);
						_fe3d.skyEntity_selectMainSky(_currentSkyID);
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyID")->getEntityID(),
							"Sky: " + _currentSkyID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedSkyID")->getEntityID(), true);
						_isCreatingSky = false;
						_isEditingSky = true;
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

		// Check if a sky ID is hovered
		if (selectedButtonID != "")
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select sky
				_currentSkyID = "@" + selectedButtonID;

				// Go to editor
				if (_isEditingSky)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyID")->getEntityID(),
						"Sky: " + _currentSkyID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedSkyID")->getEntityID(), true);
				}

				// Show entity
				_fe3d.skyEntity_selectMainSky(_currentSkyID);

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("skyList");
				_isChoosingSky = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList")) // Cancelled choosing
		{
			_isChoosingSky = false;
			_isEditingSky = false;
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

		// Check if form is answered
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
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			// Enable engine background
			_fe3d.skyEntity_selectMainSky("@@engineBackground");

			// Miscellaneous
			_isDeletingSky = false;
			_currentSkyID = "";
		}
	}
}