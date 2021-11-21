#include "engine_gui_manager.hpp"
#include "configuration.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d)
{
	// Check if loading engine preview
	if(!Config::getInst().isApplicationExported())
	{
		// Global screen
		_globalScreen = make_shared<EngineGuiGlobalScreen>(_fe3d);

		// Viewports
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "top", fvec2(0.0f, 0.95f), fvec2(2.0f, 0.1f), FRAME_COLOR));
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "left", fvec2(-0.875f, 0.15f), fvec2(0.25f, 1.5f), FRAME_COLOR));
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "right", fvec2(0.875f, 0.15f), fvec2(0.25f, 1.5f), FRAME_COLOR));
		_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "bottom", fvec2(0.0f, -0.8f), fvec2(2.0f, 0.4f), FRAME_COLOR));
	}
}

void EngineGuiManager::update()
{
	// Update viewports
	for(const auto& viewport : _viewports)
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
	for(const auto& viewport : _viewports)
	{
		if(ID == viewport->getID())
		{
			return viewport;
		}
	}

	return nullptr;
}