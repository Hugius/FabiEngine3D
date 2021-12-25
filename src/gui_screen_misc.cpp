#include "gui_screen.hpp"
#include "logger.hpp"

GuiScreen::GuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_parentPosition(position),
	_parentSize(size)
{

}

void GuiScreen::update(bool hoverable)
{
	for(const auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(hoverable);
		scrollingList->setVisible(_isActive);
	}

	for(const auto& writeField : _writeFields)
	{
		writeField->update(hoverable);
		writeField->setVisible(_isActive);
	}

	for(const auto& button : _buttons)
	{
		button->update(hoverable);
		button->setVisible(_isActive);
	}

	for(const auto& rectangle : _rectangles)
	{
		rectangle->setVisible(_isActive);
	}

	for(const auto& textField : _textFields)
	{
		textField->setVisible(_isActive);
	}
}

void GuiScreen::show()
{
	_isActive = true;
}

void GuiScreen::hide()
{
	_isActive = false;
}

const string& GuiScreen::getID() const
{
	return _ID;
}

const string& GuiScreen::getParentID() const
{
	return _parentID;
}

const fvec2 GuiScreen::convertPosition(fvec2 position) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonPosition = (screenPosition + (position * (screenSize / 2.0f)));

	return buttonPosition;
}

const fvec2 GuiScreen::convertSize(fvec2 size) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonSize = (size / 2.0f) * screenSize;

	return buttonSize;
}

const fvec4 GuiScreen::_convertDimensions(fvec2 position, fvec2 size) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonPosition = (screenPosition + (position * (screenSize / 2.0f)));
	fvec2 buttonSize = (size / 2.0f) * screenSize;

	return fvec4(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y);
}