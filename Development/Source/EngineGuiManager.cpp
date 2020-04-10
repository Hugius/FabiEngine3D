#include "EngineGuiManager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	_fe3d(fe3d),
	_globalScreen(fe3d)
{

}

void EngineGuiManager::load()
{
	// Project viewport
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "topViewport", vec2(-1.0f, 0.85f), vec2(0.75f, 0.15f)));
	getViewport("topViewport")->addWindow("mainWindow", vec2(-1.0f), vec2(2.0f));
	getViewport("topViewport")->getWindow("mainWindow")->addScreen("mainScreen", true);
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("newProject", vec2(-0.92f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "New project", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("loadProject", vec2(-0.44f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Load project", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("playGame", vec2(0.04f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Play game", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("stopGame", vec2(0.52f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Stop game", vec3(1.0f));
}

void EngineGuiManager::update(float delta)
{
	_delta = delta;

	// Update viewports
	for (auto& viewport : _viewports)
	{
		viewport->update(delta);
	}
	
	// Update global screen
	_globalScreen.update(delta);

	// Update viewport descisions
	_updateTopViewport();
	_updateLeftViewport();
	_updateRightViewport();
	_updateBottomViewport();
}

void EngineGuiManager::unload()
{

}

shared_ptr<EngineGuiViewport> EngineGuiManager::getViewport(const string& ID)
{
	for (auto& viewport : _viewports)
	{
		if (ID == viewport->getID())
		{
			return viewport;
		}
	}

	_fe3d.logger_throwError("GUI viewport requested: \"" + ID + "\" not found in guiManager");
}

void EngineGuiManager::_updateTopViewport()
{
	auto vp = getViewport("topViewport");

	// Getting hovered button
	string hoveredButtonID = vp->getWindow("mainWindow")->getActiveScreen()->getHoveredItemID();
	
	// Check if LMB pressed
	if(_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (hoveredButtonID == "newProject")
		{
			static bool clicked = false;
			if (!clicked) // Open name writefield
			{
				clicked = true;
				_globalScreen.addTextfield("newProjectName", vec2(-0.25f, 0.05f), vec2(0.5f, 0.1f), "Enter project name:", vec3(1.0f));
				_globalScreen.addWritefield("newProjectName", vec2(-0.25f, -0.05f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(1.0f));
			}
			else // Wait for output
			{
				if (true)
				{
					_globalScreen.deleteWritefield("newProjectName");
					clicked = false;
				}
			}
		}
		else if (hoveredButtonID == "loadProject")
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
			ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = "..\\User\\"; // Projects folder
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			GetOpenFileName(&ofn);

			string fileName;
		}
	}
}

void EngineGuiManager::_updateLeftViewport()
{

}

void EngineGuiManager::_updateRightViewport()
{

}

void EngineGuiManager::_updateBottomViewport()
{

}