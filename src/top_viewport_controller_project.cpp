#include "top_viewport_controller.hpp"
#include "tools.hpp"
#include "logger.hpp"

using std::ofstream;

void TopViewportController::_updateProjectCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createProject") && _gui->getOverlay()->isValueFormConfirmed())
	{
		const auto projectId = _gui->getOverlay()->getValueFormContent();
		const auto rootPath = Tools::getRootDirectoryPath();
		const auto projectDirectoryPath = (rootPath + "projects\\");
		const auto newProjectDirectoryPath = (projectDirectoryPath + projectId + "\\");

		if(!Tools::isDirectoryExisting(projectDirectoryPath))
		{
			Logger::throwWarning("Directory `projects\\` does not exist");

			return;
		}

		if(projectId.empty())
		{
			Logger::throwWarning("Project ID cannot be empty");

			return;
		}

		if(any_of(projectId.begin(), projectId.end(), isspace))
		{
			Logger::throwWarning("Project ID cannot contain any spaces");

			return;
		}

		if(any_of(projectId.begin(), projectId.end(), isupper))
		{
			Logger::throwWarning("Project ID cannot contain any capitals");

			return;
		}

		if(projectId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Project ID cannot contain any specials");

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
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\miscellaneous");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\miscellaneous\\flare_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\diffuse_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\emission_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\normal_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\reflection_map\\");
		Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\model\\refraction_map\\");
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
		Tools::createDirectory(newProjectDirectoryPath + "domain\\");
		Tools::createDirectory(newProjectDirectoryPath + "saves\\");
		Tools::createDirectory(newProjectDirectoryPath + "worlds\\");
		Tools::createDirectory(newProjectDirectoryPath + "worlds\\custom\\");
		Tools::createDirectory(newProjectDirectoryPath + "worlds\\editor\\");
		Tools::createDirectory(newProjectDirectoryPath + "scripts\\");

		auto aabbFile = ofstream(newProjectDirectoryPath + "domain\\aabb.fe3d");
		auto animation2dFile = ofstream(newProjectDirectoryPath + "domain\\animation2d.fe3d");
		auto animation3dFile = ofstream(newProjectDirectoryPath + "domain\\animation3d.fe3d");
		auto captorFile = ofstream(newProjectDirectoryPath + "domain\\captor.fe3d");
		auto modelFile = ofstream(newProjectDirectoryPath + "domain\\model.fe3d");
		auto pointlightFile = ofstream(newProjectDirectoryPath + "domain\\pointlight.fe3d");
		auto quad2dFile = ofstream(newProjectDirectoryPath + "domain\\quad2d.fe3d");
		auto quad3dFile = ofstream(newProjectDirectoryPath + "domain\\quad3d.fe3d");
		auto skyFile = ofstream(newProjectDirectoryPath + "domain\\sky.fe3d");
		auto sound2dFile = ofstream(newProjectDirectoryPath + "domain\\sound2d.fe3d");
		auto sound3dFile = ofstream(newProjectDirectoryPath + "domain\\sound3d.fe3d");
		auto spotlightFile = ofstream(newProjectDirectoryPath + "domain\\spotlight.fe3d");
		auto terrainFile = ofstream(newProjectDirectoryPath + "domain\\terrain.fe3d");
		auto text2dFile = ofstream(newProjectDirectoryPath + "domain\\text2d.fe3d");
		auto text3dFile = ofstream(newProjectDirectoryPath + "domain\\text3d.fe3d");
		auto waterFile = ofstream(newProjectDirectoryPath + "domain\\water.fe3d");

		animation2dFile.close();
		animation3dFile.close();
		captorFile.close();
		modelFile.close();
		pointlightFile.close();
		quad2dFile.close();
		quad3dFile.close();
		skyFile.close();
		sound2dFile.close();
		sound3dFile.close();
		spotlightFile.close();
		terrainFile.close();
		text2dFile.close();
		text3dFile.close();
		waterFile.close();

		_setProject(projectId);

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

		const auto skyImagePaths = _skyEditor->getImagePathsFromFile();
		const auto terrainImagePaths = _terrainEditor->getImagePathsFromFile();
		const auto waterImagePaths = _waterEditor->getImagePathsFromFile();
		const auto modelMeshPaths = _modelEditor->getMeshPathsFromFile();
		const auto modelImagePaths = _modelEditor->getImagePathsFromFile();
		const auto quad3dImagePaths = _quad3dEditor->getImagePathsFromFile();
		const auto quad2dImagePaths = _quad2dEditor->getImagePathsFromFile();
		const auto text3dImagePaths = _text3dEditor->getImagePathsFromFile();
		const auto text2dImagePaths = _text2dEditor->getImagePathsFromFile();
		const auto sound3dAudioPaths = _sound3dEditor->getAudioPathsFromFile();
		const auto sound2dAudioPaths = _sound2dEditor->getAudioPathsFromFile();

		vector<string> imagePaths = {};

		imagePaths.insert(imagePaths.end(), skyImagePaths.begin(), skyImagePaths.end());
		imagePaths.insert(imagePaths.end(), terrainImagePaths.begin(), terrainImagePaths.end());
		imagePaths.insert(imagePaths.end(), waterImagePaths.begin(), waterImagePaths.end());
		imagePaths.insert(imagePaths.end(), modelImagePaths.begin(), modelImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad3dImagePaths.begin(), quad3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad2dImagePaths.begin(), quad2dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text3dImagePaths.begin(), text3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text2dImagePaths.begin(), text2dImagePaths.end());

		vector<string> audioPaths = {};

		audioPaths.insert(audioPaths.end(), sound3dAudioPaths.begin(), sound3dAudioPaths.end());
		audioPaths.insert(audioPaths.end(), sound2dAudioPaths.begin(), sound2dAudioPaths.end());

		_fe3d->misc_cacheMeshes(modelMeshPaths, false);
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

			if(!Tools::isDirectoryExisting(directoryPath) || !Tools::deleteDirectory(directoryPath))
			{
				Logger::throwWarning("Cannot delete project");

				return;
			}

			Logger::throwInfo("Project \"" + _currentProjectId + "\" deleted");

			_setProject("");
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