#include "gui_viewport.hpp"
#include "logger.hpp"
#include "tools.hpp"

GuiViewport::GuiViewport(const string& ID)
	:
	_ID(ID),
	_entityID("@" + ID)
{

}

GuiViewport::~GuiViewport()
{
	_fe3d->quad_delete(_entityID);
}

void GuiViewport::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void GuiViewport::load(fvec2 position, fvec2 size, fvec3 color)
{
	_fe3d->quad_create(_entityID, true);
	_fe3d->quad_setPosition(_entityID, position);
	_fe3d->quad_setSize(_entityID, size);
	_fe3d->quad_setColor(_entityID, color);
}

void GuiViewport::update(bool hoverable)
{
	for(const auto& window : _windows)
	{
		window->update(hoverable);
	}
}

const bool GuiViewport::isHovered() const
{
	if(_fe3d->quad_isVisible(_entityID))
	{
		fvec2 cursorPosition = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition()));
		fvec2 buttonPosition = _fe3d->quad_getPosition(_entityID);
		fvec2 buttonSize = _fe3d->quad_getSize(_entityID);

		if(cursorPosition.x > (buttonPosition.x - (buttonSize.x / 2.0f)))
		{
			if(cursorPosition.x < (buttonPosition.x + (buttonSize.x / 2.0f)))
			{
				if(cursorPosition.y > (buttonPosition.y - (buttonSize.y / 2.0f)))
				{
					if(cursorPosition.y < (buttonPosition.y + (buttonSize.y / 2.0f)))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

const string& GuiViewport::getID()
{
	return _ID;
}

const string& GuiViewport::getEntityID()
{
	return _entityID;
}

void GuiViewport::createWindow(const string& ID, fvec2 position, fvec2 size, fvec3 color)
{
	auto viewportPosition = _fe3d->quad_getPosition(_entityID);
	auto viewportSize = _fe3d->quad_getSize(_entityID);
	auto windowPosition = viewportPosition + (position * viewportSize);
	auto windowSize = (size / 2.0f) * viewportSize;

	_windows.push_back(make_shared<GuiWindow>(_fe3d, _ID, ID, windowPosition, windowSize, color));
}

void GuiViewport::deleteWindow(const string& ID)
{
	for(size_t i = 0; i < _windows.size(); i++)
	{
		if(_windows[i]->getID() == ID)
		{
			_windows.erase(_windows.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiViewport::deleteWindow");
}

const vector<shared_ptr<GuiWindow>>& GuiViewport::getWindows() const
{
	return _windows;
}

shared_ptr<GuiWindow> GuiViewport::getWindow(const string& ID) const
{
	for(const auto& window : _windows)
	{
		if(ID == window->getID())
		{
			return window;
		}
	}

	Logger::throwError("GuiViewport::getWindow");
}