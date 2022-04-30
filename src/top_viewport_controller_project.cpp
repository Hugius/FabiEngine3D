#include "top_viewport_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::ofstream;

void TopViewportController::_updateProjectCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createProject") && _gui->getOverlay()->isValueFormConfirmed())
	{
		const auto newProjectId = _gui->getOverlay()->getValueFormContent();
		const auto rootPath = Tools::getRootDirectoryPath();
		const string projectDirectoryPath = (rootPath + "projects\\");
		const string newProjectDirectoryPath = (projectDirectoryPath + newProjectId + "\\");

		if(!Tools::isDirectoryExisting(projectDirectoryPath))
		{
			Logger::throwWarning("Directory `projects\\` does not exist");

			return;
		}

		if(newProjectId.empty())
		{
			Logger::throwWarning("Project ID cannot be empty");

			return;
		}

		if(any_of(newProjectId.begin(), newProjectId.end(), isspace))
		{
			Logger::throwWarning("Project ID cannot contain any spaces");

			return;
		}

		if(any_of(newProjectId.begin(), newProjectId.end(), isupper))
		{
			Logger::throwWarning("Project ID cannot contain any capitals");

			return;
		}

		if(Tools::isDirectoryExisting(newProjectDirectoryPath))
		{
			Logger::throwWarning("Project already exists");

			return;
		}

		Tools::createDirectory(newProjectDirectoryPath);
		Tools::createDirectory(newProjectDirectoryPath + "assets\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\audio\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\misc");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\misc\\flare_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\diffuse_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\emission_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\normal_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\reflection_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\specular_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\quad2d\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\quad2d\\diffuse_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\quad3d\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\quad3d\\diffuse_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\quad3d\\emission_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\sky\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\sky\\cube_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\terrain\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\terrain\\blend_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\terrain\\diffuse_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\terrain\\height_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\terrain\\normal_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\text2d\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\text2d\\font_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\text3d\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\text3d\\font_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\water\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\water\\dudv_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\water\\height_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\water\\normal_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\mesh\\");
		Tools::createDirectory(newProjectDirectoryPath + "data\\");
		Tools::createDirectory(newProjectDirectoryPath + "saves\\");
		Tools::createDirectory(newProjectDirectoryPath + "worlds\\");
		Tools::createDirectory(newProjectDirectoryPath + "worlds\\custom\\");
		Tools::createDirectory(newProjectDirectoryPath + "worlds\\editor\\");
		Tools::createDirectory(newProjectDirectoryPath + "scripts\\");

		auto animation2dFile = ofstream(newProjectDirectoryPath + "data\\animation2d.fe3d");
		auto animation3dFile = ofstream(newProjectDirectoryPath + "data\\animation3d.fe3d");
		auto modelFile = ofstream(newProjectDirectoryPath + "data\\model.fe3d");
		auto quad2dFile = ofstream(newProjectDirectoryPath + "data\\quad2d.fe3d");
		auto quad3dFile = ofstream(newProjectDirectoryPath + "data\\quad3d.fe3d");
		auto skyFile = ofstream(newProjectDirectoryPath + "data\\sky.fe3d");
		auto sound2dFile = ofstream(newProjectDirectoryPath + "data\\sound2d.fe3d");
		auto terrainFile = ofstream(newProjectDirectoryPath + "data\\terrain.fe3d");
		auto text2dFile = ofstream(newProjectDirectoryPath + "data\\text2d.fe3d");
		auto text3dFile = ofstream(newProjectDirectoryPath + "data\\text3d.fe3d");
		auto waterFile = ofstream(newProjectDirectoryPath + "data\\water.fe3d");
		animation2dFile.close();
		animation3dFile.close();
		modelFile.close();
		quad2dFile.close();
		quad3dFile.close();
		skyFile.close();
		sound2dFile.close();
		terrainFile.close();
		text2dFile.close();
		text3dFile.close();
		waterFile.close();

		_setProject(newProjectId);

		Logger::throwInfo("Project \"" + _currentProjectId + "\" created");
	}
}

void TopViewportController::_updateProjectLoading()
{
	if((_gui->getOverlay()->getChoiceFormId() == "loadProject") && _gui->getOverlay()->isChoiceFormConfirmed())
	{
		const auto rootPath = Tools::getRootDirectoryPath();
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();
		const auto projectDirectoryPath = (rootPath + "projects\\" + selectedOptionId + "\\");

		if(isProjectCorrupted(projectDirectoryPath))
		{
			return;
		}

		_setProject(selectedOptionId);

		auto skyImagePaths = _skyEditor->getImagePathsFromFile();
		auto terrainImagePaths = _terrainEditor->getImagePathsFromFile();
		auto waterImagePaths = _waterEditor->getImagePathsFromFile();
		auto modelMeshPaths = _modelEditor->getMeshPathsFromFile();
		auto modelImagePaths = _modelEditor->getImagePathsFromFile();
		auto quad3dImagePaths = _quad3dEditor->getImagePathsFromFile();
		auto text3dImagePaths = _text3dEditor->getImagePathsFromFile();
		auto quad2dImagePaths = _quad2dEditor->getImagePathsFromFile();
		auto text2dImagePaths = _text2dEditor->getImagePathsFromFile();
		auto audioPaths = _sound2dEditor->getAudioPathsFromFile();

		_fe3d->misc_cacheMeshes(modelMeshPaths, false);

		vector<string> imagePaths;
		imagePaths.insert(imagePaths.end(), skyImagePaths.begin(), skyImagePaths.end());
		imagePaths.insert(imagePaths.end(), terrainImagePaths.begin(), terrainImagePaths.end());
		imagePaths.insert(imagePaths.end(), waterImagePaths.begin(), waterImagePaths.end());
		imagePaths.insert(imagePaths.end(), modelImagePaths.begin(), modelImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad3dImagePaths.begin(), quad3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text3dImagePaths.begin(), text3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad2dImagePaths.begin(), quad2dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text2dImagePaths.begin(), text2dImagePaths.end());
		_fe3d->misc_cacheImages(imagePaths, false);

		_fe3d->misc_cacheAudios(audioPaths, false);

		Logger::throwInfo("Project \"" + _currentProjectId + "\" loaded");
	}
}

void TopViewportController::_updateProjectDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteProject") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + "projects\\" + _currentProjectId);

			if(!Tools::isDirectoryExisting(directoryPath))
			{
				Logger::throwWarning("Project does not exist");

				return;
			}

			if(!Tools::deleteDirectory(directoryPath))
			{
				Logger::throwWarning("Project deletion failed");

				return;
			}

			_setProject("");

			Logger::throwInfo("Project \"" + _currentProjectId + "\" deleted");
		}
	}
}

void TopViewportController::_updateWindowClosing()
{
	if((_gui->getOverlay()->getAnswerFormId() == "closeWindow") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->application_stop();
		}
	}
}