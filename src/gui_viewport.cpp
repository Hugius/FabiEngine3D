#include "gui_viewport.hpp"
#include "logger.hpp"
#include "tools.hpp"

GuiViewport::GuiViewport(shared_ptr<EngineInterface> fe3d, const string& id, const fvec2& position, const fvec2& size, const fvec3& color)
	:
	_fe3d(fe3d),
	_id(id),
	_entityId("@" + id),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->quad2d_create(_entityId, true);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setColor(_entityId, color);
}

GuiViewport::~GuiViewport()
{
	_fe3d->quad2d_delete(_entityId);
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
	if(_fe3d->quad2d_isVisible(_entityId))
	{
		auto cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
		auto buttonPosition = _fe3d->quad2d_getPosition(_entityId);
		auto buttonSize = _fe3d->quad2d_getSize(_entityId);

		if(cursorPosition.x > (buttonPosition.x - (buttonSize.x * 0.5f)))
		{
			if(cursorPosition.x < (buttonPosition.x + (buttonSize.x * 0.5f)))
			{
				if(cursorPosition.y > (buttonPosition.y - (buttonSize.y * 0.5f)))
				{
					if(cursorPosition.y < (buttonPosition.y + (buttonSize.y * 0.5f)))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

const string& GuiViewport::getId()
{
	return _id;
}

const string& GuiViewport::getEntityId()
{
	return _entityId;
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
	auto viewportPosition = _fe3d->quad2d_getPosition(_entityId);
	auto viewportSize = _fe3d->quad2d_getSize(_entityId);
	auto windowPosition = (viewportPosition + (position * viewportSize));
	auto windowSize = ((size * 0.5f) * viewportSize);

	_windows.push_back(make_shared<GuiWindow>(_fe3d, _id, id, windowPosition, windowSize, color));
}

void GuiViewport::deleteWindow(const string& id)
{
	for(unsigned int index = 0; index < _windows.size(); index++)
	{
		if(_windows[index]->getId() == id)
		{
			_windows.erase(_windows.begin() + index);
			return;
		}
	}

	abort();
}

const vector<shared_ptr<GuiWindow>>& GuiViewport::getWindows() const
{
	return _windows;
}

shared_ptr<GuiWindow> GuiViewport::getWindow(const string& id) const
{
	for(const auto& window : _windows)
	{
		if(id == window->getId())
		{
			return window;
		}
	}

	abort();
}