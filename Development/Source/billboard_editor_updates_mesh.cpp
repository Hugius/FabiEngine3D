#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "billboardEditorMenuMesh")
	{
		// Temporary values
		auto size = _fe3d.billboardEntity_getSize(_currentBillboardID);
		auto textContent = _fe3d.billboardEntity_getTextContent(_currentBillboardID);
		auto isText = _fe3d.billboardEntity_isText(_currentBillboardID);
		auto hasDiffuseMap = _fe3d.billboardEntity_hasDiffuseMap(_currentBillboardID);
		auto hasEmissionMap = _fe3d.billboardEntity_hasEmissionMap(_currentBillboardID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sizeX", "X", (size.x * 100.0f), Vec2(-0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeY", "Y", (size.y * 100.0f), Vec2(0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");

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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\emission_maps\\");

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

			// Set emission map
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.billboardEntity_setEmissionMap(_currentBillboardID, finalFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.billboardEntity_setDiffuseMap(_currentBillboardID, "");
			_fe3d.billboardEntity_setEmissionMap(_currentBillboardID, "");
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("sizeX", size.x, { 0.0f }))
		{
			size.x /= 100.0f;
			_fe3d.billboardEntity_setSize(_currentBillboardID, size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeY", size.y, { 0.0f }))
		{
			size.y /= 100.0f;
			_fe3d.billboardEntity_setSize(_currentBillboardID, size);
		}

		// Update buttons hoverability
		screen->getButton("font")->setHoverable(!hasDiffuseMap || isText);
		screen->getButton("diffuseMap")->setHoverable(!isText);
		screen->getButton("diffuseMap")->setHoverable(!isText);
		screen->getButton("clearMaps")->setHoverable((hasDiffuseMap && !isText) || hasEmissionMap);
	}
}