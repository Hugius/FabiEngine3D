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

		// First time initializations
		if (firstTime)
		{
			firstTime = false;
			_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("currentBillboardName")->getEntityID(), "Billboard: " + _currentBillboardName, 0.025f);
			_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("currentBillboardName")->getEntityID());
			_fe3d.billboardEntity_show(_currentBillboardName);
			_window->setActiveScreen("billboardEditingMain");
		}

		// Shortened screen instance
		auto screen = _window->getActiveScreen();

		// GUI management
		if (_window->getActiveScreen()->getID() == "billboardEditingMain")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mesh")->isHovered())
				{
					_window->setActiveScreen("billboardEditingMesh");
				}
				else if (screen->getButton("appearance")->isHovered())
				{
					_window->setActiveScreen("billboardEditingAppearance");
				}
				else if (screen->getButton("animation")->isHovered())
				{
					_window->setActiveScreen("billboardEditingAnimation");
				}
				else if (screen->getButton("text")->isHovered())
				{
					_window->setActiveScreen("billboardEditingText");
				}
				else if (screen->getButton("back")->isHovered())
				{
					_fe3d.billboardEntity_hide(_currentBillboardName);
					_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("currentBillboardName")->getEntityID());
					_currentBillboardName = "";
					_billboardEditingEnabled = false;
					firstTime = true;
					_window->setActiveScreen("billboardManagement");
					return;
				}
			}

			// Update buttons hoverability
			screen->getButton("appearance")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardName) == "");
			screen->getButton("animation")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardName) != "");
			screen->getButton("text")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardName) == "");
		}
		else if (_window->getActiveScreen()->getID() == "billboardEditingMesh")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("size")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("sizeX", "X", _fe3d.billboardEntity_getSize(_currentBillboardName).x * 10.0f, vec2(-0.25f, 0.0f), vec2(0.3f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("sizeY", "Y", _fe3d.billboardEntity_getSize(_currentBillboardName).y * 10.0f, vec2(0.25f, 0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("facingX")->isHovered())
				{
					bool isFacedX = !_fe3d.billboardEntity_isFacingCameraX(_currentBillboardName);
					_fe3d.billboardEntity_setCameraFacingX(_currentBillboardName, isFacedX);
				}
				else if (screen->getButton("facingY")->isHovered())
				{
					bool isFacedY = !_fe3d.billboardEntity_isFacingCameraY(_currentBillboardName);
					_fe3d.billboardEntity_setCameraFacingY(_currentBillboardName, isFacedY);
				}
				else if (screen->getButton("back")->isHovered())
				{
					_window->setActiveScreen("billboardEditingMain");
				}
			}

			// Setting billboard size
			vec2 newSize = _fe3d.billboardEntity_getSize(_currentBillboardName) * 10.0f;
			_gui->getGlobalScreen()->checkValueForm("sizeX", newSize.x, { 0.0f });
			_gui->getGlobalScreen()->checkValueForm("sizeY", newSize.y, { 0.0f });
			_fe3d.billboardEntity_setSize(_currentBillboardName, newSize / 10.0f);

			// Update facing buttons text
			string textEntityIDx = screen->getButton("facingY")->getTextfield()->getEntityID();
			string textEntityIDy = screen->getButton("facingY")->getTextfield()->getEntityID();
			bool isFacedX = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardName);
			bool isFacedY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardName);
			_fe3d.textEntity_setTextContent(textEntityIDx, isFacedX ? "Facing X: ON" : "Facing X: OFF");
			_fe3d.textEntity_setTextContent(textEntityIDy, isFacedY ? "Facing Y: ON" : "Facing Y: OFF");
		}
		else if (_window->getActiveScreen()->getID() == "billboardEditingAppearance")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("color")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("texture")->isHovered())
				{
					string path = "User\\Assets\\Textures\\BillboardMaps\\";
					string fileName = _fe3d.misc_getWinExplorerFilename(path, "PNG");

					// Check if user did not cancel
					if (fileName != "")
					{
						_fe3d.billboardEntity_setDiffuseMap(_currentBillboardName, path + fileName, false);
					}
				}
				else if (screen->getButton("transparent")->isHovered())
				{
					bool isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardName);
					_fe3d.billboardEntity_setTransparent(_currentBillboardName, !isTransparent);
				}
				else if (screen->getButton("back")->isHovered())
				{
					_window->setActiveScreen("billboardEditingMain");
				}
			}

			// Setting billboard color
			vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardName) * 255.0f;
			_gui->getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
			_gui->getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
			_gui->getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
			newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
			newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
			newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
			_fe3d.billboardEntity_setColor(_currentBillboardName, newColor);

			// Updating transparency
			string textEntityID = screen->getButton("transparent")->getTextfield()->getEntityID();
			bool isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardName);
			_fe3d.billboardEntity_setTransparent(_currentBillboardName, isTransparent);
			_fe3d.textEntity_setTextContent(textEntityID, isTransparent ? "No-white: ON" : "No-white: OFF");
		}
		else if (_window->getActiveScreen()->getID() == "billboardEditingAnimation")
		{
			int animationRowCount = _fe3d.billboardEntity_getAnimationRows(_currentBillboardName);
			int animationColumnCount = _fe3d.billboardEntity_getAnimationColumns(_currentBillboardName);
			int animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(_currentBillboardName);

			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("animate")->isHovered())
				{
					_fe3d.billBoardEntity_playSpriteAnimation(_currentBillboardName, -1);
				}
				else if (screen->getButton("rows")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("rows", "Rows", animationRowCount, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("columns")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("columns", "Columns", animationColumnCount, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("speed")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("speed", "Frame steps", animationFramestep, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered())
				{
					_window->setActiveScreen("billboardEditingMain");
				}
			}
			
			// Update button hoverability
			bool playing = _fe3d.billboardEntity_isAnimationPlaying(_currentBillboardName);
			screen->getButton("animate")->setHoverable(!playing && animationRowCount != 0 && animationColumnCount != 0);

			// Update value filling
			if (_gui->getGlobalScreen()->checkValueForm("rows", animationRowCount, { 0 })	    ||
				_gui->getGlobalScreen()->checkValueForm("columns", animationColumnCount, { 0 }) ||
				_gui->getGlobalScreen()->checkValueForm("speed", animationFramestep, { }))
			{
				if (playing) // Only if animation is already playing
				{
					_fe3d.billBoardEntity_playSpriteAnimation(_currentBillboardName, -1);
				}
			}

			// Update animation values
			_fe3d.billboardEntity_setAnimationRows(_currentBillboardName, animationRowCount);
			_fe3d.billboardEntity_setAnimationColumns(_currentBillboardName, animationColumnCount);
			_fe3d.billboardEntity_setAnimationFramestep(_currentBillboardName, animationFramestep);
		}
		else if (_window->getActiveScreen()->getID() == "billboardEditingText")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("color")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardName).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("font")->isHovered())
				{
					string path = "User\\Assets\\Fonts\\";
					string fileName = _fe3d.misc_getWinExplorerFilename(path, "TTF");

					// Check if user did not cancel
					if (fileName != "")
					{
						_fe3d.billBoardEntity_setFont(_currentBillboardName, path + fileName);
					}
				}
				else if (screen->getButton("content")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("content", "Text content", _fe3d.billboardEntity_getTextContent(_currentBillboardName), vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered())
				{
					_window->setActiveScreen("billboardEditingMain");
				}
			}

			// Setting text color
			vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardName) * 255.0f;
			_gui->getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
			_gui->getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
			_gui->getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
			newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
			newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
			newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
			_fe3d.billboardEntity_setColor(_currentBillboardName, newColor);

			// Updating text content
			string textContent = "";
			if (_gui->getGlobalScreen()->checkValueForm("content", textContent, { }))
			{
				_fe3d.billBoardEntity_setTextContent(_currentBillboardName, textContent);
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