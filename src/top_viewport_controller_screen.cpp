#include "top_viewport_controller.hpp"
#include "tools.hpp"
#include "logger.hpp"

#include <fstream>
#include <shlobj.h>

using std::ofstream;

void TopViewportController::_updateProjectScreenManagement()
{
	const auto topScreen = _gui->getTopViewport()->getWindow("projectWindow")->getActiveScreen();
	const auto leftScreen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
	{
		if(topScreen->getButton("createProject")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createProject", "Create Project", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(topScreen->getButton("loadProject")->isHovered())
		{
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto projectDirectoryPath = (rootPath + "projects\\");

			if(Tools::isDirectoryExisting(projectDirectoryPath))
			{
				auto projectIds = Tools::getDirectoryNamesFromDirectory(projectDirectoryPath);

				_gui->getOverlay()->openChoiceForm("loadProject", "Load Project", CHOICE_FORM_POSITION, projectIds);
			}
			else
			{
				Logger::throwWarning("Directory `projects\\` does not exist");
			}
		}
		else if(topScreen->getButton("deleteProject")->isHovered())
		{
			_gui->getOverlay()->openAnswerForm("deleteProject", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(topScreen->getButton("closeWindow")->isHovered())
		{
			_gui->getOverlay()->openAnswerForm("closeWindow", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
		}
	}

	_updateProjectCreating();
	_updateProjectLoading();
	_updateProjectDeleting();
	_updateWindowClosing();

	const auto isInMainMenu = (leftScreen->getId() == "main");
	const auto isScriptStarted = _scriptExecutor->isStarted();

	topScreen->getButton("createProject")->setHoverable((!isScriptStarted && isInMainMenu), true);
	topScreen->getButton("loadProject")->setHoverable((!isScriptStarted && isInMainMenu), true);
	topScreen->getButton("deleteProject")->setHoverable((!isScriptStarted && isInMainMenu && !_currentProjectId.empty()), true);
}

void TopViewportController::_updateApplicationScreenManagement()
{
	const auto topScreen = _gui->getTopViewport()->getWindow("executionWindow")->getActiveScreen();
	const auto leftScreen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(_currentProjectId.empty())
	{
		topScreen->getButton("start")->setHoverable(false, true);
		topScreen->getButton("debug")->setHoverable(false, true);
		topScreen->getButton("restart")->setHoverable(false, true);
		topScreen->getButton("stop")->setHoverable(false, true);
	}
	else
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			if(topScreen->getButton("start")->isHovered())
			{
				_scriptEditor->loadScriptFiles(true);

				_scriptExecutor->start();
			}
			else if(topScreen->getButton("debug")->isHovered())
			{
				_scriptExecutor->update(true);
			}
			else if(topScreen->getButton("restart")->isHovered())
			{
				_scriptExecutor->stop();

				_scriptEditor->loadScriptFiles(true);

				_scriptExecutor->start();
			}
			else if(topScreen->getButton("stop")->isHovered())
			{
				_scriptExecutor->stop();
			}
		}

		const auto isInMainMenu = (leftScreen->getId() == "main");
		const auto isScriptEmpty = _script->isEmpty();
		const auto isScriptStarted = _scriptExecutor->isStarted();

		topScreen->getButton("start")->setHoverable((isInMainMenu && !isScriptEmpty && !isScriptStarted), true);
		topScreen->getButton("debug")->setHoverable((isInMainMenu && isScriptStarted), true);
		topScreen->getButton("restart")->setHoverable((isInMainMenu && isScriptStarted), true);
		topScreen->getButton("stop")->setHoverable((isInMainMenu && isScriptStarted), true);

		if(isInMainMenu && !isScriptStarted && isScriptEmpty)
		{
			_scriptEditor->loadScriptFiles(false);
		}

		_scriptExecutor->update(false);
	}
}

void TopViewportController::_updateExtraScreenManagement()
{
	const auto topScreen = _gui->getTopViewport()->getWindow("extraWindow")->getActiveScreen();
	const auto leftScreen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(_currentProjectId.empty())
	{
		topScreen->getButton("uncache")->setHoverable(false, true);
		topScreen->getButton("export")->setHoverable(false, true);
	}
	else
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && topScreen->getButton("uncache")->isHovered())
		{
			if(_currentProjectId.empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + _currentProjectId + "\\assets\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
			}
			else
			{
				const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "");

				if(!filePath.empty())
				{
					if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
					{
						Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
					}
					else
					{
						const auto finalFilePath = filePath.substr(rootPath.size());

						_fe3d->misc_clearMeshCache(finalFilePath);
						_fe3d->misc_clearImageCache(finalFilePath);
						_fe3d->misc_clearAudioCache(finalFilePath);
					}
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && topScreen->getButton("export")->isHovered())
		{
			const auto chosenDirectoryPath = Tools::chooseExplorerDirectory("");

			if(!chosenDirectoryPath.empty())
			{
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto exportDirectoryPath = (chosenDirectoryPath + "\\" + _currentProjectId + "\\");

				if(Tools::isDirectoryExisting(exportDirectoryPath))
				{
					Logger::throwWarning("Project already exported to that location");
				}
				else
				{
					bool hasFailed = false;

					if(!Tools::createDirectory(exportDirectoryPath))
					{
						hasFailed = true;
					}

					if(!Tools::createDirectory(exportDirectoryPath + "logo\\"))
					{
						hasFailed = true;
					}

					if(!Tools::createDirectory(exportDirectoryPath + "shaders\\"))
					{
						hasFailed = true;
					}

					if(!Tools::copyDirectory((rootPath + "binaries\\"), (exportDirectoryPath + "binaries\\")))
					{
						hasFailed = true;
					}

					if(!Tools::copyDirectory((rootPath + "engine\\shaders\\"), (exportDirectoryPath + "shaders\\")))
					{
						hasFailed = true;
					}

					if(!Tools::copyDirectory((rootPath + "projects\\" + _currentProjectId), exportDirectoryPath))
					{
						hasFailed = true;
					}

					if(!Tools::copyFile((rootPath + "engine\\assets\\image\\diffuse_map\\logo.tga"), (exportDirectoryPath + "logo\\logo.tga")))
					{
						hasFailed = true;
					}

					if(!Tools::renameFile((exportDirectoryPath + "binaries\\fe3d.exe"), (exportDirectoryPath + "binaries\\" + _currentProjectId + ".exe")))
					{
						hasFailed = true;
					}

					if(hasFailed)
					{
						Tools::deleteDirectory(exportDirectoryPath);

						Logger::throwWarning("Cannot export project");
					}
					else
					{
						const auto filePath = (exportDirectoryPath + "configuration.fe3d");

						auto file = ofstream(filePath);

						file << "window_title=\"My Game\"";
						file << endl;
						file << "window_width=100";
						file << endl;
						file << "window_height=100";

						file.close();

						Logger::throwInfo("Project exported");
					}
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && topScreen->getButton("documentation")->isHovered())
		{
			ShellExecute(0, 0, "https://github.com/Hugius/FabiEngine3D/blob/master/README.md", 0, 0, SW_SHOW);
		}

		const auto isInMainMenu = (leftScreen->getId() == "main");
		const auto isScriptStarted = _scriptExecutor->isStarted();

		topScreen->getButton("uncache")->setHoverable((!isScriptStarted && isInMainMenu), true);
		topScreen->getButton("export")->setHoverable((!isScriptStarted && isInMainMenu), true);
	}
}