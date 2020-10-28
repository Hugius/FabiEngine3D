#include "world_editor.hpp"

void WorldEditor::_updateSkyEditor()
{
	if (_currentWorldPart == WorldPart::SKY)
	{
		_updateSkyMenuMain();
		_updateSkyMenuChoice();
		_updateSkyMenuMesh();
		_updateSkyMenuOptions();
		_updateSkyCreation();
		_updateSkyChoosing();
		_updateSkyRemoval();
		_updateSkyCamera();
	}
}

void WorldEditor::_updateSkyCreation()
{
	if (_isLoaded)
	{
		if (_skyCreationEnabled)
		{
			string newSkyName;

			// Create new sky
			if (_gui.getGlobalScreen()->checkValueForm("newSkyName", newSkyName, {}))
			{
				// Starting with at-sign not allowed
				if (newSkyName[0] != '@')
				{
					newSkyName = "@" + newSkyName;

					// If sky name not existing yet
					if (std::find(_skyNames.begin(), _skyNames.end(), newSkyName) == _skyNames.end())
					{
						_currentSkyID = newSkyName;
						_skyNames.push_back(_currentSkyID);
						_fe3d.skyEntity_add(_currentSkyID);
						_fe3d.skyEntity_select(_currentSkyID);
						_leftWindow->setActiveScreen("skyEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(),
							"Sky: " + _currentSkyID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID());
						_skyCreationEnabled = false;
						_skyEditingEnabled = true;
					}
					else
					{
						_fe3d.logger_throwWarning("Sky name \"" + newSkyName.substr(1) + "\" already exists!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New sky name cannot begin with '@'");
				}
			}
		}
	}
}

void WorldEditor::_updateSkyChoosing()
{
	if (_isLoaded)
	{
		if (_skyChoosingEnabled)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("skyList");

			// Hide last sky
			if (_hoveredSkyID != "")
			{
				_fe3d.skyEntity_select("@@engineBackground");
			}

			// Check if a sky name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select sky
					_currentSkyID = "@" + selectedButtonID;
					_hoveredSkyID = "";

					// Only if going to editor
					if (_skyEditingEnabled)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

						// Show sky name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(),
							"Sky: " + _currentSkyID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID());

						// Show entity
						_fe3d.skyEntity_select(_currentSkyID);
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("skyList");
					_skyChoosingEnabled = false;
				}
				else
				{
					// Set new hovered sky
					_hoveredSkyID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList")) // Cancelled choosing
			{
				_skyChoosingEnabled = false;
				_skyEditingEnabled = false;
				_skyRemovalEnabled = false;
				_gui.getGlobalScreen()->removeChoiceForm("skyList");
			}
			else // Nothing hovered
			{
				_hoveredSkyID = "";
			}

			// Show hovered sky
			if (_hoveredSkyID != "")
			{
				_fe3d.skyEntity_select(_hoveredSkyID);
			}
		}
	}
}

void WorldEditor::_updateSkyRemoval()
{
	if (_isLoaded)
	{
		if (_skyRemovalEnabled && _currentSkyID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeSky", "Are you sure?", vec2(0.0f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeSky"))
			{
				// Delete entity
				_fe3d.skyEntity_delete(_currentSkyID);

				// Delete from name record
				_skyNames.erase(std::remove(_skyNames.begin(), _skyNames.end(), _currentSkyID), _skyNames.end());
				_skyRemovalEnabled = false;
				_currentSkyID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("removeSky"))
			{
				_skyRemovalEnabled = false;
				_currentSkyID = "";
			}
		}
	}
}

void WorldEditor::_updateSkyCamera()
{
	if (_isLoaded && _currentSkyID != "")
	{
		if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui.getGlobalScreen()->isFocused())
		{
			if (_fe3d.misc_isCursorInsideViewport())
			{
				_fe3d.gfx_enableMotionBlur(5.0f);
				_fe3d.camera_enableFirstPersonView();
				_fe3d.camera_disableLookat();
				_fe3d.guiEntity_hide("@@cursor");
			}
		}
		else
		{
			_fe3d.gfx_disableMotionBlur();
			_fe3d.camera_disableFirstPersonView();
			_fe3d.guiEntity_show("@@cursor");
		}
	}
}