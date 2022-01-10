#include "gui_manager.hpp"
#include "gui_manager.hpp"
#include "configuration.hpp"

GuiManager::GuiManager()
{
	if(!Config::getInst().isApplicationExported())
	{
		_viewports.push_back(make_shared<GuiViewport>(_fe3d, "top", fvec2(0.0f, 0.95f), fvec2(2.0f, 0.1f), FRAME_COLOR));
		_viewports.push_back(make_shared<GuiViewport>(_fe3d, "left", fvec2(-0.875f, 0.15f), fvec2(0.25f, 1.5f), FRAME_COLOR));
		_viewports.push_back(make_shared<GuiViewport>(_fe3d, "right", fvec2(0.875f, 0.15f), fvec2(0.25f, 1.5f), FRAME_COLOR));
		_viewports.push_back(make_shared<GuiViewport>(_fe3d, "bottom", fvec2(0.0f, -0.8f), fvec2(2.0f, 0.4f), FRAME_COLOR));

		_overlay = make_shared<GuiOverlay>();
	}
}

void GuiManager::inject(shared_ptr<EngineInterface> fe3d)
{
	_overlay->inject(fe3d);

	_fe3d = fe3d;
}

void GuiManager::update()
{
	for(const auto& viewport : _viewports)
	{
		viewport->update(!_overlay->isFocused());
	}

	_overlay->update();
}

shared_ptr<GuiViewport> GuiManager::getViewport(const string& ID)
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

shared_ptr<GuiOverlay> GuiManager::getOverlay()
{
	return _overlay;
}
