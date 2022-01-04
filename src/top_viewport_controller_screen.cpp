#include "top_viewport_controller.hpp"
#include "tools.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <fstream>

using std::ofstream;

void TopViewportController::_updateProjectScreenManagement()
{
	auto topScreen = _gui.getViewport("top")->getWindow("projectWindow")->getActiveScreen();
	auto leftScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if(topScreen->getButton("newProject")->isHovered())
		{
			_gui.getOverlay()->createValueForm("newProjectID", "Create Project", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
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
			if((!_currentProjectID.empty()) && (leftScreen->getID() != "main") && (leftScreen->getID() != "worldEditorMenuMain"))
			{
				_gui.getOverlay()->createAnswerForm("quit", "Save Changes?", fvec2(0.0f, 0.25f));
			}
			else
			{
				_fe3d.application_stop();
			}
		}
	}

	_updateProjectCreating();
	_updateProjectLoading();
	_updateProjectDeleting();

	if(_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && (leftScreen->getID() == "main") && !_gui.getOverlay()->isFocused())
	{
		if(!_scriptEditor.getScriptExecutor().isStarted())
		{
			_fe3d.application_stop();
		}
	}

	if(_gui.getOverlay()->isAnswerFormConfirmed("quit"))
	{
		_saveCurrentProject();
		_fe3d.application_stop();
	}
	if(_gui.getOverlay()->isAnswerFormDenied("quit"))
	{
		_fe3d.application_stop();
	}

	topScreen->getButton("newProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
	topScreen->getButton("loadProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
	topScreen->getButton("saveProject")->setHoverable(!_currentProjectID.empty() && !_scriptEditor.getScriptExecutor().isStarted());
	topScreen->getButton("deleteProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
}

void TopViewportController::_updateGameScreenManagement()
{
	auto screen = _gui.getViewport("top")->getWindow("executionWindow")->getActiveScreen();

	if(_currentProjectID.empty())
	{
		screen->getButton("start")->setHoverable(false);
		screen->getButton("pause")->setHoverable(false);
		screen->getButton("restart")->setHoverable(false);
		screen->getButton("stop")->setHoverable(false);
		screen->getButton("debug")->setHoverable(false);
	}
	else
	{
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(screen->getButton("start")->isHovered())
			{
				if(_scriptEditor.getScriptExecutor().isStarted())
				{
					_scriptEditor.getScriptExecutor().resume();
				}
				else
				{
					_scriptEditor.loadScriptFiles(true);
					_scriptEditor.getScriptExecutor().load();
				}
			}
			else if(screen->getButton("pause")->isHovered())
			{
				_scriptEditor.getScriptExecutor().pause();
			}
			else if(screen->getButton("restart")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
				_scriptEditor.loadScriptFiles(true);
				_scriptEditor.getScriptExecutor().load();
			}
			else if(screen->getButton("stop")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
			}
			else if(screen->getButton("debug")->isHovered())
			{
				_scriptEditor.getScriptExecutor().resume();
				_scriptEditor.getScriptExecutor().update(true);
				_scriptEditor.getScriptExecutor().pause();
			}
		}

		static bool wasInMainMenu = false;
		bool isInMainMenu = (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main");
		screen->getButton("start")->setHoverable(isInMainMenu && !_scriptEditor.getScriptExecutor().isScriptEmpty() && !isScriptRunning());
		screen->getButton("pause")->setHoverable(isInMainMenu && isScriptRunning() && !_fe3d.server_isRunning());
		screen->getButton("restart")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		screen->getButton("stop")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		screen->getButton("debug")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());

		bool cameIntoMenu = (!wasInMainMenu && isInMainMenu);
		if(cameIntoMenu || (isInMainMenu && !isScriptStarted() && _fe3d.misc_checkInterval(Config::UPDATES_PER_SECOND)))
		{
			_scriptEditor.loadScriptFiles(false);
		}
		wasInMainMenu = isInMainMenu;

		if(_scriptEditor.getScriptExecutor().isRunning())
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if(_fe3d.server_isRunning())
				{
					_scriptEditor.getScriptExecutor().unload();
				}
				else
				{
					_scriptEditor.getScriptExecutor().pause();
				}
			}
		}

		_scriptEditor.getScriptExecutor().update(false);
	}
}

void TopViewportController::_updateMiscScreenManagement()
{
	auto screen = _gui.getViewport("top")->getWindow("miscellaneousWindow")->getActiveScreen();

	if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uncache")->isHovered())
	{
		if(_currentProjectID.empty())
		{
			Logger::throwError("TopViewportController::_updateMiscScreenManagement");
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
			return;
		}

		const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "");
		if(filePath.empty())
		{
			return;
		}

		if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
		   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
			return;
		}

		const string newFilePath = filePath.substr(rootPath.size());
		_fe3d.misc_clearMeshCache(newFilePath);
		_fe3d.misc_clearImageCache(newFilePath);
		_fe3d.misc_clearAudioCache(newFilePath);
	}
	else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("export")->isHovered())
	{
		const string chosenDirectoryPath = Tools::chooseExplorerDirectory("");
		if(chosenDirectoryPath.empty())
		{
			return;
		}

		const string rootPath = Tools::getRootDirectoryPath();
		const string exportDirectoryPath = string(chosenDirectoryPath + "\\" + _currentProjectID + "\\");

		if(Tools::isDirectoryExisting(exportDirectoryPath))
		{
			Logger::throwWarning("Project already exported to that location!");
		}
		else
		{
			Tools::createDirectory(exportDirectoryPath);

			Tools::copyDirectory(string(rootPath + "binaries"), string(exportDirectoryPath + "binaries"));
			Tools::copyDirectory(string(rootPath + "engine"), string(exportDirectoryPath + "engine"));
			Tools::copyDirectory(string(rootPath + "projects\\" + _currentProjectID), exportDirectoryPath);

			auto oldPath = string(exportDirectoryPath + "binaries\\fe3d.exe");
			auto newPath = string(exportDirectoryPath + "binaries\\" + _currentProjectID + ".exe");
			Tools::renameFile(oldPath, newPath);

			const auto filePath = string(exportDirectoryPath + "config.fe3d");
			auto file = ofstream(filePath);
			file << "window_size			= 0.75" << endl;
			file << "window_fullscreen      = false" << endl;
			file << "window_borderless      = false" << endl;
			file << "window_title           = MyGame";
			file.close();
		}
	}
	else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("docs")->isHovered())
	{
		ShellExecute(0, 0, "https://github.com/ConsolePeasant92/FabiEngine3D/blob/master/README.md", 0, 0, SW_SHOW);
	}

	screen->getButton("uncache")->setHoverable(!_currentProjectID.empty() && !_scriptEditor.getScriptExecutor().isStarted());
	screen->getButton("export")->setHoverable(!_currentProjectID.empty());
}