#include "billboard_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void BillboardEditor::_updateChoiceMenu()
{
	if (_isEditingBillboard && _currentBillboardID != "")
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
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("billboardID")->getEntityID(), false);
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
			screen->getButton("appearance")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID).empty());
			screen->getButton("animation")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID) != "");
			screen->getButton("text")->setHoverable(_fe3d.billboardEntity_getDiffuseMapPath(_currentBillboardID).empty());
		}
		else if (screen->getID() == "billboardEditorMenuMesh")
		{
			// Temporary values
			auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
			auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
			auto isReflected = _fe3d.billboardEntity_isReflected(_currentBillboardID);
			auto isShadowed = _fe3d.billboardEntity_isShadowed(_currentBillboardID);
			auto isBright = _fe3d.billboardEntity_isBright(_currentBillboardID);

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					return;
				}
				else if (screen->getButton("size")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("sizeX", "X", _fe3d.billboardEntity_getSize(_currentBillboardID).x * 100.0f, Vec2(-0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->createValueForm("sizeY", "Y", _fe3d.billboardEntity_getSize(_currentBillboardID).y * 100.0f, Vec2(0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("facingX")->isHovered())
				{
					isFacingX = !isFacingX;
					_fe3d.billboardEntity_setCameraFacingX(_currentBillboardID, isFacingX);
				}
				else if (screen->getButton("facingY")->isHovered())
				{
					isFacingY = !isFacingY;
					_fe3d.billboardEntity_setCameraFacingY(_currentBillboardID, isFacingY);
				}
				else if (screen->getButton("isShadowed")->isHovered())
				{
					isShadowed = !isShadowed;
					_fe3d.billboardEntity_setShadowed(_currentBillboardID, isShadowed);
				}
				else if (screen->getButton("isReflected")->isHovered())
				{
					isReflected = !isReflected;
					_fe3d.billboardEntity_setReflected(_currentBillboardID, isReflected);
				}
				else if (screen->getButton("isBright")->isHovered())
				{
					isBright = !isBright;
					_fe3d.billboardEntity_setBright(_currentBillboardID, isBright);
				}
			}

			// Setting billboard size
			Vec2 newSize = _fe3d.billboardEntity_getSize(_currentBillboardID) * 100.0f;
			_gui.getGlobalScreen()->checkValueForm("sizeX", newSize.x, { 0.0f });
			_gui.getGlobalScreen()->checkValueForm("sizeY", newSize.y, { 0.0f });
			newSize.x = max(0.0f, newSize.x / 100.0f);
			newSize.y = max(0.0f, newSize.y / 100.0f);
			_fe3d.billboardEntity_setSize(_currentBillboardID, newSize);

			// Button text contents
			screen->getButton("facingX")->changeTextContent(isFacingX ? "Facing X: ON" : "Facing X: OFF");
			screen->getButton("facingY")->changeTextContent(isFacingY ? "Facing Y: ON" : "Facing Y: OFF");
			screen->getButton("isBright")->changeTextContent(isBright ? "Bright: ON" : "Bright : OFF");

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

			// Button text contents
			screen->getButton("isReflected")->changeTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
			screen->getButton("isShadowed")->changeTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
		}
		else if (screen->getID() == "billboardEditorMenuAppearance")
		{
			// Temporary values
			auto isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardID);

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					return;
				}
				else if (screen->getButton("lightness")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", _fe3d.billboardEntity_getLightness(_currentBillboardID) * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("colorR", "R", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->createValueForm("colorG", "G", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->createValueForm("colorB", "B", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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
							Logger::throwWarning("Invalid filepath, directory switching not allowed!");
						}
					}
				}
				else if (screen->getButton("isTransparent")->isHovered())
				{
					isTransparent = !isTransparent;
					_fe3d.billboardEntity_setTransparent(_currentBillboardID, isTransparent);
				}
			}

			// Setting billboard lightness
			float newLightness;
			if (_gui.getGlobalScreen()->checkValueForm("lightness", newLightness, {}))
			{
				newLightness = max(0.0f, newLightness / 100.0f);
				_fe3d.billboardEntity_setLightness(_currentBillboardID, newLightness);
			}

			// Setting billboard color
			Vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
			_gui.getGlobalScreen()->checkValueForm("colorR", newColor.r, {});
			_gui.getGlobalScreen()->checkValueForm("colorG", newColor.g, {});
			_gui.getGlobalScreen()->checkValueForm("colorB", newColor.b, {});
			newColor.r = clamp(newColor.r / 255.0f, 0.0f, 1.0f);
			newColor.g = clamp(newColor.g / 255.0f, 0.0f, 1.0f);
			newColor.b = clamp(newColor.b / 255.0f, 0.0f, 1.0f);
			_fe3d.billboardEntity_setColor(_currentBillboardID, newColor);

			// Button text contents
			screen->getButton("isTransparent")->changeTextContent(isTransparent ? "Alpha: ON" : "Alpha: OFF");
		}
		else if (screen->getID() == "billboardEditorMenuAnimation")
		{
			// Temporary values
			int animationRowCount = _fe3d.billboardEntity_getSpriteAnimationRows(_currentBillboardID);
			int animationColumnCount = _fe3d.billboardEntity_getSpriteAnimationColumns(_currentBillboardID);
			int animationFramestep = _fe3d.billboardEntity_getSpriteAnimationFramestep(_currentBillboardID);

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					return;
				}
				else if (screen->getButton("animate")->isHovered())
				{
					_fe3d.billboardEntity_startSpriteAnimation(_currentBillboardID, -1);
				}
				else if (screen->getButton("rows")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("rows", "Rows", animationRowCount, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("columns")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("columns", "Columns", animationColumnCount, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("speed")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("speed", "Framestep", animationFramestep, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
			}

			// Update button hoverability
			bool playing = _fe3d.billboardEntity_isSpriteAnimationStarted(_currentBillboardID);
			screen->getButton("animate")->setHoverable(!playing && animationRowCount != 0 && animationColumnCount != 0);

			// Update value filling
			if (_gui.getGlobalScreen()->checkValueForm("rows", animationRowCount, { 0 }) ||
				_gui.getGlobalScreen()->checkValueForm("columns", animationColumnCount, { 0 }) ||
				_gui.getGlobalScreen()->checkValueForm("speed", animationFramestep, {}))
			{
				if (playing) // Only if animation is already playing
				{
					_fe3d.billboardEntity_stopSpriteAnimation(_currentBillboardID);
					_fe3d.billboardEntity_startSpriteAnimation(_currentBillboardID, -1);
				}
			}

			// Update animation values
			_fe3d.billboardEntity_setSpriteAnimationRows(_currentBillboardID, max(0, animationRowCount));
			_fe3d.billboardEntity_setSpriteAnimationColumns(_currentBillboardID, max(0, animationColumnCount));
			_fe3d.billboardEntity_setSpriteAnimationFramestep(_currentBillboardID, max(0, animationFramestep));
		}
		else if (screen->getID() == "billboardEditorMenuText")
		{
			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
					return;
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
							Logger::throwWarning("Invalid filepath, directory switching not allowed!");
						}
					}
				}
				else if (screen->getButton("color")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("colorR", "R", _fe3d.billboardEntity_getColor(_currentBillboardID).r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->createValueForm("colorG", "G", _fe3d.billboardEntity_getColor(_currentBillboardID).g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->createValueForm("colorB", "B", _fe3d.billboardEntity_getColor(_currentBillboardID).b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("content")->isHovered())
				{
					_gui.getGlobalScreen()->createValueForm("content", "Text content", _fe3d.billboardEntity_getTextContent(_currentBillboardID), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
			}

			// Updating buttons hoverability
			screen->getButton("color")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");
			screen->getButton("content")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");

			// Setting text color
			Vec3 newColor = _fe3d.billboardEntity_getColor(_currentBillboardID) * 255.0f;
			_gui.getGlobalScreen()->checkValueForm("colorR", newColor.r, {});
			_gui.getGlobalScreen()->checkValueForm("colorG", newColor.g, {});
			_gui.getGlobalScreen()->checkValueForm("colorB", newColor.b, {});
			newColor.r = clamp(newColor.r / 255.0f, 0.0f, 1.0f);
			newColor.g = clamp(newColor.g / 255.0f, 0.0f, 1.0f);
			newColor.b = clamp(newColor.b / 255.0f, 0.0f, 1.0f);
			_fe3d.billboardEntity_setColor(_currentBillboardID, newColor);

			// Updating text content
			string textContent = "";
			if (_gui.getGlobalScreen()->checkValueForm("content", textContent, {}))
			{
				_fe3d.misc_clearFontCache(_fe3d.billboardEntity_getFontPath(_currentBillboardID));
				_fe3d.misc_clearTextCache(textContent, _fe3d.billboardEntity_getFontPath(_currentBillboardID));
				_fe3d.billboardEntity_setTextContent(_currentBillboardID, textContent);
			}
		}
	}
}