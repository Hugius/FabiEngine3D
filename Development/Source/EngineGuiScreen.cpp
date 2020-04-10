#include "EngineGuiScreen.hpp"

EngineGuiScreen::EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_parentPosition(position),
	_parentSize(size)
{

}

void EngineGuiScreen::update(float delta)
{
	// Set to default
	_hoveredItemID = "";

	// Update buttons
	for (auto& button : _buttons)
	{
		button->update(delta);
		
		// Set hovered button ID
		if (button->isHovered())
		{
			_hoveredItemID = button->getID();
		}
	}

	// Update writefields
	for (auto& writefield : _writefields)
	{
		writefield->update(delta);

		// Set hovered button ID
		if (writefield->isHovered())
		{
			_hoveredItemID = writefield->getID();
		}
	}
}

const string& EngineGuiScreen::getID()
{
	return _ID;
}

const string& EngineGuiScreen::getParentID()
{
	return _parentID;
}

void EngineGuiScreen::addWritefield(const string& ID, vec2 position, vec2 size, vec3 color, vec3 textColor)
{
	auto dimensions = _convertDimensions(position, size);
	_writefields.push_back(make_shared<EngineGuiWritefield>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color, textColor));
}

void EngineGuiScreen::addButton(const string& ID, vec2 position, vec2 size, vec3 color, string textContent, vec3 textColor)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color, textContent, textColor));
}

void EngineGuiScreen::addRectangle(const string& ID, vec2 position, vec2 size, vec3 color)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color));
}

void EngineGuiScreen::addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor)
{
	auto dimensions = _convertDimensions(position, size);
	_textfields.push_back(make_shared<EngineGuiTextfield>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), textContent, textColor));
}

shared_ptr<EngineGuiWritefield> EngineGuiScreen::getWritefield(const string& ID)
{
	for (auto& writefield : _writefields)
	{
		if (ID == writefield->getID())
		{
			return writefield;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiButton> EngineGuiScreen::getButton(const string& ID)
{
	for (auto& button : _buttons)
	{
		if (ID == button->getID())
		{
			return button;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiRectangle> EngineGuiScreen::getRectangle(const string& ID)
{
	for (auto& rectangle : _rectangles)
	{
		if (ID == rectangle->getID())
		{
			return rectangle;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiTextfield> EngineGuiScreen::getTextfield(const string& ID)
{
	for (auto& textfield : _textfields)
	{
		if (ID == textfield->getID())
		{
			return textfield;
		}
	}

	return nullptr;
}

vector<shared_ptr<EngineGuiWritefield>>& EngineGuiScreen::getWritefields()
{
	return _writefields;
}

vector<shared_ptr<EngineGuiButton>>& EngineGuiScreen::getButtons()
{
	return _buttons;
}

vector<shared_ptr<EngineGuiRectangle>>& EngineGuiScreen::getRectangles()
{
	return _rectangles;
}

vector<shared_ptr<EngineGuiTextfield>>& EngineGuiScreen::getTextfields()
{
	return _textfields;
}

void EngineGuiScreen::deleteWritefield(const string& ID)
{
	// Check if existing
	getWritefield(ID);

	// Delete writefield
	for (size_t i = 0; i < _writefields.size(); i++)
	{
		if (ID == _writefields[i]->getID())
		{
			_writefields.erase(_writefields.begin() + i);
		}
	}
}

void EngineGuiScreen::deleteButton(const string& ID)
{
	// Check if existing
	getButton(ID);

	// Delete button
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);
		}
	}
}

void EngineGuiScreen::deleteRectangle(const string& ID)
{
	// Check if existing
	getButton(ID);

	// Delete rectangle
	for (size_t i = 0; i < _rectangles.size(); i++)
	{
		if (ID == _rectangles[i]->getID())
		{
			_rectangles.erase(_rectangles.begin() + i);
		}
	}
}

void EngineGuiScreen::deleteTextfield(const string& ID)
{
	// Check if existing
	getButton(ID);

	// Delete textfield
	for (size_t i = 0; i < _textfields.size(); i++)
	{
		if (ID == _textfields[i]->getID())
		{
			_textfields.erase(_textfields.begin() + i);
		}
	}
}

const string& EngineGuiScreen::getHoveredItemID()
{
	return _hoveredItemID;
}

vec4 EngineGuiScreen::_convertDimensions(vec2 position, vec2 size)
{
	vec2 screenPosition = _parentPosition;
	vec2 screenSize = _parentSize;
	vec2 buttonPosition = screenPosition + (_fe3d.misc_convertFromNDC(position) * screenSize);
	vec2 buttonSize = (size / 2.0f) * screenSize;

	return vec4(buttonPosition, buttonSize);
}