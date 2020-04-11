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
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "topViewport", vec2(0.0f, 0.95f), vec2(2.0f, 0.1f), vec3(0.15f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "leftViewport", vec2(-0.875f, 0.15f), vec2(0.25f, 1.5f), vec3(0.15f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "rightViewport", vec2(0.875f, 0.15f), vec2(0.25f, 1.5f), vec3(0.15f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "bottomViewport", vec2(0.0f, -0.8f), vec2(2.0f, 0.4f), vec3(0.15f)));

	// Top-viewport: projectWindow
	getViewport("topViewport")->addWindow("projectWindow", vec2(-0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	getViewport("topViewport")->getWindow("projectWindow")->addScreen("mainScreen");
	getViewport("topViewport")->getWindow("projectWindow")->setActiveScreen("mainScreen");
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("newProject", vec2(-0.767f, 0.0f), vec2(0.3f, 1.25f), vec3(0.0f, 0.25f, 0.0f), vec3(0.0f, 0.5f, 0.0f), "New project", vec3(1.0f), vec3(0.0f));
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("loadProject", vec2(-0.384, 0.0f), vec2(0.3f, 1.25f), vec3(0.0f, 0.25f, 0.0f), vec3(0.0f, 0.5f, 0.0f), "Load project", vec3(1.0f), vec3(0.0f));
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("saveProject", vec2(0.0f, 0.0f), vec2(0.3f, 1.25f), vec3(0.0f, 0.25f, 0.0f), vec3(0.0f, 0.5f, 0.0f), "Save project", vec3(1.0f), vec3(0.0f));
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("openDocs", vec2(0.384, 0.0f), vec2(0.3f, 1.25f), vec3(0.0f, 0.25f, 0.0f), vec3(0.0f, 0.5f, 0.0f), "Open docs", vec3(1.0f), vec3(0.0f));
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("quitEngine", vec2(0.767f, 0.0f), vec2(0.3f, 1.25f), vec3(0.0f, 0.25f, 0.0f), vec3(0.0f, 0.5f, 0.0f), "Quit engine", vec3(1.0f), vec3(0.0f));

	// Top-viewport: gameWindow
	getViewport("topViewport")->addWindow("gameWindow", vec2(0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	getViewport("topViewport")->getWindow("gameWindow")->addScreen("mainScreen");
	getViewport("topViewport")->getWindow("gameWindow")->setActiveScreen("mainScreen");

	// Left-viewport: mainWindow - mainScreen
	getViewport("leftViewport")->addWindow("mainWindow", vec2(0.0f), vec2(1.9f, 2.0f), vec3(0.5f));
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("modelEditor", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Model editor", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("worldEditor", vec2(0.0f, 0.35f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "World editor", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("placingEditor", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Placing editor", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("lightingEditor", vec2(0.0f, -0.35f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Lighting editor", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("scriptEditor", vec2(0.0f, -0.7f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Script editor", vec3(1.0f), vec3(0.0f));

	// Left-viewport: mainWindow - modelManagementScreen
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelManagementScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Add model", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Edit model", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Delete model", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("back", vec2(0.0f, -0.63f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Go back", vec3(1.0f), vec3(0.0f));

	// Left-viewport: mainWindow - modelEditingScreen
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelEditingScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadOBJ", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Load OBJ file", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadDiffuseMap", vec2(0.0f, 0.35f), vec2(1.5f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Load diffusemap", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadLightMap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Load lightmap", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadReflectionMap", vec2(0.0f, -0.35f), vec2(1.75f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Load reflectionmap", vec3(1.0f), vec3(0.0f));
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("back", vec2(0.0f, -0.35f), vec2(0.75f, 0.1f), vec3(0.0f, 0.0f, 0.25f), vec3(0.0f, 0.0f, 0.75f), "Go back", vec3(1.0f), vec3(0.0f));

	// Right-viewport: mainWindow
	getViewport("rightViewport")->addWindow("mainWindow", vec2(0.0f), vec2(1.9f, 2.0f), vec3(0.5f));
	getViewport("rightViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("rightViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");

	// Bottom-viewport: mainWindow
	getViewport("bottomViewport")->addWindow("mainWindow", vec2(0.0f), vec2(1.975f, 1.8f), vec3(0.05f));
	getViewport("bottomViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("bottomViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
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