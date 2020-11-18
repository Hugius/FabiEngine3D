#include "billboard_editor.hpp"

#include <algorithm>

void BillboardEditor::_updateBillboardEditing()
{
	if (_isLoaded)
	{
		if (_isEditingBillboard && _currentBillboardID != "")
		{
			// Shortened screen instance
			auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

			// GUI management
			if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "billboardEditorMenuChoice")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("mesh")->isHovered())
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
					else if (screen->getButton("back")->isHovered())
					{
						_fe3d.billboardEntity_hide(_currentBillboardID);
						_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID());
						_currentBillboardID = "";
						_isEditingBillboard = false;
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");
						return;
					}
				}

				// Update buttons hoverability
				screen->getButton("appearance")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) == "");
				screen->getButton("animation")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID) != "");
				screen->getButton("text")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID) == "");
			}
			else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "billboardEditorMenuMesh")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("size")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("sizeX", "X", _fe3d.billboardEntity_getSize(_currentBillboardID).x * 10.0f, vec2(-0.25f, 0.0f), vec2(0.3f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("sizeY", "Y", _fe3d.billboardEntity_getSize(_currentBillboardID).y * 10.0f, vec2(0.25f, 0.0f), vec2(0.3f, 0.1f));
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
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
				}

				// Setting billboard size
				vec2 newSize = _fe3d.billboardEntity_getSize(_currentBillboardID) * 10.0f;
				_gui.getGlobalScreen()->checkValueForm("sizeX", newSize.x, { 0.0f });
				_gui.getGlobalScreen()->checkValueForm("sizeY", newSize.y, { 0.0f });
				_fe3d.billboardEntity_setSize(_currentBillboardID, newSize / 10.0f);

				// Update facing buttons text
				string textEntityIDx = screen->getButton("facingX")->getTextfield()->getEntityID();
				string textEntityIDy = screen->getButton("facingY")->getTextfield()->getEntityID();
				bool isFacedX = _fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
				bool isFacedY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
				_fe3d.textEntity_setTextContent(textEntityIDx, isFacedX ? "Facing X: ON" : "Facing X: OFF");
				_fe3d.textEntity_setTextContent(textEntityIDy, isFacedY ? "Facing Y: ON" : "Facing Y: OFF");
			}
			else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "billboardEditorMenuAppearance")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("color")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
					}
					else if (screen->getButton("texture")->isHovered())
					{
						const string rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("user\\assets\\textures\\billboard_maps\\");
						const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

						// Check if user did not cancel
						if (filePath != "")
						{
							// Check if user did not switch directory
							if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
								filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
							{
								const string newFilePath = filePath.substr(rootDirectory.size());
								_fe3d.misc_clearTextureCache(newFilePath);
								_fe3d.billboardEntity_setDiffuseMap(_currentBillboardID, newFilePath, false);
							}
							else
							{
								_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
							}
						}
					}
					else if (screen->getButton("isTransparent")->isHovered())
					{
						bool isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardID);
						_fe3d.billboardEntity_setTransparent(_currentBillboardID, !isTransparent);
					}
					else if (screen->getButton("back")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
				}

				// Setting billboard color
				vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
				_gui.getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
				_gui.getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
				_gui.getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
				newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
				newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
				newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
				_fe3d.billboardEntity_setColor(_currentBillboardID, newColor);

				// Updating transparency
				string textEntityID = screen->getButton("isTransparent")->getTextfield()->getEntityID();
				bool isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardID);
				_fe3d.billboardEntity_setTransparent(_currentBillboardID, isTransparent);
				_fe3d.textEntity_setTextContent(textEntityID, isTransparent ? "Alpha: ON" : "Alpha: OFF");
			}
			else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "billboardEditorMenuAnimation")
			{
				int animationRowCount = _fe3d.billboardEntity_getAnimationRows(_currentBillboardID);
				int animationColumnCount = _fe3d.billboardEntity_getAnimationColumns(_currentBillboardID);
				int animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(_currentBillboardID);

				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("animate")->isHovered())
					{
						_fe3d.billBoardEntity_playSpriteAnimation(_currentBillboardID, -1);
					}
					else if (screen->getButton("rows")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("rows", "Rows", animationRowCount, vec2(0.0f), vec2(0.3f, 0.1f));
					}
					else if (screen->getButton("columns")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("columns", "Columns", animationColumnCount, vec2(0.0f), vec2(0.3f, 0.1f));
					}
					else if (screen->getButton("speed")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("speed", "Frame steps", animationFramestep, vec2(0.0f), vec2(0.3f, 0.1f));
					}
					else if (screen->getButton("back")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
				}

				// Update button hoverability
				bool playing = _fe3d.billboardEntity_isAnimationPlaying(_currentBillboardID);
				screen->getButton("animate")->setHoverable(!playing && animationRowCount != 0 && animationColumnCount != 0);

				// Update value filling
				if (_gui.getGlobalScreen()->checkValueForm("rows", animationRowCount, { 0 }) ||
					_gui.getGlobalScreen()->checkValueForm("columns", animationColumnCount, { 0 }) ||
					_gui.getGlobalScreen()->checkValueForm("speed", animationFramestep, { }))
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
			else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "billboardEditorMenuText")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("font")->isHovered())
					{
						const string rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("user\\assets\\fonts\\");
						const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "TTF");

						// Check if user did not cancel
						if (filePath != "")
						{
							// Check if user did not switch directory
							if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
								filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
							{
								const string newFilePath = filePath.substr(rootDirectory.size());
								_fe3d.misc_clearFontCache(newFilePath);
								_fe3d.misc_clearTextCache(_fe3d.billboardEntity_getTextContent(_currentBillboardID), 
									_fe3d.billboardEntity_getFontPath(_currentBillboardID));
								_fe3d.billBoardEntity_setFont(_currentBillboardID, newFilePath);
							}
							else
							{
								_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
							}
						}
					}
					else if (screen->getButton("color")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
					}
					else if (screen->getButton("content")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("content", "Text content", _fe3d.billboardEntity_getTextContent(_currentBillboardID), vec2(0.0f), vec2(0.3f, 0.1f));
					}
					else if (screen->getButton("back")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
				}

				// Updating buttons hoverability
				screen->getButton("color")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");
				screen->getButton("content")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");

				// Setting text color
				vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
				_gui.getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
				_gui.getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
				_gui.getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
				newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
				newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
				newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
				_fe3d.billboardEntity_setColor(_currentBillboardID, newColor);

				// Updating text content
				string textContent = "";
				if (_gui.getGlobalScreen()->checkValueForm("content", textContent, { }))
				{
					_fe3d.misc_clearFontCache(_fe3d.billboardEntity_getFontPath(_currentBillboardID));
					_fe3d.misc_clearTextCache(textContent, _fe3d.billboardEntity_getFontPath(_currentBillboardID));
					_fe3d.billBoardEntity_setTextContent(_currentBillboardID, textContent);
				}
			}
		}
	}
}