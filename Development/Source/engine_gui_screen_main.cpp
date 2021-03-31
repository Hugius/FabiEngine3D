#include "engine_gui_screen.hpp"

EngineGuiScreen::EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_parentPosition(position),
	_parentSize(size)
{

}

void EngineGuiScreen::update(bool hoverable)
{
	// Check if screen is active
	if (_isActive)
	{
		// Scrolling lists show
		for (auto& scrollingList : _scrollingLists)
		{
			scrollingList->show();
		}

		// Writefields show
		for (auto& writefield : _writefields)
		{
			writefield->show();
		}

		// Buttons show
		for (auto& button : _buttons)
		{
			button->show();
		}

		// Rectangles show
		for (auto& rectangle : _rectangles)
		{
			rectangle->show();
		}

		// Textfields show
		for (auto& textfield : _textfields)
		{
			textfield->show();
		}
	}
	else
	{
		// Scrolling lists hide
		for (auto& scrollingList : _scrollingLists)
		{
			scrollingList->hide();
		}

		// Writefields hide
		for (auto& writefield : _writefields)
		{
			writefield->hide();
		}

		// Buttons hide
		for (auto& button : _buttons)
		{
			button->hide();
		}

		// Rectangles hide
		for (auto& rectangle : _rectangles)
		{
			rectangle->hide();
		}

		// Textfields hide
		for (auto& textfield : _textfields)
		{
			textfield->hide();
		}
	}

	// Update scrolling lists
	for (auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(hoverable);
	}

	// Update writefields
	for (auto& writefield : _writefields)
	{
		writefield->update(hoverable);
	}

	// Update buttons
	for (auto& button : _buttons)
	{
		button->update(hoverable);
	}
}

void EngineGuiScreen::addScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color,
	Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize)
{
	auto dimensions = _convertDimensions(position, size);
	_scrollingLists.push_back(make_shared<EngineGuiScrollingList>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize));
}

void EngineGuiScreen::addWritefield(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, 
	bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed)
{
	auto dimensions = _convertDimensions(position, size);
	_writefields.push_back(make_shared<EngineGuiWritefield>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed));
}

void EngineGuiScreen::addButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, hoverColor, textContent, textColor, textHoverColor));
}

void EngineGuiScreen::addButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), texturePath, hoverColor));
}

void EngineGuiScreen::addRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, isCentered));
}

void EngineGuiScreen::addRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), texturePath, isCentered));
}

void EngineGuiScreen::addTextfield(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered, bool isDynamic)
{
	auto dimensions = _convertDimensions(position, size);
	_textfields.push_back(make_shared<EngineGuiTextfield>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), textContent, textColor, isCentered, isDynamic));
}

void EngineGuiScreen::deleteScrollingList(const string& ID)
{
	// Delete scrollingList
	for (size_t i = 0; i < _scrollingLists.size(); i++)
	{
		if (ID == _scrollingLists[i]->getID())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	// Error
	_fe3d.logger_throwError("Could not delete scrollingList: \"" + ID + "\"");
}

void EngineGuiScreen::deleteWritefield(const string& ID)
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
	_fe3d.logger_throwError("Could not delete writefield: \"" + ID + "\"");
}

void EngineGuiScreen::deleteButton(const string& ID)
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
	_fe3d.logger_throwError("Could not delete button: \"" + ID + "\"");
}

void EngineGuiScreen::deleteRectangle(const string& ID)
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
	_fe3d.logger_throwError("Could not delete rectangle: \"" + ID + "\"");
}

void EngineGuiScreen::deleteTextfield(const string& ID)
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
	_fe3d.logger_throwError("Could not delete textfield: \"" + ID + "\"");
}