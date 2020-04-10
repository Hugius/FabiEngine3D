#include "EngineGuiGlobalScreen.hpp"

EngineGuiGlobalScreen::EngineGuiGlobalScreen(FabiEngine3D& fe3d) :
	_fe3d(fe3d)
{

}

void EngineGuiGlobalScreen::update(float delta)
{
	// Set to default
	_hoveredItemID = "";

	// Update buttons
	for (auto& button : _buttons)
	{
		button->update(delta, true);

		// Set hovered button ID
		if (button->isHovered())
		{
			_hoveredItemID = button->getID();
		}
	}

	// Update writefields
	for (auto& writefield : _writefields)
	{
		writefield->update(delta, true);

		// Set hovered button ID
		if (writefield->isHovered())
		{
			_hoveredItemID = writefield->getID();
		}
	}
}

void EngineGuiGlobalScreen::addWritefield(const string& ID, vec2 position, vec2 size, vec3 color, vec3 textColor)
{
	_writefields.push_back(make_shared<EngineGuiWritefield>(_fe3d, "globalScreen", ID, position, size, color, textColor));
}

void EngineGuiGlobalScreen::addButton(const string& ID, vec2 position, vec2 size, vec3 color, string textContent, vec3 textColor)
{
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, "globalScreen", ID, position, size, color, textContent, textColor));
}

void EngineGuiGlobalScreen::addRectangle(const string& ID, vec2 position, vec2 size, vec3 color)
{
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, "globalScreen", ID, position, size, color));
}

void EngineGuiGlobalScreen::addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor)
{
	_textfields.push_back(make_shared<EngineGuiTextfield>(_fe3d, "globalScreen", ID, position, size, textContent, textColor));
}

shared_ptr<EngineGuiWritefield> EngineGuiGlobalScreen::getWritefield(const string& ID)
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

shared_ptr<EngineGuiButton> EngineGuiGlobalScreen::getButton(const string& ID)
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

shared_ptr<EngineGuiRectangle> EngineGuiGlobalScreen::getRectangle(const string& ID)
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

shared_ptr<EngineGuiTextfield> EngineGuiGlobalScreen::getTextfield(const string& ID)
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

vector<shared_ptr<EngineGuiWritefield>>& EngineGuiGlobalScreen::getWritefields()
{
	return _writefields;
}

vector<shared_ptr<EngineGuiButton>>& EngineGuiGlobalScreen::getButtons()
{
	return _buttons;
}

vector<shared_ptr<EngineGuiRectangle>>& EngineGuiGlobalScreen::getRectangles()
{
	return _rectangles;
}

vector<shared_ptr<EngineGuiTextfield>>& EngineGuiGlobalScreen::getTextfields()
{
	return _textfields;
}

const string& EngineGuiGlobalScreen::getHoveredItemID()
{
	return _hoveredItemID;
}

void EngineGuiGlobalScreen::deleteWritefield(const string& ID)
{
	// Delete writefield
	for (size_t i = 0; i < _writefields.size(); i++)
	{
		if (ID == _writefields[i]->getID())
		{
			_writefields.erase(_writefields.begin() + i);
			return;
		}
	}

	// Error
	_fe3d.logger_throwError("Writefield \"" + ID + "\" not deleted!");
}

void EngineGuiGlobalScreen::deleteButton(const string& ID)
{
	// Delete button
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);
			return;
		}
	}

	// Error
	_fe3d.logger_throwError("Button \"" + ID + "\" not deleted!");
}

void EngineGuiGlobalScreen::deleteRectangle(const string& ID)
{
	// Delete rectangle
	for (size_t i = 0; i < _rectangles.size(); i++)
	{
		if (ID == _rectangles[i]->getID())
		{
			_rectangles.erase(_rectangles.begin() + i);
			return;
		}
	}

	// Error
	_fe3d.logger_throwError("Rectangle \"" + ID + "\" not deleted!");
}

void EngineGuiGlobalScreen::deleteTextfield(const string& ID)
{
	// Delete textfield
	for (size_t i = 0; i < _textfields.size(); i++)
	{
		if (ID == _textfields[i]->getID())
		{
			_textfields.erase(_textfields.begin() + i);
			return;
		}
	}

	// Error
	_fe3d.logger_throwError("Textfield \"" + ID + "\" not deleted!");
}