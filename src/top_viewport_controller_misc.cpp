#include "top_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

const bool TopViewportController::isScriptStarted() const
{
	if(_currentProjectID.empty())
	{
		return false;
	}
	else
	{
		return _scriptEditor.getScriptExecutor().isStarted();
	}
}

const bool TopViewportController::isScriptRunning() const
{
	if(_currentProjectID.empty())
	{
		return false;
	}
	else
	{
		return _scriptEditor.getScriptExecutor().isRunning();
	}
}

void TopViewportController::_updateMiscellaneous()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("main");
	bool isHoverable = (_currentProjectID.empty()) ? false : !_scriptEditor.getScriptExecutor().isStarted();

	// Update buttons hoverability
	screen->getButton("settingsEditor")->setHoverable(isHoverable);
	screen->getButton("skyEditor")->setHoverable(isHoverable);
	screen->getButton("terrainEditor")->setHoverable(isHoverable);
	screen->getButton("waterEditor")->setHoverable(isHoverable);
	screen->getButton("modelEditor")->setHoverable(isHoverable);
	screen->getButton("billboardEditor")->setHoverable(isHoverable);
	screen->getButton("worldEditor")->setHoverable(isHoverable);
	screen->getButton("animation3dEditor")->setHoverable(isHoverable);
	screen->getButton("animation2dEditor")->setHoverable(isHoverable);
	screen->getButton("audioEditor")->setHoverable(isHoverable);
	screen->getButton("scriptEditor")->setHoverable(isHoverable);
}

void TopViewportController::_updateProjectCreating()
{
	if(_isCreatingProject)
	{
		// Temporary values
		string newProjectID;

		// Check if user filled in a new ID
		if(_gui.getGlobalScreen()->checkValueForm("newProjectID", newProjectID))
		{
			// Temporary values
			const string projectDirectoryPath = (Tools::getRootDirectoryPath() + "projects\\");
			const string newProjectDirectoryPath = (projectDirectoryPath + newProjectID + "\\");

			// Check if game directory exists
			if(!Tools::isDirectoryExisting(projectDirectoryPath))
			{
				Logger::throwWarning("Directory `projects\\` is missing!");
				return;
			}

			if(newProjectID.find(' ') != string::npos) // ID contains spaces
			{
				Logger::throwWarning("New project name cannot contain any spaces!");
				return;
			}
			else if(Tools::isDirectoryExisting(newProjectDirectoryPath)) // Project already exists
			{
				Logger::throwWarning("Project \"" + newProjectID + "\"" + " already exists!");
				return;
			}
			else if(std::any_of(newProjectID.begin(), newProjectID.end(), isupper)) // ID contains capitals
			{
				Logger::throwWarning("New project name cannot contain any capitals!");
				return;
			}
			else // Project not existing
			{
				// Generate new project directory
				Tools::createDirectory(newProjectDirectoryPath);

				// Generate project subdirectories
				Tools::createDirectory(newProjectDirectoryPath + "assets\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\audio\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\fonts\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\meshes\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\blend_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\cube_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\diffuse_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\displacement_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\dudv_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\emission_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\flare_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\height_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\image_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\normal_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\reflection_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\textures\\specular_maps\\");
				Tools::createDirectory(newProjectDirectoryPath + "data\\");
				Tools::createDirectory(newProjectDirectoryPath + "saves\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\custom\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\editor\\");
				Tools::createDirectory(newProjectDirectoryPath + "scripts\\");

				// Create new empty project files
				auto animation3dFile = ofstream(newProjectDirectoryPath + "data\\animation3d.fe3d");
				auto animation2dFile = ofstream(newProjectDirectoryPath + "data\\animation2d.fe3d");
				auto audioFile = ofstream(newProjectDirectoryPath + "data\\audio.fe3d");
				auto billboardFile = ofstream(newProjectDirectoryPath + "data\\billboard.fe3d");
				auto modelFile = ofstream(newProjectDirectoryPath + "data\\model.fe3d");
				auto settingsFile = ofstream(newProjectDirectoryPath + "data\\settings.fe3d");
				auto skyFile = ofstream(newProjectDirectoryPath + "data\\sky.fe3d");
				auto terrainFile = ofstream(newProjectDirectoryPath + "data\\terrain.fe3d");
				auto waterFile = ofstream(newProjectDirectoryPath + "data\\water.fe3d");
				animation3dFile.close();
				animation2dFile.close();
				audioFile.close();
				billboardFile.close();
				modelFile.close();
				settingsFile.close();
				skyFile.close();
				terrainFile.close();
				waterFile.close();

				// Load current project
				_currentProjectID = newProjectID;
				_applyProjectChange();

				// Create default settings
				_settingsEditor.loadDefaultSettings();
				_settingsEditor.saveSettingsToFile();

				// Logging
				Logger::throwInfo("New project \"" + _currentProjectID + "\" created!");

				// Miscellaneous
				_isCreatingProject = false;
			}
		}
	}
}

