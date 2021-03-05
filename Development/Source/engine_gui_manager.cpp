#include "engine_gui_manager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	_fe3d(fe3d)
{
	// Check if loading engine preview
	if (!_fe3d.engine_isGameExported())
	{
		// Global screen
		_globalScreen = make_shared<EngineGuiGlobalScreen>(_fe3d);

		// Viewports
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "top", Vec2(0.0f, 0.95f), Vec2(2.0f, 0.1f), Vec3(0.15f)));
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "left", Vec2(-0.875f, 0.15f), Vec2(0.25f, 1.5f), Vec3(0.15f)));
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "right", Vec2(0.875f, 0.15f), Vec2(0.25f, 1.5f), Vec3(0.15f)));
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "bottom", Vec2(0.0f, -0.8f), Vec2(2.0f, 0.4f), Vec3(0.15f)));
	}
}

void EngineGuiManager::update()
{
	// Update viewports
	for (auto& viewport : _viewports)
	{
		viewport->update(!_globalScreen->isFocused());
	}
	
	// Update global screen
	_globalScreen->update();
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