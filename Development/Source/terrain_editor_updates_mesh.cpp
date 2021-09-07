#include "terrain_editor.hpp"
#include "logger.hpp"

void TerrainEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "terrainEditorMenuMesh")
	{
		// Temporary values
		float maxHeight = _fe3d.terrainEntity_getMaxHeight(_currentTerrainID);
		float uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
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
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setDiffuseMap(_currentTerrainID, newFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxHeight")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("maxHeight", "Max Height", maxHeight, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uvRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("maxHeight", maxHeight))
		{
			_fe3d.terrainEntity_setMaxHeight(_currentTerrainID, maxHeight);
		}
		if (_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat))
		{
			_fe3d.terrainEntity_setUvRepeat(_currentTerrainID, uvRepeat);
		}
	}
}