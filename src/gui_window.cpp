#include "gui_window.hpp"
#include "logger.hpp"
#include "tools.hpp"

GuiWindow::GuiWindow(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->quad_create(_entityID, true);
	_fe3d->quad_setPosition(_entityID, position);
	_fe3d->quad_setSize(_entityID, size);
	_fe3d->quad_setColor(_entityID, color);
}

GuiWindow::~GuiWindow()
{
	_fe3d->quad_delete(_entityID);
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
	if(_fe3d->quad_isVisible(_entityID))
	{
		fvec2 cursorPosition = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition()));
		fvec2 buttonPosition = _fe3d->quad_getPosition(_entityID);
		fvec2 buttonSize = _fe3d->quad_getSize(_entityID);

		if(cursorPosition.x > buttonPosition.x - (buttonSize.x / 2.0f) && cursorPosition.x < buttonPosition.x + (buttonSize.x / 2.0f))
		{
			if(cursorPosition.y > buttonPosition.y - (buttonSize.y / 2.0f) && cursorPosition.y < buttonPosition.y + (buttonSize.y / 2.0f))
			{
				return true;
			}
		}
	}

	return false;
}

const string& GuiWindow::getID() const
{
	return _ID;
}

const string& GuiWindow::getEntityID() const
{
	return _entityID;
}

const string& GuiWindow::getParentID() const
{
	return _parentID;
}

const fvec3 GuiWindow::getInitialColor() const
{
	return _initialColor;
}

const fvec2 GuiWindow::getInitialPosition() const
{
	return _initialPosition;
}

const fvec2 GuiWindow::getInitialSize() const
{
	return _initialSize;
}

void GuiWindow::createScreen(const string& ID)
{
	for(const auto& screen : _screens)
	{
		if(screen->getID() == ID)
		{
			Logger::throwError("GuiWindow::createScreen");
		}
	}

	auto windowPosition = _fe3d->quad_getPosition(_entityID);
	auto windowSize = _fe3d->quad_getSize(_entityID);

	_screens.push_back(make_shared<GuiScreen>(_fe3d, _parentID + "_" + _ID, ID, windowPosition, windowSize));
}

void GuiWindow::deleteScreen(const string& ID)
{
	bool isFound = false;
	for(size_t i = 0; i < _screens.size(); i++)
	{
		if(_screens[i]->getID() == ID)
		{
			_screens.erase(_screens.begin() + i);
			isFound = true;
		}
	}

	if(ID == _activeScreenID)
	{
		_activeScreenID = "";
	}

	if(!isFound)
	{
		Logger::throwError("GuiWindow::deleteScreen");
	}
}

void GuiWindow::setActiveScreen(const string& ID)
{
	if(!_activeScreenID.empty())
	{
		getActiveScreen()->hide();
	}

	_activeScreenID = ID;
	getActiveScreen()->show();
}

const vector<shared_ptr<GuiScreen>>& GuiWindow::getScreens()const
{
	return _screens;
}

shared_ptr<GuiScreen> GuiWindow::getActiveScreen() const
{
	return getScreen(_activeScreenID);
}

shared_ptr<GuiScreen> GuiWindow::getScreen(const string& ID) const
{
	for(const auto& screen : _screens)
	{
		if(ID == screen->getID())
		{
			return screen;
		}
	}

	Logger::throwError("GuiWindow::getScreen");
}