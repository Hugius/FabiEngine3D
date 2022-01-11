#include "gui_manager.hpp"

void GuiManager::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void GuiManager::initialize()
{
	_leftViewport = make_shared<GuiViewport>("left");
	_rightViewport = make_shared<GuiViewport>("right");
	_bottomViewport = make_shared<GuiViewport>("bottom");
	_topViewport = make_shared<GuiViewport>("top");
	_overlay = make_shared<GuiOverlay>();

	_leftViewport->inject(_fe3d);
	_rightViewport->inject(_fe3d);
	_bottomViewport->inject(_fe3d);
	_topViewport->inject(_fe3d);
	_overlay->inject(_fe3d);

	_leftViewport->load(fvec2(-0.875f, 0.15f), fvec2(0.25f, 1.5f), FRAME_COLOR);
	_rightViewport->load(fvec2(0.875f, 0.15f), fvec2(0.25f, 1.5f), FRAME_COLOR);
	_bottomViewport->load(fvec2(0.0f, -0.8f), fvec2(2.0f, 0.4f), FRAME_COLOR);
	_topViewport->load(fvec2(0.0f, 0.95f), fvec2(2.0f, 0.1f), FRAME_COLOR);
}

void GuiManager::update()
{
	_leftViewport->update(!_overlay->isFocused());
	_rightViewport->update(!_overlay->isFocused());
	_bottomViewport->update(!_overlay->isFocused());
	_topViewport->update(!_overlay->isFocused());
	_overlay->update();
}

const shared_ptr<GuiViewport> GuiManager::getLeftViewport()
{
	return _leftViewport;
}

const shared_ptr<GuiViewport> GuiManager::getRightViewport()
{
	return _rightViewport;
}

const shared_ptr<GuiViewport> GuiManager::getBottomViewport()
{
	return _bottomViewport;
}

const shared_ptr<GuiViewport> GuiManager::getTopViewport()
{
	return _topViewport;
}

const shared_ptr<GuiOverlay> GuiManager::getOverlay()
{
	return _overlay;
}