const bool TopViewportController::_prepareProjectChoosing(const string& title) const
{
	// Temporary values
	const string projectDirectoryPath = (Tools::getRootDirectoryPath() + "projects\\");

	// Check if game directory exists
	if(!Tools::isDirectoryExisting(projectDirectoryPath))
	{
		Logger::throwWarning("Directory `projects\\` is missing!");
		return false;
	}

	// Get all project names
	auto projectIDs = Tools::getDirectoriesFromDirectory(projectDirectoryPath);

	// Add buttons
	_gui.getGlobalScreen()->createChoiceForm("projectList", title, fvec2(0.0f, 0.1f), projectIDs);

	return true;
}

void TopViewportController::_updateProjectLoading()
{
	if(_isLoadingProject)
	{
		// Temporary values
		const string clickedButtonID = _gui.getGlobalScreen()->checkChoiceForm("projectList");
		const string projectDirectoryPath = string(Tools::getRootDirectoryPath() + "projects\\" + clickedButtonID + "\\");

		// Check if user clicked a project ID
		if(clickedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			// Check if project corrupted
			if(isProjectCorrupted(projectDirectoryPath))
			{
				Logger::throwWarning("Cannot load project: missing files/directories!");
				return;
			}

			// Load current project
			_currentProjectID = clickedButtonID;
			_applyProjectChange();

			// Load settings for this project
			_settingsEditor.loadSettingsFromFile();

			// Cache meshes
			_fe3d.misc_cacheMeshesMultiThreaded(_modelEditor.getAllMeshPathsFromFile());

			// Cache 2D textures
			vector<string> texturePaths2D;
			texturePaths2D.insert(texturePaths2D.end(),
								_terrainEditor.getAllTexturePathsFromFile().begin(),
								_terrainEditor.getAllTexturePathsFromFile().end());
			texturePaths2D.insert(texturePaths2D.end(),
								_waterEditor.getAllTexturePathsFromFile().begin(),
								_waterEditor.getAllTexturePathsFromFile().end());
			texturePaths2D.insert(texturePaths2D.end(),
								_modelEditor.getAllTexturePathsFromFile().begin(),
								_modelEditor.getAllTexturePathsFromFile().end());
			texturePaths2D.insert(texturePaths2D.end(),
								_billboardEditor.getAllTexturePathsFromFile().begin(),
								_billboardEditor.getAllTexturePathsFromFile().end());
			_fe3d.misc_cache2dTexturesMultiThreaded(texturePaths2D);

			// Cache 3D textures
			_fe3d.misc_cache3dTexturesMultiThreaded(_skyEditor.getAllTexturePathsFromFile());

			// Cache bitmaps
			_fe3d.misc_cacheBitmapsMultiThreaded(_terrainEditor.getAllBitmapPathsFromFile());

			// Cache fonts
			_fe3d.misc_cacheFontsMultiThreaded(_billboardEditor.getAllFontPathsFromFile());

			// Cache sounds
			_fe3d.misc_cacheSoundsMultiThreaded(_audioEditor.getAllAudioPathsFromFile());

			// Logging
			Logger::throwInfo("Existing project \"" + _currentProjectID + "\" loaded!");

			// Miscellaneous
			_isLoadingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_isLoadingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
	}
}

void TopViewportController::_updateProjectDeleting()
{
	if(_isDeletingProject)
	{
		// Temporary values
		static string chosenButtonID = "";
		string clickedButtonID = _gui.getGlobalScreen()->checkChoiceForm("projectList");

		// Check if user clicked a project ID
		if(clickedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
			chosenButtonID = clickedButtonID;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_isDeletingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Check if deleting currently opened project
			if(chosenButtonID == _currentProjectID)
			{
				// Unload current project
				_currentProjectID = "";
				_applyProjectChange();
			}

			// Check if project directory is still existing
			const string directoryPath = (Tools::getRootDirectoryPath() + "projects\\" + chosenButtonID);
			if(!Tools::isDirectoryExisting(directoryPath))
			{
				Logger::throwWarning("Cannot delete project: missing directory!");
				return;
			}

			// Delete project directory
			Tools::deleteDirectory(directoryPath);

			// Logging
			Logger::throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

			// Miscellaneous
			_isDeletingProject = false;
			chosenButtonID = "";
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingProject = false;
			chosenButtonID = "";
		}
	}
}

void TopViewportController::_applyProjectChange()
{
	// Change window title
	if(_currentProjectID.empty())
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D - " + _currentProjectID);
	}

	// Go back to main menu
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");

	// Unload settings editor
	if(_settingsEditor.isLoaded())
	{
		_settingsEditor.unload();
	}

	// Unload sky editor
	if(_skyEditor.isLoaded())
	{
		_skyEditor.unload();
	}

	// Unload terrain editor
	if(_terrainEditor.isLoaded())
	{
		_terrainEditor.unload();
	}

	// Unload water editor
	if(_waterEditor.isLoaded())
	{
		_waterEditor.unload();
	}

	// Unload model editor
	if(_modelEditor.isLoaded())
	{
		_modelEditor.unload();
	}

	// Unload billboard editor
	if(_billboardEditor.isLoaded())
	{
		_billboardEditor.unload();
	}

	// Unload 3d animation editor
	if(_animation3dEditor.isLoaded())
	{
		_animation3dEditor.unload();
	}

	// Unload 2D animation editor
	if(_animation2dEditor.isLoaded())
	{
		_animation2dEditor.unload();
	}

	// Unload audio editor
	if(_audioEditor.isLoaded())
	{
		_audioEditor.unload();
	}

	// Unload world editor
	if(_worldEditor.isLoaded())
	{
		_worldEditor.unload();
	}

	// Unload script editor
	if(_scriptEditor.isLoaded())
	{
		_scriptEditor.unload();
	}

	// Pass loaded project ID
	_settingsEditor.setCurrentProjectID(_currentProjectID);
	_skyEditor.setCurrentProjectID(_currentProjectID);
	_terrainEditor.setCurrentProjectID(_currentProjectID);
	_waterEditor.setCurrentProjectID(_currentProjectID);
	_modelEditor.setCurrentProjectID(_currentProjectID);
	_billboardEditor.setCurrentProjectID(_currentProjectID);
	_animation3dEditor.setCurrentProjectID(_currentProjectID);
	_animation2dEditor.setCurrentProjectID(_currentProjectID);
	_audioEditor.setCurrentProjectID(_currentProjectID);
	_worldEditor.setCurrentProjectID(_currentProjectID);
	_scriptEditor.setCurrentProjectID(_currentProjectID);
}

