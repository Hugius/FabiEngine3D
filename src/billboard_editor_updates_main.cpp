#include "billboard_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void BillboardEditor::update()
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
		_updateTexturingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateAnimationMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardCreating();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void BillboardEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "billboardEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("billboardCreate", "Create Billboard", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingBillboard = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedBillboardIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("billboardList", "Edit Billboard", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingBillboard = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedBillboardIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("billboardList", "Delete Billboard", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingBillboard = true;
			_isDeletingBillboard = true;
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveBillboardEntitiesToFile();
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

void BillboardEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "billboardEditorMenuChoice")
	{
		// Temporary values
		auto size = _fe3d.billboard_getSize(_currentBillboardID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_fe3d.billboard_setWireframed(_currentBillboardID, false);
			_fe3d.billboard_setVisible(_currentBillboardID, false);
			_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
			_currentBillboardID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuTexturing");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuAnimation");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuLighting");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMiscellaneous");
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("sizeX", size.x, {0.0f }))
		{
			size.x /= 100.0f;
			_fe3d.billboard_setSize(_currentBillboardID, size);
		}
		if(_gui.getGlobalScreen()->checkValueForm("sizeY", size.y, {0.0f }))
		{
			size.y /= 100.0f;
			_fe3d.billboard_setSize(_currentBillboardID, size);
		}

		// Update buttons hoverability
		screen->getButton("animation")->setHoverable(_fe3d.billboard_hasDiffuseMap(_currentBillboardID) && !_fe3d.billboard_isTextual(_currentBillboardID));
	}
}

void BillboardEditor::_updateBillboardCreating()
{
	if(_isCreatingBillboard)
	{
		string newBillboardID = "";

		// Check if user filled in a new ID
		if(_gui.getGlobalScreen()->checkValueForm("billboardCreate", newBillboardID, {_currentBillboardID }))
		{
			// @ sign not allowed
			if(newBillboardID.find('@') == string::npos)
			{
				// Spaces not allowed
				if(newBillboardID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newBillboardID = ("@" + newBillboardID);

					// If billboard not existing yet
					if(find(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), newBillboardID) == _loadedBillboardIDs.end())
					{
						// Create billboard
						_fe3d.billboard_create(newBillboardID);

						// Check if billboard creation went well
						if(_fe3d.billboard_isExisting(newBillboardID))
						{
							// Go to next screen
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");

							// Select billboard
							_currentBillboardID = newBillboardID;
							_loadedBillboardIDs.push_back(newBillboardID);

							// Miscellaneous
							_fe3d.text_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Billboard: " + newBillboardID.substr(1), 0.025f);
							_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
							_isCreatingBillboard = false;
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
	if(_isChoosingBillboard)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("billboardList");

		// Hide last billboard
		if(_hoveredBillboardID != "")
		{
			_fe3d.billboard_setVisible(_hoveredBillboardID, false);
		}

		// Check if a billboard ID is hovered
		if(!selectedButtonID.empty())
		{
			// Set new hovered model
			_hoveredBillboardID = ("@" + selectedButtonID);

			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select billboard
				_currentBillboardID = ("@" + selectedButtonID);
				_hoveredBillboardID = "";

				// Go to next screen
				if(!_isDeletingBillboard)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					_fe3d.text_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Billboard: " + _currentBillboardID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
				}

				// Miscellaneous
				_fe3d.billboard_setVisible(_currentBillboardID, true);
				_gui.getGlobalScreen()->deleteChoiceForm("billboardList");
				_isChoosingBillboard = false;
			}
			else
			{
				// Set new hovered billboard
				_hoveredBillboardID = ("@" + selectedButtonID);
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("billboardList")) // Cancelled choosing
		{
			_isChoosingBillboard = false;
			_isDeletingBillboard = false;
			_gui.getGlobalScreen()->deleteChoiceForm("billboardList");
		}
		else // Nothing hovered
		{
			_hoveredBillboardID = "";
		}

		// Show hovered billboard
		if(_hoveredBillboardID != "")
		{
			_fe3d.billboard_setVisible(_hoveredBillboardID, true);
		}
	}
}

void BillboardEditor::_updateBillboardDeleting()
{
	if(_isDeletingBillboard && _currentBillboardID != "")
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
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");

			// Delete billboard
			_fe3d.billboard_delete(_currentBillboardID);
			_loadedBillboardIDs.erase(remove(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), _currentBillboardID), _loadedBillboardIDs.end());
			_currentBillboardID = "";

			// Miscellaneous
			_isDeletingBillboard = false;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.billboard_setVisible(_currentBillboardID, false);
			_isDeletingBillboard = false;
			_currentBillboardID = "";
		}
	}
}