#include "gui_viewport.hpp"
#include "tools.hpp"

GuiViewport::GuiViewport(shared_ptr<EngineInterface> fe3d, const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color)
	:
	_id(id),
	_quad2dId("@" + id)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;

	_fe3d->quad2d_create(_quad2dId, true);
	_fe3d->quad2d_setPosition(_quad2dId, position);
	_fe3d->quad2d_setSize(_quad2dId, size);
	_fe3d->quad2d_setColor(_quad2dId, color);
}

GuiViewport::~GuiViewport()
{
	_fe3d->quad2d_delete(_quad2dId);
}

void GuiViewport::update(bool isInteractable)
{
	_updateHovering(isInteractable);

	for(const auto & [windowId, window] : _windows)
	{
		window->update(isInteractable);
	}
}

const bool GuiViewport::hasWindow(const string & windowId) const
{
	return (_windows.find(windowId) != _windows.end());
}

const bool GuiViewport::isHovered() const
{
	return _isHovered;
}

void GuiViewport::_updateHovering(bool isInteractable)
{
	_isHovered = false;

	const auto cursorPosition = Tools::convertToNdc(Tools::getCursorPosition());
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
	return _fe3d->quad2d_getColor(_quad2dId);
}

const fvec2 & GuiViewport::getPosition() const
{
	return _fe3d->quad2d_getPosition(_quad2dId);
}

const fvec2 & GuiViewport::getSize() const
{
	return _fe3d->quad2d_getSize(_quad2dId);
}

void GuiViewport::createWindow(const string & windowId, const fvec2 & position, const fvec2 & size, const fvec3 & color)
{
	if(hasWindow(windowId))
	{
		abort();
	}

	const auto viewportPosition = _fe3d->quad2d_getPosition(_quad2dId);
	const auto viewportSize = _fe3d->quad2d_getSize(_quad2dId);
	const auto windowPosition = (viewportPosition + (position * viewportSize));
	const auto windowSize = ((size * 0.5f) * viewportSize);

	_windows.insert({windowId, make_shared<GuiWindow>(_fe3d, windowId, _id, windowPosition, windowSize, color)});
}

void GuiViewport::deleteWindow(const string & windowId)
{
	if(!hasWindow(windowId))
	{
		abort();
	}

	_windows.erase(windowId);
}

void GuiViewport::deleteWindows()
{
	_windows.clear();
}

const unordered_map<string, shared_ptr<GuiWindow>> & GuiViewport::getWindows() const
{
	return _windows;
}

const shared_ptr<GuiWindow> GuiViewport::getWindow(const string & windowId) const
{
	const auto iterator = _windows.find(windowId);

	if(iterator == _windows.end())
	{
		abort();
	}

	return iterator->second;
}