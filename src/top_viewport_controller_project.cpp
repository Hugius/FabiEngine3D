#include "top_viewport_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::ofstream;

void TopViewportController::_updateProjectCreating()
{
	if(_isCreatingProject)
	{
		string newProjectID;

		if(_gui.getOverlay()->checkValueForm("newProjectID", newProjectID))
		{
			const auto rootPath = Tools::getRootDirectoryPath();
			const string projectDirectoryPath = (rootPath + "projects\\");
			const string newProjectDirectoryPath = (projectDirectoryPath + newProjectID + "\\");

			if(!Tools::isDirectoryExisting(projectDirectoryPath))
			{
				Logger::throwWarning("Directory `projects\\` is missing!");
				return;
			}

			if(newProjectID.find(' ') != string::npos)
			{
				Logger::throwWarning("New project name cannot contain any spaces!");
				return;
			}
			else if(Tools::isDirectoryExisting(newProjectDirectoryPath))
			{
				Logger::throwWarning("Project \"" + newProjectID + "\"" + " already exists!");
				return;
			}
			else if(any_of(newProjectID.begin(), newProjectID.end(), isupper))
			{
				Logger::throwWarning("New project name cannot contain any capitals!");
				return;
			}
			else
			{
				Tools::createDirectory(newProjectDirectoryPath);

				Tools::createDirectory(newProjectDirectoryPath + "assets\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\audio\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\mesh\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\blend_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\cube_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\diffuse_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\displacement_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\dudv_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\emission_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\flare_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\font_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\height_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\normal_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\reflection_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\specular_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "data\\");
				Tools::createDirectory(newProjectDirectoryPath + "saves\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\custom\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\editor\\");
				Tools::createDirectory(newProjectDirectoryPath + "scripts\\");

				auto animation2dFile = ofstream(newProjectDirectoryPath + "data\\animation2d.fe3d");
				auto animation3dFile = ofstream(newProjectDirectoryPath + "data\\animation3d.fe3d");
				auto billboardFile = ofstream(newProjectDirectoryPath + "data\\billboard.fe3d");
				auto modelFile = ofstream(newProjectDirectoryPath + "data\\model.fe3d");
				auto quadFile = ofstream(newProjectDirectoryPath + "data\\quad.fe3d");
				auto settingsFile = ofstream(newProjectDirectoryPath + "data\\settings.fe3d");
				auto skyFile = ofstream(newProjectDirectoryPath + "data\\sky.fe3d");
				auto soundFile = ofstream(newProjectDirectoryPath + "data\\sound.fe3d");
				auto terrainFile = ofstream(newProjectDirectoryPath + "data\\terrain.fe3d");
				auto waterFile = ofstream(newProjectDirectoryPath + "data\\water.fe3d");
				animation2dFile.close();
				animation3dFile.close();
				billboardFile.close();
				quadFile.close();
				modelFile.close();
				settingsFile.close();
				skyFile.close();
				soundFile.close();
				terrainFile.close();
				waterFile.close();

				_currentProjectID = newProjectID;
				_applyProjectChange();

				Logger::throwInfo("New project \"" + _currentProjectID + "\" created!");

				_isCreatingProject = false;
			}
		}
	}
}

void TopViewportController::_updateProjectLoading()
{
	if(_isLoadingProject)
	{
		const auto rootPath = Tools::getRootDirectoryPath();
		const string clickedButtonID = _gui.getOverlay()->checkChoiceForm("projectList");
		const string projectDirectoryPath = string(rootPath + "projects\\" + clickedButtonID + "\\");

		if(!clickedButtonID.empty() && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(isProjectCorrupted(projectDirectoryPath))
			{
				Logger::throwWarning("Cannot load project: missing files/directories!");
				return;
			}

			_currentProjectID = clickedButtonID;
			_applyProjectChange();

			auto skyTexturePaths = _skyEditor.getTexturePathsFromFile();
			auto terrainImagePaths = _terrainEditor.getImagePathsFromFile();
			auto terrainTexturePaths = _terrainEditor.getTexturePathsFromFile();
			auto waterTexturePaths = _waterEditor.getTexturePathsFromFile();
			auto modelMeshPaths = _modelEditor.getMeshPathsFromFile();
			auto modelTexturePaths = _modelEditor.getTexturePathsFromFile();
			auto billboardTexturePaths = _billboardEditor.getTexturePathsFromFile();
			auto quadTexturePaths = _quadEditor.getTexturePathsFromFile();
			auto audioPaths = _soundEditor.getAudioPathsFromFile();

			_fe3d.misc_cacheMeshes(modelMeshPaths);

			_fe3d.misc_cacheImages(terrainImagePaths);

			vector<string> texturePaths2D;
			texturePaths2D.insert(texturePaths2D.end(), terrainTexturePaths.begin(), terrainTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), waterTexturePaths.begin(), waterTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), modelTexturePaths.begin(), modelTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), billboardTexturePaths.begin(), billboardTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), quadTexturePaths.begin(), quadTexturePaths.end());
			_fe3d.misc_cache2dTextures(texturePaths2D);

			_fe3d.misc_cache3dTextures(skyTexturePaths);

			_fe3d.misc_cacheAudios(audioPaths);

			Logger::throwInfo("Existing project \"" + _currentProjectID + "\" loaded!");

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
		static string chosenButtonID = "";
		string clickedButtonID = _gui.getOverlay()->checkChoiceForm("projectList");

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

		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			if(chosenButtonID == _currentProjectID)
			{
				_currentProjectID = "";
				_applyProjectChange();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string directoryPath = (rootPath + "projects\\" + chosenButtonID);
			if(!Tools::isDirectoryExisting(directoryPath))
			{
				Logger::throwWarning("Cannot delete project: missing directory!");
				return;
			}

			Tools::deleteDirectory(directoryPath);

			Logger::throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

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