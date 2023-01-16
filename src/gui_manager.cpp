#include "gui_manager.hpp"

void GuiManager::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void GuiManager::construct()
{
	_overlay = make_shared<GuiOverlay>(_fe3d);

	_leftViewport = make_shared<GuiViewport>(_fe3d, "left", LEFT_VIEWPORT_POSITION, LEFT_VIEWPORT_SIZE, FRAME_COLOR);
	_rightViewport = make_shared<GuiViewport>(_fe3d, "right", RIGHT_VIEWPORT_POSITION, RIGHT_VIEWPORT_SIZE, FRAME_COLOR);
	_bottomViewport = make_shared<GuiViewport>(_fe3d, "bottom", BOTTOM_VIEWPORT_POSITION, BOTTOM_VIEWPORT_SIZE, FRAME_COLOR);
	_topViewport = make_shared<GuiViewport>(_fe3d, "top", TOP_VIEWPORT_POSITION, TOP_VIEWPORT_SIZE, FRAME_COLOR);
}

void GuiManager::updateOverlay()
{
	_overlay->update(true);
}

void GuiManager::updateViewports()
{
	_leftViewport->update(!_overlay->isFocused());
	_rightViewport->update(!_overlay->isFocused());
	_bottomViewport->update(!_overlay->isFocused());
	_topViewport->update(!_overlay->isFocused());
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