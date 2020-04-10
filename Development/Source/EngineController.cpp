#include "EngineController.hpp"

EngineController::EngineController() :
	_gui(make_shared<EngineGuiManager>(*this))
{

}

EngineController::~EngineController()
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	_gui->load();
}

void EngineController::FE3D_CONTROLLER_UPDATE(float delta)
{
	_delta = delta;

	_gui->update(delta);

	_updateGuiInteraction();
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{
	_gui->unload();
}

void EngineController::_updateGuiInteraction()
{
	auto vp = _gui->getViewport("topViewport");

	// Getting hovered button
	string hoveredItemID = vp->getWindow("mainWindow")->getActiveScreen()->getHoveredItemID();

	// Check if LMB pressed
	if (input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (hoveredItemID == "newProject")
		{
			if (!_creatingProject)
			{
				_gui->getGlobalScreen()->addTextfield("newProjectName", vec2(-0.25f, 0.05f), vec2(0.5f, 0.1f), "Enter project name:", vec3(1.0f));
				_gui->getGlobalScreen()->addWritefield("newProjectName", vec2(-0.25f, -0.05f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(1.0f));
				_gui->getGlobalScreen()->getWritefield("newProjectName")->setActive(true);
				_gui->setFocus(true);
				_creatingProject = true;
			}
		}
		else if (hoveredItemID == "loadProject")
		{
			_loadingProject = true;
		}
		else if (hoveredItemID == "saveProject")
		{
			_savingProject = true;
		}
		else if (hoveredItemID == "loadProject")
		{
			engine_stop();
		}
	}

	// Update specific processes
	_updateProjectCreation();
	_updateProjectLoading();
	_updateProjectSaving();
}

void EngineController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		// Check if pressed ESCAPE or ENTER
		if (_gui->getGlobalScreen()->getWritefield("newProjectName")->cancelledInput() ||
			_gui->getGlobalScreen()->getWritefield("newProjectName")->confirmedInput())
		{
			// Extract new name
			string projectName = _gui->getGlobalScreen()->getWritefield("newProjectName")->getTextContent();

			// Cleanup
			_creatingProject = false;
			_gui->setFocus(false);
			_gui->getGlobalScreen()->deleteTextfield("newProjectName");
			_gui->getGlobalScreen()->deleteWritefield("newProjectName");

			// Create new project
			if (_gui->getGlobalScreen()->getWritefield("newProjectName")->confirmedInput())
			{

			}
		}
	}
}

void EngineController::_updateProjectLoading()
{
	if (_loadingProject)
	{
		// Open file explorer
		OPENFILENAME ofn;
		char szFile[100];
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "*.FE3D\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = "..\\User\\"; // Projects folder
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		GetOpenFileName(&ofn);
		
		// Get the loaded filename
		string fileName = ofn.lpstrFile;
		if (fileName == "") // Cancelled
		{
			_loadingProject = false;
		}
		else // Confirmed
		{
			
		}
	}
}

void EngineController::_updateProjectSaving()
{
	if (_savingProject)
	{

	}
}