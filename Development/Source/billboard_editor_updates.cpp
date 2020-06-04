#include "billboard_editor.hpp"

void BillboardEditor::update()
{
	if (_isLoaded)
	{
		_updateBillboardManagement();
		_updateBillboardCreation();
		_updateBillboardChoosing();
		_updateBillboardEditing();
		_updateBillboardRemoval();
		_updateBillboardCamera();
	}
}

void BillboardEditor::_updateBillboardManagement()
{
	auto screen = _window->getScreen("billboardManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("addBillboard")->isHovered()) // Add billboard button
		{
			_gui->getGlobalScreen()->addValueForm("newBillboardName", "New billboard name", "", vec2(0.0f));
			_billboardCreationEnabled = true;
		}
		else if (screen->getButton("editBillboard")->isHovered()) // Edit billboard button
		{
			_billboardChoosingEnabled = true;
			_billboardEditingEnabled = true;
			_gui->getGlobalScreen()->addChoiceForm("billboardList", "Select billboard", vec2(0.0f), _billboardNames);
		}
		else if (screen->getButton("deleteBillboard")->isHovered()) // Delete billboard button
		{
			_billboardChoosingEnabled = true;
			_billboardRemovalEnabled = true;
			_gui->getGlobalScreen()->addChoiceForm("billboardList", "Select billboard", vec2(0.0f), _billboardNames);
		}
		else if (screen->getButton("back")->isHovered()) // Back button
		{
			_gui->getGlobalScreen()->addAnswerForm("exitBillboardEditor", "Save changes?", vec2(0.0f, 0.25f));
		}
	}

	// Check if user wants to save changes
	if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitBillboardEditor"))
	{
		save();
		_window->setActiveScreen("main");
		unload();
	}
	else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitBillboardEditor"))
	{
		_window->setActiveScreen("main");
		unload();
	}
}

void BillboardEditor::_updateBillboardCreation()
{
	if (_billboardCreationEnabled)
	{
		string newBillboardName = "";

		// Check if user filled in a new name
		if (_gui->getGlobalScreen()->checkValueForm("newBillboardName", newBillboardName, {_currentBillboardName}))
		{
			if (std::find(_billboardNames.begin(), _billboardNames.end(), newBillboardName) == _billboardNames.end()) // If name not existing yet
			{
				_billboardCreationEnabled = false;
				_billboardEditingEnabled = true;
				_currentBillboardName = newBillboardName;
				_billboardNames.push_back(newBillboardName);
				_fe3d.billBoardEntity_add(newBillboardName, vec3(1.0f), vec3(0.0f, _cameraHeight, 0.0f), vec3(0.0f), vec3(1.0f), false, false);
			}
			else // Name already exists
			{
				_fe3d.logger_throwWarning("Billboard name \"" + newBillboardName + "\" already exists!");
			}
		}
	}
}

void BillboardEditor::_updateBillboardChoosing()
{
	if (_billboardChoosingEnabled)
	{
		string clickedButtonID = _gui->getGlobalScreen()->getClickedChoiceFormButtonID("billboardList");

		if (clickedButtonID != "")
		{
			_currentBillboardName = clickedButtonID;
			_billboardChoosingEnabled = false;
		}
		else
		{
			if (_gui->getGlobalScreen()->isChoiceFormCancelled("billboardList"))
			{
				_billboardChoosingEnabled = false;
				_billboardEditingEnabled = false;
				_billboardRemovalEnabled = false;
				_gui->getGlobalScreen()->removeChoiceForm("billboardList");
			}
		}
	}
}

void BillboardEditor::_updateBillboardEditing()
{
	if (_billboardEditingEnabled && _currentBillboardName != "")
	{
		static bool firstTime = true;
		auto screen = _window->getScreen("billboardEditingMain");

		// First time initializations
		if (firstTime)
		{
			firstTime = false;
			_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("currentBillboardName")->getEntityID(), "Billboard: " + _currentBillboardName, 0.025f);
			_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("currentBillboardName")->getEntityID());
			_fe3d.billboardEntity_show(_currentBillboardName);
			_window->setActiveScreen("billboardEditingMain");
		}
		
		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("size")->isHovered())
			{

			}
			else if (screen->getButton("color")->isHovered())
			{

			}
			else if (screen->getButton("texture")->isHovered())
			{

			}
			else if (screen->getButton("animation")->isHovered())
			{

			}
			else if (screen->getButton("back")->isHovered())
			{
				_fe3d.billboardEntity_hide(_currentBillboardName);
				_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("currentBillboardName")->getEntityID());
				_currentBillboardName = "";
				_billboardEditingEnabled = false;
				firstTime = true;
				_window->setActiveScreen("billboardManagement");
			}
		}
	}
}

void BillboardEditor::_updateBillboardRemoval()
{
	if (_billboardRemovalEnabled && _currentBillboardName != "")
	{
		_gui->getGlobalScreen()->addAnswerForm("removeBillboard", "Are you sure?", vec2(0.0f));

		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("removeBillboard"))
		{
			_gui->getGlobalScreen()->removeAnswerForm("removeBillboard");
			_fe3d.billboardEntity_delete(_currentBillboardName);
			_billboardNames.erase(std::remove(_billboardNames.begin(), _billboardNames.end(), _currentBillboardName), _billboardNames.end());
			_billboardRemovalEnabled = false;
			_currentBillboardName = "";
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("removeBillboard"))
		{
			_billboardChoosingEnabled = true;
			_currentBillboardName = "";
		}
	}
}

void BillboardEditor::_updateBillboardCamera()
{
	if (_currentBillboardName != "")
	{
		vec3 billboardSize = _fe3d.billboardEntity_getSize(_currentBillboardName);
		_fe3d.camera_setPosition(vec3(0.0f, _cameraHeight + billboardSize.y / 2.0f, (billboardSize.x * 4.0f)));
	}
}