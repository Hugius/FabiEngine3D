#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateEffectsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "waterEditorMenuEffects")
	{
		// Temporary values
		bool isReflective = _fe3d.waterEntity_isReflective(_currentWaterID);
		bool isRefractive = _fe3d.waterEntity_isRefractive(_currentWaterID);
		bool isWaving = _fe3d.waterEntity_isWaving(_currentWaterID);
		bool isRippling = _fe3d.waterEntity_isRippling(_currentWaterID);
		bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(_currentWaterID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
				return;
			}
			else if (screen->getButton("dudvMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\dudv_maps\\");

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

				// Set DUDV map
				const string newFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(newFilePath);
				_fe3d.waterEntity_setDudvMap(_currentWaterID, newFilePath);
			}
			else if (screen->getButton("normalMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");

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

				// Set normal map
				const string newFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(newFilePath);
				_fe3d.waterEntity_setNormalMap(_currentWaterID, newFilePath);
			}
			else if (screen->getButton("displaceMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\displacement_maps\\");

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

				// Set displacement map
				const string newFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(newFilePath);
				_fe3d.waterEntity_setDisplacementMap(_currentWaterID, newFilePath);
			}
			else if (screen->getButton("isReflective")->isHovered())
			{
				isReflective = !isReflective;
				_fe3d.waterEntity_setReflective(_currentWaterID, isReflective);
			}
			else if (screen->getButton("isRefractive")->isHovered())
			{
				isRefractive = !isRefractive;
				_fe3d.waterEntity_setRefractive(_currentWaterID, isRefractive);
			}
			else if (screen->getButton("isWaving")->isHovered())
			{
				isWaving = !isWaving;
				_fe3d.waterEntity_setWaving(_currentWaterID, isWaving);
			}
			else if (screen->getButton("isRippling")->isHovered())
			{
				isRippling = !isRippling;
				_fe3d.waterEntity_setRippling(_currentWaterID, isRippling);
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				isSpecularLighted = !isSpecularLighted;
				_fe3d.waterEntity_setSpecularLighted(_currentWaterID, isSpecularLighted);
			}
		}

		// Update buttons hoverability
		screen->getButton("isRippling")->setHoverable(_fe3d.waterEntity_hasDudvMap(_currentWaterID));
		screen->getButton("isSpecular")->setHoverable(_fe3d.waterEntity_hasNormalMap(_currentWaterID));
		screen->getButton("isWaving")->setHoverable(_fe3d.waterEntity_hasDisplacementMap(_currentWaterID));

		// Update button text contents
		screen->getButton("isReflective")->changeTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		screen->getButton("isRefractive")->changeTextContent(isRefractive ? "Refractive: ON" : "Refractive: OFF");
		screen->getButton("isWaving")->changeTextContent(isWaving ? "Waving: ON" : "Waving: OFF");
		screen->getButton("isRippling")->changeTextContent(isRippling ? "Rippling: ON" : "Rippling: OFF");
		screen->getButton("isSpecular")->changeTextContent(isSpecularLighted ? "Specular: ON" : "Specular: OFF");
	}
}