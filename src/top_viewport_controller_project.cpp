#include "top_viewport_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::ofstream;

void TopViewportController::_updateProjectCreating()
{
	if(_isCreatingProject)
	{
		// Temporary values
		string newProjectID;

		// Check if user filled in a new ID
		if(_gui.getOverlay()->checkValueForm("newProjectID", newProjectID))
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
			else if(any_of(newProjectID.begin(), newProjectID.end(), isupper)) // ID contains capitals
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
				Tools::createDirectory(newProjectDirectoryPath + "assets\\font\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\mesh\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\blend_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\cube_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\diffuse_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\displacement_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\dudv_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\emission_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\flare_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\height_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\normal_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\reflection_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\texture\\specular_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "data\\");
				Tools::createDirectory(newProjectDirectoryPath + "saves\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\custom\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\editor\\");
				Tools::createDirectory(newProjectDirectoryPath + "scripts\\");

				// Create new empty project files
				auto animation2dFile = ofstream(newProjectDirectoryPath + "data\\animation2d.fe3d");
				auto animation3dFile = ofstream(newProjectDirectoryPath + "data\\animation3d.fe3d");
				auto billboardFile = ofstream(newProjectDirectoryPath + "data\\billboard.fe3d");
				auto imageFile = ofstream(newProjectDirectoryPath + "data\\image.fe3d");
				auto modelFile = ofstream(newProjectDirectoryPath + "data\\model.fe3d");
				auto settingsFile = ofstream(newProjectDirectoryPath + "data\\settings.fe3d");
				auto skyFile = ofstream(newProjectDirectoryPath + "data\\sky.fe3d");
				auto soundFile = ofstream(newProjectDirectoryPath + "data\\sound.fe3d");
				auto terrainFile = ofstream(newProjectDirectoryPath + "data\\terrain.fe3d");
				auto waterFile = ofstream(newProjectDirectoryPath + "data\\water.fe3d");
				animation2dFile.close();
				animation3dFile.close();
				billboardFile.close();
				imageFile.close();
				modelFile.close();
				settingsFile.close();
				skyFile.close();
				soundFile.close();
				terrainFile.close();
				waterFile.close();

				// Load current project
				_currentProjectID = newProjectID;
				_applyProjectChange();

				// Logging
				Logger::throwInfo("New project \"" + _currentProjectID + "\" created!");

				// Miscellaneous
				_isCreatingProject = false;
			}
		}
	}
}

void TopViewportController::_updateProjectLoading()
{
	if(_isLoadingProject)
	{
		// Temporary values
		const string clickedButtonID = _gui.getOverlay()->checkChoiceForm("projectList");
		const string projectDirectoryPath = string(Tools::getRootDirectoryPath() + "projects\\" + clickedButtonID + "\\");

		// Check if user clicked a project ID
		if(!clickedButtonID.empty() && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
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

			// Gather file paths
			auto skyTexturePaths = _skyEditor.getTexturePathsFromFile();
			auto terrainTexturePaths = _terrainEditor.getTexturePathsFromFile();
			auto terrainBitmapPaths = _terrainEditor.getBitmapPathsFromFile();
			auto waterTexturePaths = _waterEditor.getTexturePathsFromFile();
			auto modelMeshPaths = _modelEditor.getMeshPathsFromFile();
			auto modelTexturePaths = _modelEditor.getTexturePathsFromFile();
			auto billboardTexturePaths = _billboardEditor.getTexturePathsFromFile();
			auto billboardFontPaths = _billboardEditor.getFontPathsFromFile();
			auto imageTexturePaths = _imageEditor.getTexturePathsFromFile();
			auto audioPaths = _soundEditor.getAudioPathsFromFile();

			// Cache meshes
			_fe3d.misc_cacheMeshes(modelMeshPaths);

			// Cache 2D textures
			vector<string> texturePaths2D;
			texturePaths2D.insert(texturePaths2D.end(), terrainTexturePaths.begin(), terrainTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), waterTexturePaths.begin(), waterTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), modelTexturePaths.begin(), modelTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), billboardTexturePaths.begin(), billboardTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), imageTexturePaths.begin(), imageTexturePaths.end());
			_fe3d.misc_cache2dTextures(texturePaths2D);

			// Cache 3D textures
			_fe3d.misc_cache3dTextures(skyTexturePaths);

			// Cache bitmaps
			_fe3d.misc_cacheBitmaps(terrainBitmapPaths);

			// Cache fonts
			_fe3d.misc_cacheFonts(billboardFontPaths);

			// Cache audios
			_fe3d.misc_cacheAudios(audioPaths);

			// Logging
			Logger::throwInfo("Existing project \"" + _currentProjectID + "\" loaded!");

			// Miscellaneous
			_isLoadingProject = false;
			_gui.getOverlay()->deleteChoiceForm("projectList");
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("projectList"))
		{
			_isLoadingProject = false;
			_gui.getOverlay()->deleteChoiceForm("projectList");
		}
	}
}

void TopViewportController::_updateProjectDeleting()
{
	if(_isDeletingProject)
	{
		// Temporary values
		static string chosenButtonID = "";
		string clickedButtonID = _gui.getOverlay()->checkChoiceForm("projectList");

		// Check if user clicked a project ID
		if(!clickedButtonID.empty() && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
			chosenButtonID = clickedButtonID;
			_gui.getOverlay()->deleteChoiceForm("projectList");
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("projectList"))
		{
			_isDeletingProject = false;
			_gui.getOverlay()->deleteChoiceForm("projectList");
		}

		// Update answer forms
		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
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
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingProject = false;
			chosenButtonID = "";
		}
	}
}