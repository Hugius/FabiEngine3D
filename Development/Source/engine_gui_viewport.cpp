#include "engine_gui_viewport.hpp"
#include "logger.hpp"
#include "tools.hpp"

EngineGuiViewport::EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, Vec2 position, Vec2 size, Vec3 color)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + ID)
{
	_fe3d.imageEntity_create(_entityID, true);
	_fe3d.imageEntity_setPosition(_entityID, position);
	_fe3d.imageEntity_setSize(_entityID, size);
	_fe3d.imageEntity_setColor(_entityID, color);
}

EngineGuiViewport::~EngineGuiViewport()
{
	_fe3d.imageEntity_delete(_entityID);
}

void EngineGuiViewport::update(bool hoverable)
{
	for (const auto& window : _windows)
	{
		window->update(hoverable);
	}
}

bool EngineGuiViewport::isHovered()
{
	// Check if entity is visible anyway
	if (_fe3d.imageEntity_isVisible(_entityID))
	{
		// Convert dimensions to same space
		Vec2 cursorPosition = Math::convertToNDC(Tools::convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		Vec2 buttonPosition = _fe3d.imageEntity_getPosition(_entityID);
		Vec2 buttonSize = _fe3d.imageEntity_getSize(_entityID);

		// Check if cursor inside entity
		if (cursorPosition.x > buttonPosition.x - (buttonSize.x / 2.0f) && cursorPosition.x < buttonPosition.x + (buttonSize.x / 2.0f)) // X axis
		{
			if (cursorPosition.y > buttonPosition.y - (buttonSize.y / 2.0f) && cursorPosition.y < buttonPosition.y + (buttonSize.y / 2.0f)) // Y axis
			{
				return true;
			}
		}
	}

	return false;
}

const string& EngineGuiViewport::getID()
{
	return _ID;
}

const string& EngineGuiViewport::getEntityID()
{
	return _entityID;
}

void EngineGuiViewport::createWindow(const string& ID, Vec2 position, Vec2 size, Vec3 color)
{
	Vec2 viewportPosition = _fe3d.imageEntity_getPosition(_entityID);
	Vec2 viewportSize = _fe3d.imageEntity_getSize(_entityID);
	Vec2 windowPosition = viewportPosition + (position * viewportSize);
	Vec2 windowSize = (size / 2.0f) * viewportSize;

	_windows.push_back(make_shared<EngineGuiWindow>(_fe3d, _ID, ID, windowPosition, windowSize, color));
}

void EngineGuiViewport::deleteWindow(const string& ID)
{
	// Delete window
	for (size_t i = 0; i < _windows.size(); i++)
	{
		if (_windows[i]->getID() == ID)
		{
			_windows.erase(_windows.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiViewport::deleteWindow");
}

vector<shared_ptr<EngineGuiWindow>>& EngineGuiViewport::getWindows()
{
	return _windows;
}

shared_ptr<EngineGuiWindow> EngineGuiViewport::getWindow(const string& ID)
{
	// Retrieve window
	for (const auto& window : _windows)
	{
		if (ID == window->getID())
		{
			return window;
		}
	}

	// Error
	Logger::throwError("EngineGuiViewport::getWindow");
}