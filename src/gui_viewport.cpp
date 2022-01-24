#include "gui_viewport.hpp"
#include "logger.hpp"
#include "tools.hpp"

GuiViewport::GuiViewport(shared_ptr<EngineInterface> fe3d, const string& id, const fvec2& position, const fvec2& size, const fvec3& color)
	:
	_fe3d(fe3d),
	_ID(id),
	_entityID("@" + id),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->quad2d_create(_entityID, true);
	_fe3d->quad2d_setPosition(_entityID, position);
	_fe3d->quad2d_setSize(_entityID, size);
	_fe3d->quad2d_setColor(_entityID, color);
}

GuiViewport::~GuiViewport()
{
	_fe3d->quad2d_delete(_entityID);
}

void GuiViewport::update(bool isHoverable)
{
	for(const auto& window : _windows)
	{
		window->update(isHoverable);
	}
}

const bool GuiViewport::isHovered() const
{
	if(_fe3d->quad2d_isVisible(_entityID))
	{
		auto cursorPosition = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition()));
		auto buttonPosition = _fe3d->quad2d_getPosition(_entityID);
		auto buttonSize = _fe3d->quad2d_getSize(_entityID);

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

const fvec3& GuiViewport::getInitialColor() const
{
	return _initialColor;
}

const fvec2& GuiViewport::getInitialPosition() const
{
	return _initialPosition;
}

const fvec2& GuiViewport::getInitialSize() const
{
	return _initialSize;
}

void GuiViewport::createWindow(const string& id, const fvec2& position, const fvec2& size, const fvec3& color)
{
	auto viewportPosition = _fe3d->quad2d_getPosition(_entityID);
	auto viewportSize = _fe3d->quad2d_getSize(_entityID);
	auto windowPosition = (viewportPosition + (position * viewportSize));
	auto windowSize = ((size / 2.0f) * viewportSize);

	_windows.push_back(make_shared<GuiWindow>(_fe3d, _ID, id, windowPosition, windowSize, color));
}

void GuiViewport::deleteWindow(const string& id)
{
	for(size_t i = 0; i < _windows.size(); i++)
	{
		if(_windows[i]->getID() == id)
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

shared_ptr<GuiWindow> GuiViewport::getWindow(const string& id) const
{
	for(const auto& window : _windows)
	{
		if(id == window->getID())
		{
			return window;
		}
	}

	Logger::throwError("GuiViewport::getWindow");
}