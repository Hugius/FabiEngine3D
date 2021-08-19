#include "billboard_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void BillboardEditor::_updateAppearanceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "billboardEditorMenuAppearance")
	{
		// Temporary values
		auto isTransparent = _fe3d.billboardEntity_isTransparent(_currentBillboardID);
		auto lightness = _fe3d.billboardEntity_getLightness(_currentBillboardID);
		auto color = _fe3d.billboardEntity_getColor(_currentBillboardID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
				return;
			}
			else if (screen->getButton("texture")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\billboard_maps\\");

				// Validate target directory
				if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
				{
					Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
					return;
				}

				// Validate chosen file
				const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
				
				// Set diffuse map
				const string finalFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(finalFilePath);
				_fe3d.billboardEntity_setDiffuseMap(_currentBillboardID, finalFilePath);
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", lightness * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("isTransparent")->isHovered())
			{
				isTransparent = !isTransparent;
				_fe3d.billboardEntity_setTransparent(_currentBillboardID, isTransparent);
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness, {}))
		{
			lightness = max(0.0f, lightness / 100.0f);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorR", color.r, {}))
		{
			color.r = clamp(color.r / 255.0f, 0.0f, 1.0f);
			_fe3d.billboardEntity_setColor(_currentBillboardID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorG", color.g, {}))
		{
			color.g = clamp(color.g / 255.0f, 0.0f, 1.0f);
			_fe3d.billboardEntity_setColor(_currentBillboardID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorB", color.b, {}))
		{
			color.b = clamp(color.b / 255.0f, 0.0f, 1.0f);
			_fe3d.billboardEntity_setColor(_currentBillboardID, color);
		}

		// Update buttons hoverability
		screen->getButton("texture")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID).empty());
		screen->getButton("isTransparent")->setHoverable(_fe3d.billboardEntity_getFontPath(_currentBillboardID).empty());

		// Update button text contents
		screen->getButton("isTransparent")->changeTextContent(isTransparent ? "Alpha: ON" : "Alpha: OFF");
	}
}