#include "top_viewport_controller.hpp"
#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <fstream>
#include <shlobj.h>

using std::ofstream;

void TopViewportController::_updateProjectScreenManagement()
{
	auto topScreen = _gui->getTopViewport()->getWindow("projectWindow")->getActiveScreen();
	auto leftScreen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
	{
		if(topScreen->getButton("createProject")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createProject", "Create Project", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(topScreen->getButton("loadProject")->isHovered())
		{
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto projectDirectoryPath = (rootPath + "projects\\");

			if(Tools::isDirectoryExisting(projectDirectoryPath))
			{
				auto projectIds = Tools::getDirectoryNamesFromDirectory(projectDirectoryPath);

				_gui->getOverlay()->openChoiceForm("loadProject", "Load Project", fvec2(0.0f, 0.1f), projectIds);
			}
			else
			{
				Logger::throwWarning("Directory `projects\\` does not exist");
			}
		}
		else if(topScreen->getButton("deleteProject")->isHovered())
		{
			_gui->getOverlay()->openAnswerForm("deleteProject", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(topScreen->getButton("closeWindow")->isHovered())
		{
			_gui->getOverlay()->openAnswerForm("closeWindow", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
	}

	_updateProjectCreating();
	_updateProjectLoading();
	_updateProjectDeleting();
	_updateWindowClosing();

	const auto isInMainMenu = (leftScreen->getId() == "main");
	const auto isScriptStarted = _scriptExecutor->isStarted();

	topScreen->getButton("createProject")->setHoverable(!isScriptStarted && isInMainMenu);
	topScreen->getButton("loadProject")->setHoverable(!isScriptStarted && isInMainMenu);
	topScreen->getButton("deleteProject")->setHoverable(!isScriptStarted && isInMainMenu && !_currentProjectId.empty());
}

void TopViewportController::_updateApplicationScreenManagement()
{
	auto topScreen = _gui->getTopViewport()->getWindow("executionWindow")->getActiveScreen();
	auto leftScreen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(_currentProjectId.empty())
	{
		topScreen->getButton("start")->setHoverable(false);
		topScreen->getButton("pause")->setHoverable(false);
		topScreen->getButton("restart")->setHoverable(false);
		topScreen->getButton("stop")->setHoverable(false);
		topScreen->getButton("debug")->setHoverable(false);
	}
	else
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			if(topScreen->getButton("start")->isHovered())
			{
				if(_scriptExecutor->isStarted())
				{
					_scriptExecutor->resume();
				}
				else
				{
					_scriptEditor->loadScriptFiles(true);
					_scriptExecutor->start();
				}
			}
			else if(topScreen->getButton("pause")->isHovered())
			{
				_scriptExecutor->pause();
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
			else if(topScreen->getButton("debug")->isHovered())
			{
				_scriptExecutor->resume();
				_scriptExecutor->update(true);
				_scriptExecutor->pause();
			}
		}

		const auto isInMainMenu = (leftScreen->getId() == "main");
		const auto isScriptEmpty = _script->isEmpty();
		const auto isScriptStarted = _scriptExecutor->isStarted();
		const auto isScriptRunning = _scriptExecutor->isRunning();

		topScreen->getButton("start")->setHoverable(isInMainMenu && !isScriptEmpty && !isScriptRunning);
		topScreen->getButton("pause")->setHoverable(isInMainMenu && isScriptRunning);
		topScreen->getButton("restart")->setHoverable(isInMainMenu && isScriptStarted);
		topScreen->getButton("stop")->setHoverable(isInMainMenu && isScriptStarted);
		topScreen->getButton("debug")->setHoverable(isInMainMenu && isScriptStarted);

		if(isInMainMenu && !isScriptStarted && _script->isEmpty())
		{
			_scriptEditor->loadScriptFiles(false);
		}

		if(isScriptRunning)
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE))
			{
				_scriptExecutor->pause();
			}
		}

		_scriptExecutor->update(false);
	}
}

void TopViewportController::_updateMiscScreenManagement()
{
	auto screen = _gui->getTopViewport()->getWindow("miscellaneousWindow")->getActiveScreen();

	if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("uncache")->isHovered())
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
					const string finalFilePath = filePath.substr(rootPath.size());

					_fe3d->misc_clearMeshCache(finalFilePath);
					_fe3d->misc_clearImageCache(finalFilePath);
					_fe3d->misc_clearAudioCache(finalFilePath);
				}
			}
		}
	}
	else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("export")->isHovered())
	{
		const string chosenDirectoryPath = Tools::chooseExplorerDirectory("");

		if(!chosenDirectoryPath.empty())
		{
			const string rootPath = Tools::getRootDirectoryPath();
			const string exportDirectoryPath = (chosenDirectoryPath + "\\" + _currentProjectId + "\\");

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

					Logger::throwWarning("Project exportation failed");
				}
				else
				{
					const auto filePath = (exportDirectoryPath + "configuration.fe3d");

					auto file = ofstream(filePath);
					file << "window_title  = My Game";
					file << endl;
					file << "window_width  = 0.75";
					file << endl;
					file << "window_height = 0.75";
					file.close();
				}
			}
		}
	}
	else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("documentation")->isHovered())
	{
		ShellExecute(0, 0, "https://github.com/Hugius/FabiEngine3D/blob/master/README.md", 0, 0, SW_SHOW);
	}

	screen->getButton("uncache")->setHoverable(!_currentProjectId.empty() && !_scriptExecutor->isStarted() && (_gui->getLeftViewport()->getWindow("main")->getActiveScreen()->getId() == "main"));
	screen->getButton("export")->setHoverable(!_currentProjectId.empty() && !_scriptExecutor->isStarted() && (_gui->getLeftViewport()->getWindow("main")->getActiveScreen()->getId() == "main"));
}