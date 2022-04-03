#include "gui_viewport.hpp"
#include "logger.hpp"
#include "tools.hpp"

GuiViewport::GuiViewport(shared_ptr<EngineInterface> fe3d, const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color)
	:
	_id(id),
	_entityId("@" + id)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;

	_fe3d->quad2d_create(_entityId, true);
	_fe3d->quad2d_setPosition(_entityId, position);
	_fe3d->quad2d_setSize(_entityId, size);
	_fe3d->quad2d_setColor(_entityId, color);
}

GuiViewport::~GuiViewport()
{
	_fe3d->quad2d_delete(_entityId);
}

void GuiViewport::update(bool isInteractable)
{
	_updateHovering(isInteractable);

	for(const auto & [windowId, window] : _windows)
	{
		window->update(isInteractable);
	}
}

const bool GuiViewport::hasWindow(const string & id) const
{
	return (_windows.find(id) != _windows.end());
}

const bool GuiViewport::isHovered() const
{
	return _isHovered;
}

void GuiViewport::_updateHovering(bool isInteractable)
{
	_isHovered = false;

	const auto cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
	const auto viewportPosition = getPosition();
	const auto viewportSize = getSize();

	if(cursorPosition.x > (viewportPosition.x - (viewportSize.x * 0.5f)))
	{
		if(cursorPosition.x < (viewportPosition.x + (viewportSize.x * 0.5f)))
		{
			if(cursorPosition.y > (viewportPosition.y - (viewportSize.y * 0.5f)))
			{
				if(cursorPosition.y < (viewportPosition.y + (viewportSize.y * 0.5f)))
				{
					if(isInteractable)
					{
						_isHovered = true;
					}
				}
			}
		}
	}
}

const string & GuiViewport::getId()
{
	return _id;
}

const fvec3 & GuiViewport::getColor() const
{
	return _fe3d->quad2d_getColor(_entityId);
}

const fvec2 & GuiViewport::getPosition() const
{
	return _fe3d->quad2d_getPosition(_entityId);
}

const fvec2 & GuiViewport::getSize() const
{
	return _fe3d->quad2d_getSize(_entityId);
}

void GuiViewport::createWindow(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color)
{
	if(hasWindow(id))
	{
		abort();
	}

	const auto viewportPosition = _fe3d->quad2d_getPosition(_entityId);
	const auto viewportSize = _fe3d->quad2d_getSize(_entityId);
	const auto windowPosition = (viewportPosition + (position * viewportSize));
	const auto windowSize = ((size * 0.5f) * viewportSize);

	_windows.insert({id, make_shared<GuiWindow>(_fe3d, id, _id, windowPosition, windowSize, color)});
}

void GuiViewport::deleteWindow(const string & id)
{
	if(!hasWindow(id))
	{
		abort();
	}

	_windows.erase(id);
}

void GuiViewport::deleteWindows()
{
	_windows.clear();
}

const unordered_map<string, shared_ptr<GuiWindow>> & GuiViewport::getWindows() const
{
	return _windows;
}

const shared_ptr<GuiWindow> GuiViewport::getWindow(const string & id) const
{
	auto iterator = _windows.find(id);

	if(iterator == _windows.end())
	{
		abort();
	}

	return iterator->second;
}