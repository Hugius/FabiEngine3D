#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateTextMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "billboardEditorMenuText")
	{
		// Temporary values
		auto textContent = _fe3d.billboardEntity_getTextContent(_currentBillboardID);

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
						_fe3d.misc_clearTextCache(textContent, _fe3d.billboardEntity_getFontPath(_currentBillboardID));
						_fe3d.billboardEntity_setFont(_currentBillboardID, newFilePath);

						// Set default text
						if (textContent.empty())
						{
							_fe3d.billboardEntity_setTextContent(_currentBillboardID, "text");
						}
					}
					else
					{
						Logger::throwWarning("Invalid filepath: directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("content")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("content", "Text content", textContent, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
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