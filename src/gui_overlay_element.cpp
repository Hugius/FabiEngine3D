#include "gui_overlay.hpp"
#include "logger.hpp"

void GuiOverlay::createScrollingList(const string& id, const fvec2& position, const fvec2& size, const fvec3& color,
									 const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered)
{
	_scrollingLists.push_back(make_shared<GuiScrollingList>(_fe3d, "overlay", id, position, size, color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize, isCentered));
}

void GuiOverlay::createInputField(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const fvec3& textColor, const fvec3& textHoverColor,
								  bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	_inputFields.push_back(make_shared<GuiInputField>(_fe3d, "overlay", id, position, size, color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered));
}

void GuiOverlay::createButton(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& hoverColor, const string& textContent, const fvec3& textColor, const fvec3& textHoverColor, bool isCentered)
{
	_buttons.push_back(make_shared<GuiButton>(_fe3d, "overlay", id, position, size, color, hoverColor, textContent, textColor, textHoverColor, isCentered));
}

void GuiOverlay::createButton(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, const fvec3& hoverColor, bool isCentered)
{
	_buttons.push_back(make_shared<GuiButton>(_fe3d, "overlay", id, position, size, texturePath, hoverColor, isCentered));
}

void GuiOverlay::createRectangle(const string& id, const fvec2& position, const fvec2& size, const fvec3& color, bool isCentered)
{
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, "overlay", id, position, size, color, isCentered));
}

void GuiOverlay::createRectangle(const string& id, const fvec2& position, const fvec2& size, const string& texturePath, bool isCentered)
{
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, "overlay", id, position, size, texturePath, isCentered));
}

void GuiOverlay::createTextField(const string& id, const fvec2& position, const fvec2& size, const string& textContent, const fvec3& textColor, bool isCentered)
{
	_textFields.push_back(make_shared<GuiTextField>(_fe3d, "overlay", id, position, size, textContent, textColor, isCentered));
}

const bool GuiOverlay::isScrollingListExisting(const string& id) const
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

const bool GuiOverlay::isInputFieldExisting(const string& id) const
{
	for(const auto& inputField : _inputFields)
	{
		if(id == inputField->getId())
		{
			return true;
		}
	}

	return false;
}

const bool GuiOverlay::isButtonExisting(const string& id) const
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

const bool GuiOverlay::isRectangleExisting(const string& id) const
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

const bool GuiOverlay::isTextFieldExisting(const string& id) const
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

shared_ptr<GuiScrollingList> GuiOverlay::getScrollingList(const string& id) const
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

shared_ptr<GuiInputField> GuiOverlay::getInputField(const string& id) const
{
	for(const auto& inputField : _inputFields)
	{
		if(id == inputField->getId())
		{
			return inputField;
		}
	}

	abort();
}

shared_ptr<GuiButton> GuiOverlay::getButton(const string& id) const
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

shared_ptr<GuiRectangle> GuiOverlay::getRectangle(const string& id) const
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

shared_ptr<GuiTextField> GuiOverlay::getTextField(const string& id) const
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

const vector<shared_ptr<GuiScrollingList>>& GuiOverlay::getScrollingLists() const
{
	return _scrollingLists;
}

const vector<shared_ptr<GuiInputField>>& GuiOverlay::getInputFields() const
{
	return _inputFields;
}

const vector<shared_ptr<GuiButton>>& GuiOverlay::getButtons() const
{
	return _buttons;
}

const vector<shared_ptr<GuiRectangle>>& GuiOverlay::getRectangles() const
{
	return _rectangles;
}

const vector<shared_ptr<GuiTextField>>& GuiOverlay::getTextFields() const
{
	return _textFields;
}

void GuiOverlay::deleteScrollingList(const string& id)
{
	for(unsigned int i = 0; i < _scrollingLists.size(); i++)
	{
		if(id == _scrollingLists[i]->getId())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	abort();
}

void GuiOverlay::deleteInputField(const string& id)
{
	for(unsigned int i = 0; i < _inputFields.size(); i++)
	{
		if(id == _inputFields[i]->getId())
		{
			_inputFields.erase(_inputFields.begin() + i);
			return;
		}
	}

	abort();
}

void GuiOverlay::deleteButton(const string& id)
{
	for(unsigned int i = 0; i < _buttons.size(); i++)
	{
		if(id == _buttons[i]->getId())
		{
			_buttons.erase(_buttons.begin() + i);
			return;
		}
	}

	abort();
}

void GuiOverlay::deleteRectangle(const string& id)
{
	for(unsigned int i = 0; i < _rectangles.size(); i++)
	{
		if(id == _rectangles[i]->getId())
		{
			_rectangles.erase(_rectangles.begin() + i);
			return;
		}
	}

	abort();
}

void GuiOverlay::deleteTextField(const string& id)
{
	for(unsigned int i = 0; i < _textFields.size(); i++)
	{
		if(id == _textFields[i]->getId())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	abort();
}