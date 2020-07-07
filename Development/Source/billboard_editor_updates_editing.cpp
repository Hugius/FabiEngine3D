#include "billboard_editor.hpp"

#include <algorithm>

void BillboardEditor::_updateBillboardEditing()
{
	if (_isLoaded)
	{
		if (_billboardEditingEnabled && _currentBillboardID != "")
		{
			static bool firstTime = true;

			// First time initializations
			if (firstTime)
			{
				firstTime = false;
				_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), "Billboard: " +
					_currentBillboardID.substr(1, _currentBillboardID.size()), 0.025f);
				_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID());
				_fe3d.billboardEntity_show(_currentBillboardID);
				_leftWindow->setActiveScreen("billboardEditingMain");
			}

			// Shortened screen instance
			auto screen = _leftWindow->getActiveScreen();

			// GUI management
			if (_leftWindow->getActiveScreen()->getID() == "billboardEditingMain")
			{
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("mesh")->isHovered())
					{
						_leftWindow->setActiveScreen("billboardEditingMesh");
					}
					else if (screen->getButton("appearance")->isHovered())
					{
						_leftWindow->setActiveScreen("billboardEditingAppearance");
					}
					else if (screen->getButton("animation")->isHovered())
					{
						_leftWindow->setActiveScreen("billboardEditingAnimation");
					}
					else if (screen->getButton("text")->isHovered())
					{
						_leftWindow->setActiveScreen("billboardEditingText");
					}
					else if (screen->getButton("back")->isHovered())
					{
						_fe3d.billboardEntity_hide(_currentBillboardID);
						_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID());
						_currentBillboardID = "";
						_billboardEditingEnabled = false;
						firstTime = true;
						_leftWindow->setActiveScreen("billboardManagement");
						return;
					}
				}

				// Update buttons hoverability
				screen->getButton("appearance")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) == "");
				screen->getButton("animation")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID) != "");
				screen->getButton("text")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID) == "");
			}
			else if (_leftWindow->getActiveScreen()->getID() == "billboardEditingMesh")
			{
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("size")->isHovered())
					{
						_gui->getGlobalScreen()->addValueForm("sizeX", "X", _fe3d.billboardEntity_getSize(_currentBillboardID).x * 10.0f, vec2(-0.25f, 0.0f), vec2(0.3f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("sizeY", "Y", _fe3d.billboardEntity_getSize(_currentBillboardID).y * 10.0f, vec2(0.25f, 0.0f), vec2(0.3f, 0.1f));
					}
					else if (screen->getButton("facingX")->isHovered())
					{
						bool isFacedX = !_fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
						_fe3d.billboardEntity_setCameraFacingX(_currentBillboardID, isFacedX);
					}
					else if (screen->getButton("facingY")->isHovered())
					{
						bool isFacedY = !_fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
						_fe3d.billboardEntity_setCameraFacingY(_currentBillboardID, isFacedY);
					}
					else if (screen->getButton("back")->isHovered())
					{
						_leftWindow->setActiveScreen("billboardEditingMain");
					}
				}

				// Setting billboard size
				vec2 newSize = _fe3d.billboardEntity_getSize(_currentBillboardID) * 10.0f;
				_gui->getGlobalScreen()->checkValueForm("sizeX", newSize.x, { 0.0f });
				_gui->getGlobalScreen()->checkValueForm("sizeY", newSize.y, { 0.0f });
				_fe3d.billboardEntity_setSize(_currentBillboardID, newSize / 10.0f);

				// Update facing buttons text
				string textEntityIDx = screen->getButton("facingX")->getTextfield()->getEntityID();
				string textEntityIDy = screen->getButton("facingY")->getTextfield()->getEntityID();
				bool isFacedX = _fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
				bool isFacedY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
				_fe3d.textEntity_setTextContent(textEntityIDx, isFacedX ? "Facing X: ON" : "Facing X: OFF");
				_fe3d.textEntity_setTextContent(textEntityIDy, isFacedY ? "Facing Y: ON" : "Facing Y: OFF");
			}
			else if (_leftWindow->getActiveScreen()->getID() == "billboardEditingAppearance")
			{
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("color")->isHovered())
					{
						_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
					}
					else if (screen->getButton("texture")->isHovered())
					{
						string path = "User\\Assets\\Textures\\BillboardMaps\\";
						string fileName = _fe3d.misc_getWinExplorerFilename(path, "PNG");

						// Check if user did not cancel
						if (fileName != "")
						{
							_fe3d.billboardEntity_setDiffuseMap(_currentBillboardID, path + fileName, false);
						}
					}
					else if (screen->getButton("transparent")->isHovered())
					{
						bool isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardID);
						_fe3d.billboardEntity_setTransparent(_currentBillboardID, !isTransparent);
					}
					else if (screen->getButton("back")->isHovered())
					{
						_leftWindow->setActiveScreen("billboardEditingMain");
					}
				}

				// Setting billboard color
				vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
				_gui->getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
				_gui->getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
				_gui->getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
				newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
				newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
				newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
				_fe3d.billboardEntity_setColor(_currentBillboardID, newColor);

				// Updating transparency
				string textEntityID = screen->getButton("transparent")->getTextfield()->getEntityID();
				bool isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardID);
				_fe3d.billboardEntity_setTransparent(_currentBillboardID, isTransparent);
				_fe3d.textEntity_setTextContent(textEntityID, isTransparent ? "No-white: ON" : "No-white: OFF");
			}
			else if (_leftWindow->getActiveScreen()->getID() == "billboardEditingAnimation")
			{
				int animationRowCount = _fe3d.billboardEntity_getAnimationRows(_currentBillboardID);
				int animationColumnCount = _fe3d.billboardEntity_getAnimationColumns(_currentBillboardID);
				int animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(_currentBillboardID);

				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("animate")->isHovered())
					{
						_fe3d.billBoardEntity_playSpriteAnimation(_currentBillboardID, -1);
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
						_leftWindow->setActiveScreen("billboardEditingMain");
					}
				}

				// Update button hoverability
				bool playing = _fe3d.billboardEntity_isAnimationPlaying(_currentBillboardID);
				screen->getButton("animate")->setHoverable(!playing && animationRowCount != 0 && animationColumnCount != 0);

				// Update value filling
				if (_gui->getGlobalScreen()->checkValueForm("rows", animationRowCount, { 0 }) ||
					_gui->getGlobalScreen()->checkValueForm("columns", animationColumnCount, { 0 }) ||
					_gui->getGlobalScreen()->checkValueForm("speed", animationFramestep, { }))
				{
					if (playing) // Only if animation is already playing
					{
						_fe3d.billBoardEntity_playSpriteAnimation(_currentBillboardID, -1);
					}
				}

				// Update animation values
				_fe3d.billboardEntity_setAnimationRows(_currentBillboardID, animationRowCount);
				_fe3d.billboardEntity_setAnimationColumns(_currentBillboardID, animationColumnCount);
				_fe3d.billboardEntity_setAnimationFramestep(_currentBillboardID, animationFramestep);
			}
			else if (_leftWindow->getActiveScreen()->getID() == "billboardEditingText")
			{
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("font")->isHovered())
					{
						string path = "User\\Assets\\Fonts\\";
						string fileName = _fe3d.misc_getWinExplorerFilename(path, "TTF");

						// Check if user did not cancel
						if (fileName != "")
						{
							_fe3d.billBoardEntity_setFont(_currentBillboardID, path + fileName);
						}
					}
					else if (screen->getButton("color")->isHovered())
					{
						_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
						_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
					}
					else if (screen->getButton("content")->isHovered())
					{
						_gui->getGlobalScreen()->addValueForm("content", "Text content", _fe3d.billboardEntity_getTextContent(_currentBillboardID), vec2(0.0f), vec2(0.3f, 0.1f));
					}
					else if (screen->getButton("back")->isHovered())
					{
						_leftWindow->setActiveScreen("billboardEditingMain");
					}
				}

				// Updating buttons hoverability
				screen->getButton("color")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");
				screen->getButton("content")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");

				// Setting text color
				vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
				_gui->getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
				_gui->getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
				_gui->getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
				newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
				newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
				newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
				_fe3d.billboardEntity_setColor(_currentBillboardID, newColor);

				// Updating text content
				string textContent = "";
				if (_gui->getGlobalScreen()->checkValueForm("content", textContent, { }))
				{
					_fe3d.billBoardEntity_setTextContent(_currentBillboardID, textContent);
				}
			}
		}
	}
}