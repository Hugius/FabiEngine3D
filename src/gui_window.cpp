#include "gui_window.hpp"
#include "tools.hpp"

GuiWindow::GuiWindow(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & color)
	:
	_id(id),
	_parentId(parentId),
	_entityId("@" + parentId + "_" + id)
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

GuiWindow::~GuiWindow()
{
	_fe3d->quad2d_delete(_entityId);
}

void GuiWindow::update(bool isInteractable)
{
	_updateHovering(isInteractable);

	for(const auto & [screenId, screen] : _screens)
	{
		screen->update(isInteractable);

		screen->setVisible(screenId == _activeScreenId);
	}
}

const bool GuiWindow::hasScreen(const string & id) const
{
	return (_screens.find(id) != _screens.end());
}

const bool GuiWindow::isHovered() const
{
	return _isHovered;
}

void GuiWindow::_updateHovering(bool isInteractable)
{
	_isHovered = false;

	const auto cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
	const auto windowPosition = getPosition();
	const auto windowSize = getSize();

	if(cursorPosition.x > (windowPosition.x - (windowSize.x * 0.5f)))
	{
		if(cursorPosition.x < (windowPosition.x + (windowSize.x * 0.5f)))
		{
			if(cursorPosition.y > (windowPosition.y - (windowSize.y * 0.5f)))
			{
				if(cursorPosition.y < (windowPosition.y + (windowSize.y * 0.5f)))
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

const string & GuiWindow::getId() const
{
	return _id;
}

const string & GuiWindow::getParentId() const
{
	return _parentId;
}

const fvec3 & GuiWindow::getColor() const
{
	return _fe3d->quad2d_getColor(_entityId);
}

const fvec2 & GuiWindow::getPosition() const
{
	return _fe3d->quad2d_getPosition(_entityId);
}

const fvec2 & GuiWindow::getSize() const
{
	return _fe3d->quad2d_getSize(_entityId);
}

void GuiWindow::createScreen(const string & id)
{
	if(hasScreen(id))
	{
		abort();
	}

	_screens.insert({id, make_shared<GuiScreen>(_fe3d, id, (_parentId + "_" + _id), getPosition(), getSize())});
}

void GuiWindow::deleteScreen(const string & id)
{
	if(!hasScreen(id))
	{
		abort();
	}

	_screens.erase(id);

	if(id == _activeScreenId)
	{
		_activeScreenId = "";
	}
}

void GuiWindow::deleteScreens()
{
	_screens.clear();
}

void GuiWindow::setActiveScreen(const string & id)
{
	if(!hasScreen(id))
	{
		abort();
	}

	_activeScreenId = id;
}

const unordered_map<string, shared_ptr<GuiScreen>> & GuiWindow::getScreens() const
{
	return _screens;
}

const shared_ptr<GuiScreen> GuiWindow::getActiveScreen() const
{
	return getScreen(_activeScreenId);
}

const shared_ptr<GuiScreen> GuiWindow::getScreen(const string & id) const
{
	auto iterator = _screens.find(id);

	if(iterator == _screens.end())
	{
		abort();
	}

	return iterator->second;
}