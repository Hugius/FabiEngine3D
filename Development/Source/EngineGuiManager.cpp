#include "EngineGuiManager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	_fe3d(fe3d)
{

}

void EngineGuiManager::load()
{
	// Global screen
	_globalScreen = make_shared<EngineGuiGlobalScreen>(_fe3d);

	// Viewports
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "topViewport", vec2(0.0f, 0.75f), vec2(2.0f, 0.5f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "leftViewport", vec2(-0.875f, -0.25f), vec2(0.25f, 1.5f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "rightViewport", vec2(0.875f, -0.25f), vec2(0.25f, 1.5f)));

	// Top-viewport: mainWindow
	getViewport("topViewport")->addWindow("mainWindow", vec2(0.0f), vec2(2.0f));
	getViewport("topViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("topViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("newProject", vec2(-0.72f, 0.0f), vec2(0.4f, 1.25f), vec3(0.25f), "New project", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("loadProject", vec2(-0.24f, 0.0f), vec2(0.4f, 1.25f), vec3(0.25f), "Load project", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("saveProject", vec2(0.24f, 0.0f), vec2(0.4f, 1.25f), vec3(0.25f), "Save project", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("exit", vec2(0.72f, 0.0f), vec2(0.4f, 1.25f), vec3(0.25f), "Close engine", vec3(1.0f));

	// Left-viewport: mainWindow
	getViewport("leftViewport")->addWindow("mainWindow", vec2(0.0f), vec2(2.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");

	// Right-viewport: mainWindow
	getViewport("rightViewport")->addWindow("mainWindow", vec2(0.0f), vec2(2.0f));
	getViewport("rightViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("rightViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
}

void EngineGuiManager::update(float delta)
{
	// Update viewports
	if (!_isFocused)
	{
		for (auto& viewport : _viewports)
		{
			viewport->update(delta, !_isFocused);
		}
	}
	
	// Update global screen
	_globalScreen->update(delta);
}

void EngineGuiManager::unload()
{

}

void EngineGuiManager::setFocus(bool focused)
{
	_isFocused = focused;
}

shared_ptr<EngineGuiGlobalScreen> EngineGuiManager::getGlobalScreen()
{
	return _globalScreen;
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

	return nullptr;
}