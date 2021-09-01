#include "billboard_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void BillboardEditor::update()
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
		_updateMeshMenu();
	}
	if (_isEditorLoaded)
	{
		_updateAppearanceMenu();
	}
	if (_isEditorLoaded)
	{
		_updateAnimationMenu();
	}
	if (_isEditorLoaded)
	{
		_updateTextMenu();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardCreating();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardDeleting();
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

void BillboardEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "billboardEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
			{
				_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("create")->isHovered()) // Add billboard button
			{
				_gui.getGlobalScreen()->createValueForm("billboardCreate", "Create Billboard", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingBillboard = true;
			}
			else if (screen->getButton("edit")->isHovered()) // Edit billboard button
			{
				_isChoosingBillboard = true;
				_isEditingBillboard = true;
				auto IDs = getLoadedBillboardIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("billboardList", "Edit Billboard", Vec2(-0.5f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered()) // Delete billboard button
			{
				_isChoosingBillboard = true;
				_isDeletingBillboard = true;
				auto IDs = getLoadedBillboardIDs();
				for (auto& ID : IDs)
				{
					ID = ID.substr(1);
				}
				_gui.getGlobalScreen()->createChoiceForm("billboardList", "Delete Billboard", Vec2(-0.5f, 0.1f), IDs);
			}
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveBillboardEntitiesToFile();
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

void BillboardEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "billboardEditorMenuChoice")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_fe3d.billboardEntity_setWireFramed(_currentBillboardID, false);
				_fe3d.billboardEntity_setVisible(_currentBillboardID, false);
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
				_currentBillboardID = "";
				_isEditingBillboard = false;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");
				return;
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMesh");
			}
			else if (screen->getButton("appearance")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuAppearance");
			}
			else if (screen->getButton("animation")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuAnimation");
			}
			else if (screen->getButton("text")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuText");
			}
		}

		// Update buttons hoverability
		screen->getButton("animation")->setHoverable(!_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID).empty());
		screen->getButton("text")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID).empty());
	}
}

void BillboardEditor::_updateBillboardCreating()
{
	if (_isCreatingBillboard)
	{
		string newBillboardID = "";

		// Check if user filled in a new ID
		if (_gui.getGlobalScreen()->checkValueForm("billboardCreate", newBillboardID, { _currentBillboardID }))
		{
			// @ sign not allowed
			if (newBillboardID.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newBillboardID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newBillboardID = ("@" + newBillboardID);

					// If billboard not existing yet
					if (find(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), newBillboardID) == _loadedBillboardIDs.end())
					{
						// Create billboard
						_fe3d.billboardEntity_create(newBillboardID);

						// Check if billboard creation went well
						if (_fe3d.billboardEntity_isExisting(newBillboardID))
						{
							// Go to editor
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");

							// Select billboard
							_currentBillboardID = newBillboardID;
							_loadedBillboardIDs.push_back(newBillboardID);

							// Miscellaneous
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Billboard: " + newBillboardID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
							_isCreatingBillboard = false;
							_isEditingBillboard = true;
						}
					}
					else
					{
						Logger::throwWarning("Billboard with ID \"" + newBillboardID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Billboard ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Billboard ID cannot contain '@'!");
			}
		}
	}
}

void BillboardEditor::_updateBillboardChoosing()
{
	if (_isChoosingBillboard)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("billboardList");

		// Hide last billboard
		if (_hoveredBillboardID != "")
		{
			_fe3d.billboardEntity_setVisible(_hoveredBillboardID, false);
		}

		// Check if a billboard ID is hovered
		if (!selectedButtonID.empty())
		{
			// Set new hovered model
			_hoveredBillboardID = ("@" + selectedButtonID);

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select billboard
				_currentBillboardID = ("@" + selectedButtonID);
				_hoveredBillboardID = "";

				// Go to editor
				if (_isEditingBillboard)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Billboard: " + _currentBillboardID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
				}

				// Miscellaneous
				_fe3d.billboardEntity_setVisible(_currentBillboardID, true);
				_gui.getGlobalScreen()->deleteChoiceForm("billboardList");
				_isChoosingBillboard = false;
			}
			else
			{
				// Set new hovered billboard
				_hoveredBillboardID = ("@" + selectedButtonID);
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("billboardList")) // Cancelled choosing
		{
			_isChoosingBillboard = false;
			_isEditingBillboard = false;
			_isDeletingBillboard = false;
			_gui.getGlobalScreen()->deleteChoiceForm("billboardList");
		}
		else // Nothing hovered
		{
			_hoveredBillboardID = "";
		}

		// Show hovered billboard
		if (_hoveredBillboardID != "")
		{
			_fe3d.billboardEntity_setVisible(_hoveredBillboardID, true);
		}
	}
}

void BillboardEditor::_updateBillboardDeleting()
{
	if (_isDeletingBillboard && _currentBillboardID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Update answer form
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");

			// Delete billboard
			_fe3d.billboardEntity_delete(_currentBillboardID);
			_loadedBillboardIDs.erase(remove(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), _currentBillboardID), _loadedBillboardIDs.end());
			_currentBillboardID = "";

			// Miscellaneous
			_isDeletingBillboard = false;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.billboardEntity_setVisible(_currentBillboardID, false);
			_isDeletingBillboard = false;
			_currentBillboardID = "";
		}
	}
}