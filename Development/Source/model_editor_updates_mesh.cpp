#include "model_editor.hpp"
#include "logger.hpp"

void ModelEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuMesh")
	{
		// Temporary values
		auto size = _fe3d.modelEntity_getSize(_currentModelID, "");
		auto isMultiParted = _fe3d.modelEntity_isMultiParted(_currentModelID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sizeX", "X", (size.x * 100.0f), Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeY", "Y", (size.y * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeZ", "Z", (size.z * 100.0f), Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			auto lambda = [this]()
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
				_fe3d.modelEntity_setDiffuseMap(_currentModelID, _currentPartID, finalFilePath);

				// Miscellaneous
				_currentPartID = "";
			};
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			auto lambda = [this]()
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
				_fe3d.modelEntity_setEmissionMap(_currentModelID, _currentPartID, finalFilePath);

				// Miscellaneous
				_currentPartID = "";
			};
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularMap")->isHovered())
		{
			auto lambda = [this]()
			{
				// Get the chosen filename
				const auto rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\specular_maps\\");

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

				// Set specular map
				const string finalFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(finalFilePath);
				_fe3d.modelEntity_setSpecularMap(_currentModelID, _currentPartID, finalFilePath);

				// Miscellaneous
				_currentPartID = "";
			};
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectionMap")->isHovered())
		{
			auto lambda = [this]()
			{
				// Get the chosen filename
				const auto rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\reflection_maps\\");

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

				// Set reflection map
				const string finalFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(finalFilePath);
				_fe3d.modelEntity_setReflectionMap(_currentModelID, _currentPartID, finalFilePath);

				// Miscellaneous
				_currentPartID = "";
			};
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			auto lambda = [this]()
			{
				// Get the chosen filename
				const auto rootDirectory = _fe3d.misc_getRootDirectory();
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
				const string finalFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(finalFilePath);
				_fe3d.modelEntity_setNormalMap(_currentModelID, _currentPartID, finalFilePath);

				// Miscellaneous
				_currentPartID = "";
			};
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			auto lambda = [this]()
			{
				_fe3d.modelEntity_setDiffuseMap(_currentModelID, _currentPartID, "");
				_fe3d.modelEntity_setEmissionMap(_currentModelID, _currentPartID, "");
				_fe3d.modelEntity_setSpecularMap(_currentModelID, _currentPartID, "");
				_fe3d.modelEntity_setReflectionMap(_currentModelID, _currentPartID, "");
				_fe3d.modelEntity_setNormalMap(_currentModelID, _currentPartID, "");
				_currentPartID = "";
			};
			isMultiParted ? _preparePartChoosing(lambda) : lambda();
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d.modelEntity_setSize(_currentModelID, "", size);
		}
	}
}