#include "engine_gui_viewport.hpp"

EngineGuiViewport::EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, Vec2 position, Vec2 size, Vec3 color) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + ID)
{
	fe3d.guiEntity_add(_entityID, color, position, 0.0f, size, true);
}

void EngineGuiViewport::update(bool hoverable)
{
	for (auto& window : _windows)
	{
		window->update(hoverable);
	}
}

bool EngineGuiViewport::isHovered()
{
	// Check if entity is visible anyway
	if (_fe3d.guiEntity_isVisible(_entityID))
	{
		// Convert dimensions to same space
		Vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		Vec2 buttonPos = _fe3d.guiEntity_getPosition(_entityID);
		Vec2 buttonSize = _fe3d.guiEntity_getSize(_entityID);

		// Check if cursor inside entity
		if (mousePos.x > buttonPos.x - (buttonSize.x / 2.0f) && mousePos.x < buttonPos.x + (buttonSize.x / 2.0f)) // X axis
		{
			if (mousePos.y > buttonPos.y - (buttonSize.y / 2.0f) && mousePos.y < buttonPos.y + (buttonSize.y / 2.0f)) // Y axis
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

void EngineGuiViewport::addWindow(const string& ID, Vec2 position, Vec2 size, Vec3 color)
{
	Vec2 viewportPosition = _fe3d.guiEntity_getPosition(_entityID);
	Vec2 viewportSize = _fe3d.guiEntity_getSize(_entityID);
	Vec2 windowPosition = viewportPosition + (position * viewportSize);
	Vec2 windowSize = (size / 2.0f) * viewportSize;
	_windows.push_back(make_shared<EngineGuiWindow>(_fe3d, _ID, ID, windowPosition, windowSize, color));
}

vector<shared_ptr<EngineGuiWindow>>& EngineGuiViewport::getWindows()
{
	return _windows;
}

shared_ptr<EngineGuiWindow> EngineGuiViewport::getWindow(const string& ID)
{
	for (auto& window : _windows)
	{
		if (ID == window->getID())
		{
			return window;
		}
	}

	return nullptr;
}
