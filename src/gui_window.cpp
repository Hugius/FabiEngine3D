#include "gui_window.hpp"
#include "logger.hpp"
#include "tools.hpp"

GuiWindow::GuiWindow(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color)
	:
	_fe3d(fe3d),
	_id(id),
	_entityId("@" + parentId + "_" + id),
	_parentId(parentId),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->quad2d_create(_entityId, true);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setColor(_entityId, color);
}

GuiWindow::~GuiWindow()
{
	_fe3d->quad2d_delete(_entityId);
}

void GuiWindow::update(bool isHoverable)
{
	for(const auto& screen : _screens)
	{
		screen->update(isHoverable);
	}
}

const bool GuiWindow::isHovered() const
{
	if(_fe3d->quad2d_isVisible(_entityId))
	{
		fvec2 cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
		fvec2 buttonPosition = _fe3d->quad2d_getPosition(_entityId);
		fvec2 buttonSize = _fe3d->quad2d_getSize(_entityId);

		if(cursorPosition.x > buttonPosition.x - (buttonSize.x * 0.5f) && cursorPosition.x < buttonPosition.x + (buttonSize.x * 0.5f))
		{
			if(cursorPosition.y > buttonPosition.y - (buttonSize.y * 0.5f) && cursorPosition.y < buttonPosition.y + (buttonSize.y * 0.5f))
			{
				return true;
			}
		}
	}

	return false;
}

const string& GuiWindow::getId() const
{
	return _id;
}

const string& GuiWindow::getEntityId() const
{
	return _entityId;
}

const string& GuiWindow::getParentId() const
{
	return _parentId;
}

const fvec3& GuiWindow::getInitialColor() const
{
	return _initialColor;
}

const fvec2& GuiWindow::getInitialPosition() const
{
	return _initialPosition;
}

const fvec2& GuiWindow::getInitialSize() const
{
	return _initialSize;
}

void GuiWindow::createScreen(const string& id)
{
	for(const auto& screen : _screens)
	{
		if(screen->getId() == id)
		{
			abort();
		}
	}

	auto windowPosition = _fe3d->quad2d_getPosition(_entityId);
	auto windowSize = _fe3d->quad2d_getSize(_entityId);

	_screens.push_back(make_shared<GuiScreen>(_fe3d, _parentId + "_" + _id, id, windowPosition, windowSize));
}

void GuiWindow::deleteScreen(const string& id)
{
	bool isFound = false;
	for(unsigned int i = 0; i < _screens.size(); i++)
	{
		if(_screens[i]->getId() == id)
		{
			_screens.erase(_screens.begin() + i);
			isFound = true;
		}
	}

	if(id == _activeScreenId)
	{
		_activeScreenId = "";
	}

	if(!isFound)
	{
		abort();
	}
}

void GuiWindow::setActiveScreen(const string& id)
{
	if(!_activeScreenId.empty())
	{
		getActiveScreen()->hide();
	}

	_activeScreenId = id;
	getActiveScreen()->show();
}

const vector<shared_ptr<GuiScreen>>& GuiWindow::getScreens()const
{
	return _screens;
}

shared_ptr<GuiScreen> GuiWindow::getActiveScreen() const
{
	return getScreen(_activeScreenId);
}

shared_ptr<GuiScreen> GuiWindow::getScreen(const string& id) const
{
	for(const auto& screen : _screens)
	{
		if(id == screen->getId())
		{
			return screen;
		}
	}

	abort();
}