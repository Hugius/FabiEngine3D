#include "billboard_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void BillboardEditor::update()
{
	_updateBillboardManagement();
	_updateBillboardCreation();
	_updateBillboardChoosing();
	_updateBillboardEditing();
	_updateBillboardRemoval();
	_updateCamera();
	_updateMiscellaneous();
}

void BillboardEditor::_updateBillboardManagement()
{
	if (_isEditorLoaded)
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
					_gui.getGlobalScreen()->addAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("add")->isHovered()) // Add billboard button
				{
					_gui.getGlobalScreen()->addValueForm("billboardCreate", "New Billboard Name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
					_isCreatingBillboard = true;
				}
				else if (screen->getButton("edit")->isHovered()) // Edit billboard button
				{
					_isChoosingBillboard = true;
					_isEditingBillboard = true;
					auto IDs = getLoadedBillboardIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("billboardList", "Select Billboard", Vec2(-0.5f, 0.1f), IDs);
				}
				else if (screen->getButton("delete")->isHovered()) // Delete billboard button
				{
					_isChoosingBillboard = true;
					_isRemovingBillboard = true;
					auto IDs = getLoadedBillboardIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("billboardList", "Select Billboard", Vec2(-0.5f, 0.1f), IDs);
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
			{
				saveBillboardEntitiesToFile();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
		}
	}
}

void BillboardEditor::_updateBillboardCreation()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingBillboard)
		{
			string newBillboardName = "";

			// Check if user filled in a new name
			if (_gui.getGlobalScreen()->checkValueForm("billboardCreate", newBillboardName, { _currentBillboardID }))
			{
				// @ sign not allowed
				if (newBillboardName.find('@') == string::npos)
				{
					// Spaces not allowed
					if (newBillboardName.find(' ') == string::npos)
					{
						// Add @ sign to new name
						newBillboardName = "@" + newBillboardName;

						// Check if name already exists
						if (std::find(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), newBillboardName) == _loadedBillboardIDs.end()) // If name not existing yet
						{
							// Go to editor
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");

							// Select billboard
							_currentBillboardID = newBillboardName;
							_loadedBillboardIDs.push_back(newBillboardName);

							// Miscellaneous
							_fe3d.billboardEntity_add(newBillboardName, Vec3(1.0f), Vec3(0.0f), Vec3(0.0f), Vec2(1.0f), false, false);
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), "Billboard: " +
								_currentBillboardID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), true);
							_isCreatingBillboard = false;
							_isEditingBillboard = true;
						}
						else // Name already exists
						{
							Logger::throwWarning("Billboard name \"" + newBillboardName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						Logger::throwWarning("Billboard name cannot contain any spaces!");
					}
				}
				else
				{
					Logger::throwWarning("Billboard name cannot contain '@'!");
				}
			}
		}
	}
}

void BillboardEditor::_updateBillboardChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingBillboard)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("billboardList");

			// Hide last billboard
			if (_hoveredBillboardID != "")
			{
				_fe3d.billboardEntity_setVisible(_hoveredBillboardID, false);
			}

			// Check if a billboard name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select billboard
					_currentBillboardID = "@" + selectedButtonID;
					_hoveredBillboardID = "";

					// Go to editor
					if (_isEditingBillboard)
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), "Billboard: " +
							_currentBillboardID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), true);
					}

					// Miscellaneous
					_fe3d.billboardEntity_setVisible(_currentBillboardID, true);
					_gui.getGlobalScreen()->removeChoiceForm("billboardList");
					_isChoosingBillboard = false;
				}
				else
				{
					// Set new hovered billboard
					_hoveredBillboardID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("billboardList")) // Cancelled choosing
			{
				_isChoosingBillboard = false;
				_isEditingBillboard = false;
				_isRemovingBillboard = false;
				_gui.getGlobalScreen()->removeChoiceForm("billboardList");
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
}

void BillboardEditor::_updateBillboardRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isRemovingBillboard && _currentBillboardID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("delete", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
			{
				// Go to main screen
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");

				// Delete billboard
				_fe3d.billboardEntity_delete(_currentBillboardID);
				_loadedBillboardIDs.erase(std::remove(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), _currentBillboardID), _loadedBillboardIDs.end());
				_currentBillboardID = "";

				// Miscellaneous
				_isRemovingBillboard = false;
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
			{
				_fe3d.billboardEntity_setVisible(_currentBillboardID, false);
				_isRemovingBillboard = false;
				_currentBillboardID = "";
			}
		}
	}
}

void BillboardEditor::_updateCamera()
{
	if (_isEditorLoaded)
	{
		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update moving up
			if (_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				_cameraLookatPosition.y += LOOKAT_MOVEMENT_SPEED;
			}

			// Update moving down
			if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT))
			{
				_cameraLookatPosition.y -= LOOKAT_MOVEMENT_SPEED;
				_cameraLookatPosition.y = std::max(0.0f, _cameraLookatPosition.y);
			}
		}

		// Check if third person view is enabled
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			// Disable third person view
			_fe3d.camera_disableThirdPersonView();

			// Show cursor
			_fe3d.imageEntity_setVisible("@@cursor", true);

			// Disable shadows
			if (_fe3d.gfx_isShadowsEnabled())
			{
				_fe3d.gfx_disableShadows();
			}

			// Enable shadows
			const auto distance = _fe3d.camera_getThirdPersonDistance();
			_fe3d.gfx_enableShadows(Vec3(_cameraLookatPosition + Vec3(distance * 2.0f)),
				_cameraLookatPosition, distance * 4.0f, distance * 8.0f, 0.5f, false, false, 0);
		}

		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Check if RMB pressed
			if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				// Update lookat position
				_fe3d.camera_setThirdPersonLookat(_cameraLookatPosition);

				// Enable third person view
				_fe3d.camera_enableThirdPersonView(
					_fe3d.camera_getThirdPersonYaw(),
					_fe3d.camera_getThirdPersonPitch(),
					_fe3d.camera_getThirdPersonDistance());

				// Hide cursor
				_fe3d.imageEntity_setVisible("@@cursor", false);
			}
		}
	}
}