#include "TopViewportController.hpp"

void TopViewportController::update(float delta)
{
	auto vp = _gui->getViewport("topViewport");

	// Getting hovered button
	string hoveredItemID = vp->getWindow("projectWindow")->getActiveScreen()->getHoveredItemID();

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (hoveredItemID == "newProject")
		{
			if (!_creatingProject)
			{
				_gui->getGlobalScreen()->addTextfield("newProjectName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter project name:", vec3(1.0f));
				_gui->getGlobalScreen()->addWritefield("newProjectName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
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
		else if (hoveredItemID == "openDocs")
		{
			_openingDocs = true;
		}
		else if (hoveredItemID == "quitEngine")
		{
			_quittingEngine = true;
		}
	}

	// Update specific processes
	_updateProjectCreation();
	_updateProjectLoading();
	_updateProjectSaving();
	_updateDocsOpening();
	_updateEngineQuitting();
}

void TopViewportController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		// Check if pressed ESCAPE or ENTER
		if (_gui->getGlobalScreen()->getWritefield("newProjectName")->cancelledInput() ||
			_gui->getGlobalScreen()->getWritefield("newProjectName")->confirmedInput())
		{
			// Extract new name
			string projectName = _gui->getGlobalScreen()->getWritefield("newProjectName")->getTextContent();

			// Create new project
			if (_gui->getGlobalScreen()->getWritefield("newProjectName")->confirmedInput())
			{

			}

			// Cleanup
			_creatingProject = false;
			_gui->setFocus(false);
			_gui->getGlobalScreen()->deleteTextfield("newProjectName");
			_gui->getGlobalScreen()->deleteWritefield("newProjectName");
		}
	}
}

void TopViewportController::_updateProjectLoading()
{
	if (_loadingProject)
	{
		// Get the loaded filename
		string fileName = _fe3d.misc_getWinExplorerFilename("User\\", "FE3D");
		if (fileName == "") // Cancelled
		{
			_loadingProject = false;
		}
		else // Confirmed
		{

		}
	}
}

void TopViewportController::_updateProjectSaving()
{
	if (_savingProject)
	{

	}
}

void TopViewportController::_updateDocsOpening()
{
	if (_openingDocs)
	{

	}
}

void TopViewportController::_updateEngineQuitting()
{
	if (_quittingEngine)
	{
		_fe3d.engine_stop();
	}
}