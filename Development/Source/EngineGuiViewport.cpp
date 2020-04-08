#include "EngineGuiViewport.hpp"

EngineGuiViewport::EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, vec2 position, vec2 size) :
	FE3D(fe3d),
	_ID(ID)
{
	fe3d.guiEntity_add(ID, "viewport.png", position, 0.0f, size, false);
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
	vec2 viewportPosition = FE3D.guiEntity_getPosition(_ID);
	vec2 viewportSize = FE3D.guiEntity_getSize(_ID);
	vec2 windowPosition = viewportPosition + (FE3D.misc_convertFromNDC(position) * viewportSize);
	vec2 windowSize = size * viewportSize;
	_windows.push_back(EngineGuiWindow(FE3D, ID, windowPosition, windowSize));
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

	FE3D.logger_throwError("GUI window requested: \"" + ID + "\" not found in viewport \"" + _ID + "\"");
}
