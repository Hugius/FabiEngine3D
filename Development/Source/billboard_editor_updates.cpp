#include "billboard_editor.hpp"

#include <algorithm>

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
			_gui->getGlobalScreen()->addValueForm("newBillboardName", "New billboard name", "", vec2(0.0f), vec2(0.5f, 0.1f));
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
				_fe3d.billBoardEntity_add(newBillboardName, vec3(1.0f), _billboardPosition, vec3(0.0f), vec2(1.0f), false, false);
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
				_gui->getGlobalScreen()->addValueForm("sizeX", "X", _fe3d.billboardEntity_getSize(_currentBillboardName).x * 10.0f, vec2(-0.25f, 0.0f), vec2(0.3f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("sizeY", "Y", _fe3d.billboardEntity_getSize(_currentBillboardName).y * 10.0f, vec2(0.25f, 0.0f), vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
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

		// Setting billboard size
		vec2 newSize = _fe3d.billboardEntity_getSize(_currentBillboardName) * 10.0f;
		_gui->getGlobalScreen()->checkValueForm("sizeX", newSize.x, { 0.0f });
		_gui->getGlobalScreen()->checkValueForm("sizeY", newSize.y, { 0.0f });
		_fe3d.billboardEntity_setSize(_currentBillboardName, newSize / 10.0f);

		// Setting billboard color
		vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardName) * 255.0f;
		_gui->getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
		_gui->getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
		_gui->getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
		newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
		newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
		newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
		_fe3d.billboardEntity_setColor(_currentBillboardName, newColor);
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
		vec2 billboardSize = _fe3d.billboardEntity_getSize(_currentBillboardName);
		float cameraDistance = (max(billboardSize.x, billboardSize.y) * 2.0f);
		float cameraHeight = _billboardPosition.y + (billboardSize.y / 2.0f);

		// Get scroll wheel input
		if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
		{
			float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) / _scrollWheelDivider;
			_cameraRotationSpeed += rotationAcceleration;
		}
		_cameraRotationSpeed *= 0.975f;
		_totalCameraRotation += _cameraRotationSpeed;

		// Calculate new camera position
		float x = cameraDistance * sin(_totalCameraRotation);
		float y = cameraHeight;
		float z = cameraDistance * cos(_totalCameraRotation);

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
		_fe3d.camera_enableLookat(vec3(0.0f, cameraHeight, 0.0f));
	}
	else
	{
		_fe3d.camera_setPosition(_defaultCameraPosition);
		_fe3d.camera_enableLookat(_billboardPosition);
	}
}