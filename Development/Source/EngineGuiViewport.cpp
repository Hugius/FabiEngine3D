#include "EngineGuiViewport.hpp"

EngineGuiViewport::EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, vec2 position, vec2 size) :
	_fe3d(fe3d),
	_ID(ID)
{
	fe3d.guiEntity_add(ID, vec3(0.15f), position, 0.0f, size, true);
}

void EngineGuiViewport::update(float delta, bool hoverable)
{
	for (auto& window : _windows)
	{
		window->update(delta, hoverable);
	}
}

const string& EngineGuiViewport::getID()
{
	return _ID;
}

void EngineGuiViewport::addWindow(const string& ID, vec2 position, vec2 size)
{
	vec2 viewportPosition = _fe3d.guiEntity_getPosition(_ID);
	vec2 viewportSize = _fe3d.guiEntity_getSize(_ID);
	vec2 windowPosition = viewportPosition + (position * viewportSize);
	vec2 windowSize = (size / 2.0f) * viewportSize;
	_windows.push_back(make_shared<EngineGuiWindow>(_fe3d, _ID, ID, windowPosition, windowSize));
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
