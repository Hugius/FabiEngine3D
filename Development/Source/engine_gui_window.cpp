#include "engine_gui_window.hpp"
#include "logger.hpp"
#include "tools.hpp"

EngineGuiWindow::EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size)
{
	_fe3d.imageEntity_create(_entityID, true);
	_fe3d.imageEntity_setPosition(_entityID, position);
	_fe3d.imageEntity_setSize(_entityID, size);
	_fe3d.imageEntity_setColor(_entityID, color);
}

EngineGuiWindow::~EngineGuiWindow()
{
	_fe3d.imageEntity_delete(_entityID);
}

void EngineGuiWindow::update(bool hoverable)
{
	for (const auto& screen : _screens)
	{
		screen->update(hoverable);
	}
}

bool EngineGuiWindow::isHovered()
{
	// Check if entity is visible anyway
	if (_fe3d.imageEntity_isVisible(_entityID))
	{
		// Convert dimensions to same space
		Vec2 mousePos = Math::convertToNDC(Tools::convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		Vec2 buttonPos = _fe3d.imageEntity_getPosition(_entityID);
		Vec2 buttonSize = _fe3d.imageEntity_getSize(_entityID);

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

const string& EngineGuiWindow::getID()
{
	return _ID;
}

const string& EngineGuiWindow::getEntityID()
{
	return _entityID;
}

const string& EngineGuiWindow::getParentID()
{
	return _parentID;
}

const Vec2 EngineGuiWindow::getOriginalPosition()
{
	return _originalPosition;
}

const Vec2 EngineGuiWindow::getOriginalSize()
{
	return _originalSize;
}

void EngineGuiWindow::createScreen(const string& ID)
{
	// Check if already exists
	for (const auto& screen : _screens)
	{
		if (screen->getID() == ID)
		{
			Logger::throwError("EngineGuiWindow::createScreen");
		}
	}

	// Add new screen
	Vec2 windowPosition = _fe3d.imageEntity_getPosition(_entityID);
	Vec2 windowSize = _fe3d.imageEntity_getSize(_entityID);
	_screens.push_back(make_shared<EngineGuiScreen>(_fe3d, _parentID + "_" + _ID, ID, windowPosition, windowSize));
	getScreen(ID)->hide();
}

void EngineGuiWindow::deleteScreen(const string& ID)
{
	// Find screen
	bool isFound = false;
	for (size_t i = 0; i < _screens.size(); i++)
	{
		if (_screens[i]->getID() == ID)
		{
			_screens.erase(_screens.begin() + i);
			isFound = true;
		}
	}

	// No active screen
	if (ID == _activeScreenID)
	{
		_activeScreenID = "";
	}

	// Error
	if (!isFound)
	{
		Logger::throwError("EngineGuiWindow::deleteScreen");
	}
}

void EngineGuiWindow::setActiveScreen(const string& ID)
{
	// Hide old active screen if possible
	if (_activeScreenID != "")
	{
		getActiveScreen()->hide();
	}

	// Show new active screen
	_activeScreenID = ID;
	getActiveScreen()->show();
}

vector<shared_ptr<EngineGuiScreen>>& EngineGuiWindow::getScreens()
{
	return _screens;
}

shared_ptr<EngineGuiScreen> EngineGuiWindow::getActiveScreen()
{
	return getScreen(_activeScreenID);
}

shared_ptr<EngineGuiScreen> EngineGuiWindow::getScreen(const string& ID)
{
	// Retrieve screen
	for (const auto& screen : _screens)
	{
		if (ID == screen->getID())
		{
			return screen;
		}
	}

	// Error
	Logger::throwError("EngineGuiWindow::getScreen");
}