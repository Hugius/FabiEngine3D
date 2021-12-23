#include "billboard_editor.hpp"
#include "logger.hpp"

using std::max;

void BillboardEditor::_updateCamera()
{
	// Check if third person view is enabled
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		// Update distance scrolling
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		// Update lookat position
		auto cameraLookat = _fe3d.camera_getThirdPersonLookat();
		if(_fe3d.input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d.camera_setThirdPersonLookat(cameraLookat);

		// Hide cursor
		_fe3d.image_setVisible("@@cursor", false);

		// Update shadows
		const auto distance = _fe3d.camera_getThirdPersonDistance();
		_fe3d.gfx_setShadowEyePosition(fvec3(cameraLookat + fvec3(distance * 2.0f)));
		_fe3d.gfx_setShadowCenterPosition(cameraLookat);
		_fe3d.gfx_setShadowSize(distance * 4.0f);
		_fe3d.gfx_setShadowReach(distance * 8.0f);
	}

	// Check if allowed by GUI
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check third person view status
			if(_fe3d.camera_isThirdPersonViewEnabled())
			{
				_fe3d.camera_disableThirdPersonView();
			}
			else
			{
				_fe3d.camera_enableThirdPersonView(_fe3d.camera_getThirdPersonYaw(), _fe3d.camera_getThirdPersonPitch());
			}
		}
	}

	// Disable third person view if necessary
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		if(_gui.getOverlay()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void BillboardEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update reference model visibility
		if(_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d.model_isVisible("@@box"))
			{
				_fe3d.model_setVisible("@@box", false);
			}
			else
			{
				_fe3d.model_setVisible("@@box", true);
			}
		}

		// Update wireframe rendering
		if(!_currentBillboardID.empty())
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.billboard_isWireframed(_currentBillboardID))
				{
					_fe3d.billboard_setWireframed(_currentBillboardID, false);
				}
				else
				{
					_fe3d.billboard_setWireframed(_currentBillboardID, true);
				}
			}
		}

		// Update debug rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_H))
		{
			if(_fe3d.misc_isDebugRenderingEnabled())
			{
				_fe3d.misc_disableDebugRendering();
			}
			else
			{
				_fe3d.misc_enableDebugRendering();
			}
		}
	}
}

void BillboardEditor::_updateBillboardCreating()
{
	if(_isCreatingBillboard)
	{
		// Temporary values
		string newBillboardID;

		// Check if user filled in a new ID
		if(_gui.getOverlay()->checkValueForm("billboardCreate", newBillboardID, {_currentBillboardID}))
		{
			// Spaces not allowed
			if(newBillboardID.find(' ') != string::npos)
			{
				Logger::throwWarning("Billboard ID cannot contain any spaces!");
				return;
			}

			// @ sign not allowed
			if(newBillboardID.find('@') != string::npos)
			{
				Logger::throwWarning("Billboard ID cannot contain '@'!");
				return;
			}

			// Add @ sign to new ID
			newBillboardID = ("@" + newBillboardID);

			// Check if billboard already exists
			if(find(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), newBillboardID) != _loadedBillboardIDs.end())
			{
				Logger::throwWarning("Billboard with ID \"" + newBillboardID.substr(1) + "\" already exists!");
				return;
			}

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
				_fe3d.text_setContent(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), "Billboard: " + newBillboardID.substr(1), 0.025f);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), true);
				_isCreatingBillboard = false;
			}
		}
	}
}

void BillboardEditor::_updateBillboardChoosing()
{
	if(_isChoosingBillboard)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("billboardList");

		// Hide last billboard
		if(!_hoveredBillboardID.empty())
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
					_fe3d.text_setContent(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), "Billboard: " + _currentBillboardID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), true);
				}

				// Miscellaneous
				_fe3d.billboard_setVisible(_currentBillboardID, true);
				_gui.getOverlay()->deleteChoiceForm("billboardList");
				_isChoosingBillboard = false;
			}
			else
			{
				// Set new hovered billboard
				_hoveredBillboardID = ("@" + selectedButtonID);
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("billboardList")) // Cancelled choosing
		{
			_isChoosingBillboard = false;
			_isDeletingBillboard = false;
			_gui.getOverlay()->deleteChoiceForm("billboardList");
		}
		else // Nothing hovered
		{
			_hoveredBillboardID = "";
		}

		// Show hovered billboard
		if(!_hoveredBillboardID.empty())
		{
			_fe3d.billboard_setVisible(_hoveredBillboardID, true);
		}
	}
}

void BillboardEditor::_updateBillboardDeleting()
{
	if(_isDeletingBillboard && !_currentBillboardID.empty())
	{
		// Add answer form
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
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
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_fe3d.billboard_setVisible(_currentBillboardID, false);
			_isDeletingBillboard = false;
			_currentBillboardID = "";
		}
	}
}