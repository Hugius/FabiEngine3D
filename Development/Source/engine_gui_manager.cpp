#include "engine_gui_manager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	_fe3d(fe3d)
{
	// Global screen
	_globalScreen = make_shared<EngineGuiGlobalScreen>(_fe3d);

	// Viewports
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "top", vec2(0.0f, 0.95f), vec2(2.0f, 0.1f), vec3(0.15f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "left", vec2(-0.875f, 0.15f), vec2(0.25f, 1.5f), vec3(0.15f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "right", vec2(0.875f, 0.15f), vec2(0.25f, 1.5f), vec3(0.15f)));
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "bottom", vec2(0.0f, -0.8f), vec2(2.0f, 0.4f), vec3(0.15f)));
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

bool EngineGuiManager::isFocused()
{
	return _isFocused;
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