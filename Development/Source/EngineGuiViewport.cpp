#include "EngineGuiViewport.hpp"

EngineGuiViewport::EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, vec2 position, vec2 size) :
	_fe3d(fe3d),
	_ID(ID)
{
	fe3d.guiEntity_add(ID, vec3(0.15f), position, 0.0f, size, false);
}

void EngineGuiViewport::update()
{
	for (auto& window : _windows)
	{
		window.update();
	}
}

const string& EngineGuiViewport::getID()
{
	return _ID;
}

const string& EngineGuiViewport::getParentID()
{
	return _parentID;
}

void EngineGuiViewport::setParentID(const string& ID)
{
	_parentID = ID;
}

void EngineGuiViewport::addWindow(const string& ID, vec2 position, vec2 size)
{
	vec2 viewportPosition = _fe3d.guiEntity_getPosition(_ID);
	vec2 viewportSize = _fe3d.guiEntity_getSize(_ID);
	vec2 windowPosition = viewportPosition + (_fe3d.misc_convertFromNDC(position) * viewportSize);
	vec2 windowSize = (size / 2.0f) * viewportSize;
	_windows.push_back(EngineGuiWindow(_fe3d, _ID, ID, windowPosition, windowSize));
}

vector<EngineGuiWindow>& EngineGuiViewport::getWindows()
{
	return _windows;
}

EngineGuiWindow& EngineGuiViewport::getWindow(const string& ID)
{
	for (auto& window : _windows)
	{
		if (ID == window.getID())
		{
			return window;
		}
	}

	_fe3d.logger_throwError("GUI window requested: \"" + ID + "\" not found in viewport \"" + _ID + "\"");
}
