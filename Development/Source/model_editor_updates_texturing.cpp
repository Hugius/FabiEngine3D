#include "model_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void ModelEditor::_updateTexturingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "modelEditorMenuTexturing")
	{
		// Temporary values
		auto textureRepeat = _fe3d.modelEntity_getTextureRepeat(_currentModelID, _currentPartID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_currentPartID = "";
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("partID")->getEntityID(), false);
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = Tools::getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			   filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
				return;
			}

			// Set diffuse map
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.modelEntity_setDiffuseMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = Tools::getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\emission_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			   filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
				return;
			}

			// Set emission map
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.modelEntity_setEmissionMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = Tools::getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\specular_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			   filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
				return;
			}

			// Set specular map
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.modelEntity_setSpecularMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectionMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = Tools::getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\reflection_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			   filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
				return;
			}

			// Set reflection map
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.modelEntity_setReflectionMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = Tools::getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\normal_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			   filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
				return;
			}

			// Set normal map
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.modelEntity_setNormalMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.modelEntity_setDiffuseMap(_currentModelID, _currentPartID, "");
			_fe3d.modelEntity_setEmissionMap(_currentModelID, _currentPartID, "");
			_fe3d.modelEntity_setSpecularMap(_currentModelID, _currentPartID, "");
			_fe3d.modelEntity_setReflectionMap(_currentModelID, _currentPartID, "");
			_fe3d.modelEntity_setNormalMap(_currentModelID, _currentPartID, "");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("textureRepeat", textureRepeat, {}))
		{
			_fe3d.modelEntity_setTextureRepeat(_currentModelID, _currentPartID, textureRepeat);
		}
	}
}