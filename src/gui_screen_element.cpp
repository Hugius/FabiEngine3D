#include "gui_screen.hpp"
#include "logger.hpp"

void GuiScreen::createScrollingList(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_scrollingLists.push_back(make_shared<GuiScrollingList>(_fe3d, _parentId + "_" + _id, id, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize, isCentered));
}

void GuiScreen::createWriteField(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const fvec3& textColor, const fvec3& textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_writeFields.push_back(make_shared<GuiWriteField>(_fe3d, _parentId + "_" + _id, id, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered));
}

void GuiScreen::createButton(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const string& textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<GuiButton>(_fe3d, _parentId + "_" + _id, id, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, hoverColor, textContent, textColor, textHoverColor, isCentered));
}

void GuiScreen::createButton(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, const fvec3& hoverColor, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<GuiButton>(_fe3d, _parentId + "_" + _id, id, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), texturePath, hoverColor, isCentered));
}

void GuiScreen::createRectangle(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, _parentId + "_" + _id, id, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, isCentered));
}

void GuiScreen::createRectangle(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, _parentId + "_" + _id, id, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), texturePath, isCentered));
}

void GuiScreen::createTextField(const string& id, const fvec2& position, const fvec2& size, const string& textContent, const fvec3& textColor, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_textFields.push_back(make_shared<GuiTextField>(_fe3d, _parentId + "_" + _id, id, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), textContent, textColor, isCentered));
}

void GuiScreen::deleteScrollingList(const string& id)
{
	for(size_t i = 0; i < _scrollingLists.size(); i++)
	{
		if(id == _scrollingLists[i]->getId())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	abort();
}

void GuiScreen::deleteWriteField(const string& id)
{
	for(size_t i = 0; i < _writeFields.size(); i++)
	{
		if(id == _writeFields[i]->getId())
		{
			_writeFields.erase(_writeFields.begin() + i);
			return;
		}
	}

	abort();
}

void GuiScreen::deleteButton(const string& id)
{
	for(size_t i = 0; i < _buttons.size(); i++)
	{
		if(id == _buttons[i]->getId())
		{
			_buttons.erase(_buttons.begin() + i);
			return;
		}
	}

	abort();
}

void GuiScreen::deleteRectangle(const string& id)
{
	for(size_t i = 0; i < _rectangles.size(); i++)
	{
		if(id == _rectangles[i]->getId())
		{
			_rectangles.erase(_rectangles.begin() + i);
			return;
		}
	}

	abort();
}

void GuiScreen::deleteTextField(const string& id)
{
	for(size_t i = 0; i < _textFields.size(); i++)
	{
		if(id == _textFields[i]->getId())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	abort();
}

const bool GuiScreen::isScrollingListExisting(const string& id) const
{
	for(const auto& scrollingList : _scrollingLists)
	{
		if(id == scrollingList->getId())
		{
			return true;
		}
	}

	return false;
}

const bool GuiScreen::isWriteFieldExisting(const string& id) const
{
	for(const auto& writeField : _writeFields)
	{
		if(id == writeField->getId())
		{
			return true;
		}
	}

	return false;
}

const bool GuiScreen::isButtonExisting(const string& id) const
{
	for(const auto& button : _buttons)
	{
		if(id == button->getId())
		{
			return true;
		}
	}

	return false;
}

const bool GuiScreen::isRectangleExisting(const string& id) const
{
	for(const auto& rectangle : _rectangles)
	{
		if(id == rectangle->getId())
		{
			return true;
		}
	}

	return false;
}

const bool GuiScreen::isTextFieldExisting(const string& id) const
{
	for(const auto& textField : _textFields)
	{
		if(id == textField->getId())
		{
			return true;
		}
	}

	return false;
}

shared_ptr<GuiScrollingList> GuiScreen::getScrollingList(const string& id) const
{
	for(const auto& scrollingList : _scrollingLists)
	{
		if(id == scrollingList->getId())
		{
			return scrollingList;
		}
	}

	abort();
}

shared_ptr<GuiWriteField> GuiScreen::getWriteField(const string& id) const
{
	for(const auto& writeField : _writeFields)
	{
		if(id == writeField->getId())
		{
			return writeField;
		}
	}

	abort();
}

shared_ptr<GuiButton> GuiScreen::getButton(const string& id) const
{
	for(const auto& button : _buttons)
	{
		if(id == button->getId())
		{
			return button;
		}
	}

	abort();
}

shared_ptr<GuiRectangle> GuiScreen::getRectangle(const string& id) const
{
	for(const auto& rectangle : _rectangles)
	{
		if(id == rectangle->getId())
		{
			return rectangle;
		}
	}

	abort();
}

shared_ptr<GuiTextField> GuiScreen::getTextField(const string& id) const
{
	for(const auto& textField : _textFields)
	{
		if(id == textField->getId())
		{
			return textField;
		}
	}

	abort();
}

const vector<shared_ptr<GuiScrollingList>>& GuiScreen::getScrollingLists() const
{
	return _scrollingLists;
}

const vector<shared_ptr<GuiWriteField>>& GuiScreen::getWriteFields() const
{
	return _writeFields;
}

const vector<shared_ptr<GuiButton>>& GuiScreen::getButtons() const
{
	return _buttons;
}

const vector<shared_ptr<GuiRectangle>>& GuiScreen::getRectangles() const
{
	return _rectangles;
}

const vector<shared_ptr<GuiTextField>>& GuiScreen::getTextFields() const
{
	return _textFields;
}