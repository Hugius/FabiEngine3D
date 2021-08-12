#include "terrain_editor.hpp"
#include "logger.hpp"

using std::max;

void TerrainEditor::_updateBlendMapMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuBlendMap")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
				return;
			}
			else if (screen->getButton("blendMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\blend_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setBlendMap(_currentTerrainID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("red")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setDiffuseMapR(_currentTerrainID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("green")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setDiffuseMapG(_currentTerrainID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("blue")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setDiffuseMapB(_currentTerrainID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("redRepeat")->isHovered())
			{
				float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
				_gui.getGlobalScreen()->createValueForm("redRepeat", "Red Repeat", blendRepeatR, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("greenRepeat")->isHovered())
			{
				float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
				_gui.getGlobalScreen()->createValueForm("greenRepeat", "Green Repeat", blendRepeatG, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("blueRepeat")->isHovered())
			{
				float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
				_gui.getGlobalScreen()->createValueForm("blueRepeat", "Blue Repeat", blendRepeatB, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update value forms
		float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("redRepeat", blendRepeatR))
		{
			blendRepeatR = max(0.0f, blendRepeatR);
			_fe3d.terrainEntity_setBlendRepeatR(_currentTerrainID, blendRepeatR);
		}
		float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("greenRepeat", blendRepeatG))
		{
			blendRepeatG = max(0.0f, blendRepeatG);
			_fe3d.terrainEntity_setBlendRepeatG(_currentTerrainID, blendRepeatG);
		}
		float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("blueRepeat", blendRepeatB))
		{
			blendRepeatB = max(0.0f, blendRepeatB);
			_fe3d.terrainEntity_setBlendRepeatB(_currentTerrainID, blendRepeatB);
		}

		// Filling statuses
		auto hasBlendMap = _fe3d.terrainEntity_hasBlendMap(_currentTerrainID);
		auto hasDiffuseMapR = _fe3d.terrainEntity_hasDiffuseMapR(_currentTerrainID);
		auto hasDiffuseMapG = _fe3d.terrainEntity_hasDiffuseMapG(_currentTerrainID);
		auto hasDiffuseMapB = _fe3d.terrainEntity_hasDiffuseMapB(_currentTerrainID);

		// Update buttons hoverability
		screen->getButton("red")->setHoverable(hasBlendMap);
		screen->getButton("green")->setHoverable(hasBlendMap);
		screen->getButton("blue")->setHoverable(hasBlendMap);
		screen->getButton("redRepeat")->setHoverable(hasBlendMap && hasDiffuseMapR);
		screen->getButton("greenRepeat")->setHoverable(hasBlendMap && hasDiffuseMapG);
		screen->getButton("blueRepeat")->setHoverable(hasBlendMap && hasDiffuseMapB);
	}
}