#include "EngineGuiManager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	_fe3d(fe3d)
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
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("newProject", vec2(-0.767f, 0.0f), vec2(0.3f, 1.25f), _topVpButtonColor, _topVpButtonHoverColor, "New project", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("loadProject", vec2(-0.384, 0.0f), vec2(0.3f, 1.25f), _topVpButtonColor, _topVpButtonHoverColor, "Load project", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("saveProject", vec2(0.0f, 0.0f), vec2(0.3f, 1.25f), _topVpButtonColor, _topVpButtonHoverColor, "Save project", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("openDocs", vec2(0.384, 0.0f), vec2(0.3f, 1.25f), _topVpButtonColor, _topVpButtonHoverColor, "Open docs", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("quitEngine", vec2(0.767f, 0.0f), vec2(0.3f, 1.25f), _topVpButtonColor, _topVpButtonHoverColor, "Quit engine", _leftVpTextColor, _leftVpTextHoverColor);

	// Top-viewport: gameWindow
	getViewport("topViewport")->addWindow("gameWindow", vec2(0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	getViewport("topViewport")->getWindow("gameWindow")->addScreen("mainScreen");
	getViewport("topViewport")->getWindow("gameWindow")->setActiveScreen("mainScreen");

	// Left-viewport: mainWindow - mainScreen
	getViewport("leftViewport")->addWindow("mainWindow", vec2(0.0f), vec2(1.9f, 2.0f), vec3(0.5f));
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("modelEditor", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Model editor", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("worldEditor", vec2(0.0f, 0.35f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "World editor", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("placingEditor", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Placing editor", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("lightingEditor", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Lighting editor", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("scriptEditor", vec2(0.0f, -0.7f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Script editor", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelManagementScreen
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelManagementScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("addModel", vec2(0.0f, 0.63f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Add model", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("editModel", vec2(0.0f, 0.21), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Edit model", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("deleteModel", vec2(0.0f, -0.21), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Delete model", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelManagementScreen")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelChoiceScreen
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelChoiceScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), _leftVpButtonColor, _leftVpButtonHoverColor, _leftVpTextColor, _leftVpTextHoverColor, 0.25f);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test1", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test2", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test3", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test4", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test5", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test6", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test7", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test8", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test9", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test10", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test11", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->getScrollingList("modelList")->addButton("test12", "hoi");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelChoiceScreen")->addButton("back", vec2(0.0f, -0.9f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

	// Left-viewport: mainWindow - modelEditingScreen
	getViewport("leftViewport")->getWindow("mainWindow")->addScreen("modelEditingScreen");
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadOBJ", vec2(0.0f, 0.7f), vec2(1.25f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load OBJ file", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadDiffuseMap", vec2(0.0f, 0.35f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load diffusemap", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadLightMap", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load lightmap", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("loadReflectionMap", vec2(0.0f, -0.35f), vec2(1.6f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Load reflectmap", _leftVpTextColor, _leftVpTextHoverColor);
	getViewport("leftViewport")->getWindow("mainWindow")->getScreen("modelEditingScreen")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _leftVpButtonColor, _leftVpButtonHoverColor, "Go back", _leftVpTextColor, _leftVpTextHoverColor);

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
	for (auto& viewport : _viewports)
	{
		viewport->update(delta, !_isFocused);
	}
	
	// Update global screen
	_globalScreen->update(delta);
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