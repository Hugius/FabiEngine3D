#include "engine_gui_screen.hpp"
#include "logger.hpp"

EngineGuiScreen::EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_parentPosition(position),
	_parentSize(size)
{

}

void EngineGuiScreen::update(bool hoverable)
{
	// Update scrolling lists
	for (const auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(hoverable);
		scrollingList->setVisible(_isActive);
	}

	// Update writeFields
	for (const auto& writeField : _writeFields)
	{
		writeField->update(hoverable);
		writeField->setVisible(_isActive);
	}

	// Update buttons
	for (const auto& button : _buttons)
	{
		button->update(hoverable);
		button->setVisible(_isActive);
	}

	// Update rectangles
	for (const auto& rectangle : _rectangles)
	{
		rectangle->setVisible(_isActive);
	}

	// Update TextFields
	for (const auto& TextField : _textFields)
	{
		TextField->setVisible(_isActive);
	}
}

void EngineGuiScreen::createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize)
{
	auto dimensions = _convertDimensions(position, size);
	_scrollingLists.push_back(make_shared<EngineGuiScrollingList>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize));
}

void EngineGuiScreen::createWriteField(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed)
{
	auto dimensions = _convertDimensions(position, size);
	_writeFields.push_back(make_shared<EngineGuiWriteField>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed));
}

void EngineGuiScreen::createButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, hoverColor, textContent, textColor, textHoverColor));
}

void EngineGuiScreen::createButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), texturePath, hoverColor));
}

void EngineGuiScreen::createRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), color, isCentered));
}

void EngineGuiScreen::createRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), texturePath, isCentered));
}

void EngineGuiScreen::createTextField(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered, bool isDynamic)
{
	auto dimensions = _convertDimensions(position, size);
	_textFields.push_back(make_shared<EngineGuiTextField>(_fe3d, _parentID + "_" + _ID, ID, Vec2(dimensions.x, dimensions.y), Vec2(dimensions.z, dimensions.w), textContent, textColor, isCentered, isDynamic));
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
	Logger::throwError("Cannot not delete scrollingList with ID \"" + ID + "\"!");
}

void EngineGuiScreen::deleteWriteField(const string& ID)
{
	// Delete writeField
	for (size_t i = 0; i < _writeFields.size(); i++)
	{
		if (ID == _writeFields[i]->getID())
		{
			_writeFields.erase(_writeFields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("Cannot not delete writeField with ID \"" + ID + "\"!");
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
	Logger::throwError("Cannot not delete button with ID \"" + ID + "\"!");
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
	Logger::throwError("Cannot not delete rectangle with ID \"" + ID + "\"!");
}

void EngineGuiScreen::deleteTextField(const string& ID)
{
	// Delete TextField
	for (size_t i = 0; i < _textFields.size(); i++)
	{
		if (ID == _textFields[i]->getID())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("Cannot not delete TextField with ID \"" + ID + "\"!");
}