const bool TopViewportController::isProjectCorrupted(const string& projectDirectoryPath) const
{
	// Check if all default directories are still existing
	if(!Tools::isDirectoryExisting(projectDirectoryPath) ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "data") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "saves") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds\\custom") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds\\editor") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "scripts"))
	{
		return true;
	}

	// Check if all default files are still existing
	if(!Tools::isFileExisting(projectDirectoryPath + "data\\animation3d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\animation2d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\audio.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\billboard.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\model.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\settings.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\sky.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\terrain.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\water.fe3d"))
	{
		return true;
	}

	return false;
}

void TopViewportController::_saveCurrentProject()
{
	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("TopViewportController::_saveCurrentProject");
	}

	// Save everything
	_settingsEditor.saveSettingsToFile();
	_skyEditor.saveSkyEntitiesToFile();
	_terrainEditor.saveTerrainEntitiesToFile();
	_waterEditor.saveWaterEntitiesToFile();
	_modelEditor.saveModelEntitiesToFile();
	_billboardEditor.saveBillboardEntitiesToFile();
	_animation3dEditor.saveAnimationsToFile();
	_animation2dEditor.saveAnimationsToFile();
	_audioEditor.saveAudioEntitiesToFile();
	_worldEditor.saveEditorWorldToFile();
	_scriptEditor.saveScriptFiles();

	// Logging
	Logger::throwInfo("Project \"" + _currentProjectID + "\" saved!");
}