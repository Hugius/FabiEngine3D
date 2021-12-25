#include "gui_viewport.hpp"
#include "logger.hpp"
#include "tools.hpp"

GuiViewport::GuiViewport(FabiEngine3D& fe3d, const string& ID, fvec2 position, fvec2 size, fvec3 color)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + ID)
{
	_fe3d.image_create(_entityID, true);
	_fe3d.image_setPosition(_entityID, position);
	_fe3d.image_setSize(_entityID, size);
	_fe3d.image_setColor(_entityID, color);
}

GuiViewport::~GuiViewport()
{
	_fe3d.image_delete(_entityID);
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
	if(_fe3d.image_isVisible(_entityID))
	{
		// Convert dimensions to same space
		fvec2 cursorPosition = Math::convertToNDC(Tools::convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		fvec2 buttonPosition = _fe3d.image_getPosition(_entityID);
		fvec2 buttonSize = _fe3d.image_getSize(_entityID);

		// Check if cursor inside entity
		if(cursorPosition.x > buttonPosition.x - (buttonSize.x / 2.0f) && cursorPosition.x < buttonPosition.x + (buttonSize.x / 2.0f)) // X axis
		{
			if(cursorPosition.y > buttonPosition.y - (buttonSize.y / 2.0f) && cursorPosition.y < buttonPosition.y + (buttonSize.y / 2.0f)) // Y axis
			{
				return true;
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
	fvec2 viewportPosition = _fe3d.image_getPosition(_entityID);
	fvec2 viewportSize = _fe3d.image_getSize(_entityID);
	fvec2 windowPosition = viewportPosition + (position * viewportSize);
	fvec2 windowSize = (size / 2.0f) * viewportSize;

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