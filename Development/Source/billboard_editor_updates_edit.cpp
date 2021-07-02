#include "billboard_editor.hpp"

#include <algorithm>

void BillboardEditor::_updateBillboardEditing()
{
	if (_isEditorLoaded)
	{
		if (_isEditingBillboard && _currentBillboardID != "")
		{
			// Shortened screen instance
			auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

			// GUI management
			if (screen->getID() == "billboardEditorMenuChoice")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_fe3d.billboardEntity_setVisible(_currentBillboardID, false);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), false);
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
				screen->getButton("appearance")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) == "");
				screen->getButton("animation")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID) != "");
				screen->getButton("text")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID) == "");
			}
			else if (screen->getID() == "billboardEditorMenuMesh")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
					else if (screen->getButton("size")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("sizeX", "X", _fe3d.billboardEntity_getSize(_currentBillboardID).x * 100.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("sizeY", "Y", _fe3d.billboardEntity_getSize(_currentBillboardID).y * 100.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
					}
					else if (screen->getButton("facingX")->isHovered())
					{
						bool isFacingX = !_fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
						_fe3d.billboardEntity_setCameraFacingX(_currentBillboardID, isFacingX);
					}
					else if (screen->getButton("facingY")->isHovered())
					{
						bool isFacingY = !_fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
						_fe3d.billboardEntity_setCameraFacingY(_currentBillboardID, isFacingY);
					}
					else if (screen->getButton("isReflected")->isHovered())
					{
						bool isReflected = _fe3d.billboardEntity_isReflected(_currentBillboardID);
						_fe3d.billboardEntity_setReflected(_currentBillboardID, !isReflected);
					}
					else if (screen->getButton("isShadowed")->isHovered())
					{
						bool isShadowed = _fe3d.billboardEntity_isShadowed(_currentBillboardID);
						_fe3d.billboardEntity_setShadowed(_currentBillboardID, !isShadowed);
					}
				}

				// Setting billboard size
				Vec2 newSize = _fe3d.billboardEntity_getSize(_currentBillboardID) * 100.0f;
				_gui.getGlobalScreen()->checkValueForm("sizeX", newSize.x, { 0.0f });
				_gui.getGlobalScreen()->checkValueForm("sizeY", newSize.y, { 0.0f });
				newSize.x = std::max(0.0f, newSize.x / 100.0f);
				newSize.y = std::max(0.0f, newSize.y / 100.0f);
				_fe3d.billboardEntity_setSize(_currentBillboardID, newSize);

				// Update facing buttons text
				string textEntityIDx = screen->getButton("facingX")->getTextfield()->getEntityID();
				string textEntityIDy = screen->getButton("facingY")->getTextfield()->getEntityID();
				bool isFacingX = _fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
				bool isFacingY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
				_fe3d.textEntity_setTextContent(textEntityIDx, isFacingX ? "Facing X: ON" : "Facing X: OFF");
				_fe3d.textEntity_setTextContent(textEntityIDy, isFacingY ? "Facing Y: ON" : "Facing Y: OFF");

				// Reset rotations if not facing camera
				Vec3 rotation = _fe3d.billboardEntity_getRotation(_currentBillboardID);
				if (!isFacingX)
				{
					rotation.x = 0.0f;
					rotation.z = 0.0f;
				}
				if (!isFacingY)
				{
					rotation.y = 0.0f;
				}
				_fe3d.billboardEntity_setRotation(_currentBillboardID, rotation);

				// Updating reflected status
				string reflectedTextEntityID = screen->getButton("isReflected")->getTextfield()->getEntityID();
				bool isReflected = _fe3d.billboardEntity_isReflected(_currentBillboardID);
				_fe3d.billboardEntity_setReflected(_currentBillboardID, isReflected);
				_fe3d.textEntity_setTextContent(reflectedTextEntityID, isReflected ? "Reflected: ON" : "Reflected: OFF");

				// Updating shadowed status
				string shadowedEntityID = screen->getButton("isShadowed")->getTextfield()->getEntityID();
				bool isShadowed = _fe3d.billboardEntity_isShadowed(_currentBillboardID);
				_fe3d.billboardEntity_setShadowed(_currentBillboardID, isShadowed);
				_fe3d.textEntity_setTextContent(shadowedEntityID, isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
			}
			else if (screen->getID() == "billboardEditorMenuAppearance")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
					else if (screen->getButton("lightness")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("lightness", "Lightness", _fe3d.billboardEntity_getLightness(_currentBillboardID) * 100.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
					}
					else if (screen->getButton("color")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("colorR", "R", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorG", "G", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorB", "B", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
					}
					else if (screen->getButton("texture")->isHovered())
					{
						// Get the chosen filename
						const string rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("game_assets\\textures\\billboard_maps\\");
						const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

						// Check if user did not cancel
						if (filePath != "")
						{
							// Check if user did not switch directory
							if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
								filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
							{
								const string newFilePath = filePath.substr(rootDirectory.size());
								_fe3d.misc_clearTextureCache2D(newFilePath);
								_fe3d.billboardEntity_setDiffuseMap(_currentBillboardID, newFilePath);
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
				}

				// Setting billboard lightness
				float newLightness;
				if (_gui.getGlobalScreen()->checkValueForm("lightness", newLightness, { }))
				{
					newLightness = std::max(0.0f, newLightness / 100.0f);
					_fe3d.billboardEntity_setLightness(_currentBillboardID, newLightness);
				}

				// Setting billboard color
				Vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
				_gui.getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
				_gui.getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
				_gui.getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
				newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
				newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
				newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
				_fe3d.billboardEntity_setColor(_currentBillboardID, newColor);

				// Updating transparent status
				string transparentTextEntityID = screen->getButton("isTransparent")->getTextfield()->getEntityID();
				bool isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardID);
				_fe3d.billboardEntity_setTransparent(_currentBillboardID, isTransparent);
				_fe3d.textEntity_setTextContent(transparentTextEntityID, isTransparent ? "Alpha: ON" : "Alpha: OFF");
			}
			else if (screen->getID() == "billboardEditorMenuAnimation")
			{
				int animationRowCount = _fe3d.billboardEntity_getSpriteAnimationRows(_currentBillboardID);
				int animationColumnCount = _fe3d.billboardEntity_getSpriteAnimationColumns(_currentBillboardID);
				int animationFramestep = _fe3d.billboardEntity_getSpriteAnimationFramestep(_currentBillboardID);

				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
					else if (screen->getButton("animate")->isHovered())
					{
						_fe3d.billboardEntity_startSpriteAnimation(_currentBillboardID, -1);
					}
					else if (screen->getButton("rows")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("rows", "Rows", animationRowCount, Vec2(0.0f), Vec2(0.15f, 0.1f));
					}
					else if (screen->getButton("columns")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("columns", "Columns", animationColumnCount, Vec2(0.0f), Vec2(0.15f, 0.1f));
					}
					else if (screen->getButton("speed")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("speed", "Frame steps", animationFramestep, Vec2(0.0f), Vec2(0.15f, 0.1f));
					}
				}

				// Update button hoverability
				bool playing = _fe3d.billboardEntity_isSpriteAnimationStarted(_currentBillboardID);
				screen->getButton("animate")->setHoverable(!playing && animationRowCount != 0 && animationColumnCount != 0);

				// Update value filling
				if (_gui.getGlobalScreen()->checkValueForm("rows", animationRowCount, { 0 }) ||
					_gui.getGlobalScreen()->checkValueForm("columns", animationColumnCount, { 0 }) ||
					_gui.getGlobalScreen()->checkValueForm("speed", animationFramestep, { }))
				{
					if (playing) // Only if animation is already playing
					{
						_fe3d.billboardEntity_stopSpriteAnimation(_currentBillboardID);
						_fe3d.billboardEntity_startSpriteAnimation(_currentBillboardID, -1);
					}
				}

				// Update animation values
				_fe3d.billboardEntity_setSpriteAnimationRows(_currentBillboardID, std::max(0, animationRowCount));
				_fe3d.billboardEntity_setSpriteAnimationColumns(_currentBillboardID, std::max(0, animationColumnCount));
				_fe3d.billboardEntity_setSpriteAnimationFramestep(_currentBillboardID, std::max(0, animationFramestep));
			}
			else if (screen->getID() == "billboardEditorMenuText")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					}
					else if (screen->getButton("font")->isHovered())
					{
						// Get the chosen filename
						const string rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("game_assets\\fonts\\");
						const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "TTF");

						// Check if user did not cancel
						if (filePath != "")
						{
							// Check if user did not switch directory
							if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
								filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
							{
								// Set font
								const string newFilePath = filePath.substr(rootDirectory.size());
								_fe3d.misc_clearFontCache(newFilePath);
								_fe3d.misc_clearTextCache(_fe3d.billboardEntity_getTextContent(_currentBillboardID), 
									_fe3d.billboardEntity_getFontPath(_currentBillboardID));
								_fe3d.billboardEntity_setFont(_currentBillboardID, newFilePath);

								// Set default text
								if (_fe3d.billboardEntity_getTextContent(_currentBillboardID).empty())
								{
									_fe3d.billboardEntity_setTextContent(_currentBillboardID, "text");
								}
							}
							else
							{
								_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
							}
						}
					}
					else if (screen->getButton("color")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("colorR", "R", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorG", "G", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
						_gui.getGlobalScreen()->addValueForm("colorB", "B", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
					}
					else if (screen->getButton("content")->isHovered())
					{
						_gui.getGlobalScreen()->addValueForm("content", "Text content", _fe3d.billboardEntity_getTextContent(_currentBillboardID), Vec2(0.0f), Vec2(0.15f, 0.1f));
					}
				}

				// Updating buttons hoverability
				screen->getButton("color")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");
				screen->getButton("content")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");

				// Setting text color
				Vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
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
					_fe3d.billboardEntity_setTextContent(_currentBillboardID, textContent);
				}
			}
		}
	}
}