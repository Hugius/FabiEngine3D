#include "EngineGuiManager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	_fe3d(fe3d)
{

}

void EngineGuiManager::load()
{
	// Project viewport
	_viewports.push_back(EngineGuiViewport(_fe3d, "topViewport", vec2(-1.0f, 0.85f), vec2(0.75f, 0.15f)));
	_getViewport("topViewport").addWindow("mainWindow", vec2(-1.0f), vec2(2.0f));
	_getViewport("topViewport").getWindow("mainWindow").addScreen("mainScreen", true);
	_getViewport("topViewport").getWindow("mainWindow").getScreen("mainScreen").addButton("newProject", vec2(-0.92f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "New project", vec3(1.0f));
	_getViewport("topViewport").getWindow("mainWindow").getScreen("mainScreen").addButton("loadProject", vec2(-0.44f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Load project", vec3(1.0f));
	_getViewport("topViewport").getWindow("mainWindow").getScreen("mainScreen").addButton("playGame", vec2(0.04f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Play game", vec3(1.0f));
	_getViewport("topViewport").getWindow("mainWindow").getScreen("mainScreen").addButton("stopGame", vec2(0.52f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Stop game", vec3(1.0f));
}

void EngineGuiManager::update(float delta)
{
	_delta = delta;

	// Update viewports
	for (auto& viewport : _viewports)
	{
		viewport.update();
	}

	// Update viewport descisions
	_updateTopViewport();
	_updateLeftViewport();
	_updateRightViewport();
	_updateBottomViewport();
}

void EngineGuiManager::unload()
{

}

EngineGuiViewport& EngineGuiManager::_getViewport(const string& ID)
{
	for (auto& viewport : _viewports)
	{
		if (ID == viewport.getID())
		{
			return viewport;
		}
	}

	_fe3d.logger_throwError("GUI viewport requested: \"" + ID + "\" not found in guiManager");
}

void EngineGuiManager::_updateTopViewport()
{
	auto& vp = _getViewport("topViewport");

	string hoveredButtonID = vp.getWindow("mainWindow").getActiveScreen().getHoveredButtonID();
	{
		if (hoveredButtonID == "newProject")
		{
			
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