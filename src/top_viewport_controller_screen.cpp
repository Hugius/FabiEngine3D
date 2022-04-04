#include "top_viewport_controller.hpp"
#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <fstream>

using std::ofstream;

void TopViewportController::_updateProjectScreenManagement()
{
	auto topScreen = _gui->getTopViewport()->getWindow("projectWindow")->getActiveScreen();
	auto leftScreen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if(topScreen->getButton("newProject")->isHovered())
		{
			_gui->getOverlay()->openValueForm("projectId", "Create Project", "", fvec2(0.0f, 0.1f), 10, true, true, false);
			_isCreatingProject = true;
		}
		else if(topScreen->getButton("loadProject")->isHovered())
		{
			if(_prepareProjectChoosing("Load Project"))
			{
				_isLoadingProject = true;
			}
		}
		else if(topScreen->getButton("saveProject")->isHovered())
		{
			_saveCurrentProject();
		}
		else if(topScreen->getButton("deleteProject")->isHovered())
		{
			if(_prepareProjectChoosing("Delete Project"))
			{
				_isDeletingProject = true;
			}
		}
		else if(topScreen->getButton("quitEngine")->isHovered())
		{
			if((!_currentProjectId.empty()) && (leftScreen->getId() != "main") && (leftScreen->getId() != "worldEditorMenuMain"))
			{
				_gui->getOverlay()->openAnswerForm("quit", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
			}
			else
			{
				_fe3d->application_stop();
			}
		}
	}

	_updateProjectCreating();
	_updateProjectLoading();
	_updateProjectDeleting();

	if(_gui->getOverlay()->getAnswerFormId() == "quit")
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_saveCurrentProject();
			_fe3d->application_stop();


		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->application_stop();


		}
	}

	topScreen->getButton("newProject")->setHoverable(!_scriptExecutor->isStarted());
	topScreen->getButton("loadProject")->setHoverable(!_scriptExecutor->isStarted());
	topScreen->getButton("saveProject")->setHoverable(!_currentProjectId.empty() && !_scriptExecutor->isStarted());
	topScreen->getButton("deleteProject")->setHoverable(!_scriptExecutor->isStarted());
}

void TopViewportController::_updateGameScreenManagement()
{
	auto screen = _gui->getTopViewport()->getWindow("executionWindow")->getActiveScreen();

	if(_currentProjectId.empty())
	{
		screen->getButton("start")->setHoverable(false);
		screen->getButton("pause")->setHoverable(false);
		screen->getButton("restart")->setHoverable(false);
		screen->getButton("stop")->setHoverable(false);
		screen->getButton("debug")->setHoverable(false);
	}
	else
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(screen->getButton("start")->isHovered())
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
			else if(screen->getButton("pause")->isHovered())
			{
				_scriptExecutor->pause();
			}
			else if(screen->getButton("restart")->isHovered())
			{
				_scriptExecutor->stop();
				_scriptEditor->loadScriptFiles(true);
				_scriptExecutor->start();
			}
			else if(screen->getButton("stop")->isHovered())
			{
				_scriptExecutor->stop();
			}
			else if(screen->getButton("debug")->isHovered())
			{
				_scriptExecutor->resume();
				_scriptExecutor->update(true);
				_scriptExecutor->pause();
			}
		}

		static bool wasInMainMenu = false;
		const bool isInMainMenu = (_gui->getLeftViewport()->getWindow("main")->getActiveScreen()->getId() == "main");
		screen->getButton("start")->setHoverable(isInMainMenu && !_script->isEmpty() && !isScriptRunning());
		screen->getButton("pause")->setHoverable(isInMainMenu && isScriptRunning() && !_fe3d->server_isRunning());
		screen->getButton("restart")->setHoverable(isInMainMenu && _scriptExecutor->isStarted());
		screen->getButton("stop")->setHoverable(isInMainMenu && _scriptExecutor->isStarted());
		screen->getButton("debug")->setHoverable(isInMainMenu && _scriptExecutor->isStarted());

		const bool cameIntoMainMenu = (!wasInMainMenu && isInMainMenu);
		if(cameIntoMainMenu || (isInMainMenu && !isScriptStarted() && ((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0)))
		{
			_scriptEditor->loadScriptFiles(false);
		}
		wasInMainMenu = isInMainMenu;

		if(_scriptExecutor->isRunning())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if(_fe3d->server_isRunning())
				{
					_scriptExecutor->stop();
				}
				else
				{
					_scriptExecutor->pause();
				}
			}
		}

		_scriptExecutor->update(false);
	}
}

void TopViewportController::_updateMiscScreenManagement()
{
	auto screen = _gui->getTopViewport()->getWindow("miscellaneousWindow")->getActiveScreen();

	if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uncache")->isHovered())
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
	else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("export")->isHovered())
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
					file << "window_size       = 0.75" << endl;
					file << "window_fullscreen = false" << endl;
					file << "window_borderless = false" << endl;
					file << "window_title      = MyGame";
					file.close();
				}
			}
		}
	}
	else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("documentation")->isHovered())
	{
		ShellExecute(0, 0, "https://github.com/Hugius/FabiEngine3D/blob/master/README.md", 0, 0, SW_SHOW);
	}

	screen->getButton("uncache")->setHoverable(!_currentProjectId.empty() && !_scriptExecutor->isStarted() && (_gui->getLeftViewport()->getWindow("main")->getActiveScreen()->getId() == "main"));
	screen->getButton("export")->setHoverable(!_currentProjectId.empty() && !_scriptExecutor->isStarted() && (_gui->getLeftViewport()->getWindow("main")->getActiveScreen()->getId() == "main"));
}