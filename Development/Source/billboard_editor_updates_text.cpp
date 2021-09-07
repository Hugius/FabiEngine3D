#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateTextMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "billboardEditorMenuText")
	{
		// Temporary values
		auto textContent = _fe3d.billboardEntity_getTextContent(_currentBillboardID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("font")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\fonts\\");

			// Validate target directory
			if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "TTF");
			if (filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
				filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
				return;
			}

			// Set font
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearFontCache(finalFilePath);
			_fe3d.misc_clearTextCache(textContent, _fe3d.billboardEntity_getFontPath(_currentBillboardID));
			_fe3d.billboardEntity_setFont(_currentBillboardID, finalFilePath);

			// Set default text
			if (textContent.empty())
			{
				_fe3d.billboardEntity_setTextContent(_currentBillboardID, "text");
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("content")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("content", "Text content", textContent, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("content", textContent, {}))
		{
			_fe3d.misc_clearFontCache(_fe3d.billboardEntity_getFontPath(_currentBillboardID));
			_fe3d.misc_clearTextCache(textContent, _fe3d.billboardEntity_getFontPath(_currentBillboardID));
			_fe3d.billboardEntity_setTextContent(_currentBillboardID, textContent);
		}

		// Update buttons hoverability
		screen->getButton("content")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID) != "");
	}
}