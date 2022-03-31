#include "gui_screen.hpp"

GuiScreen::GuiScreen(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & parentPosition, const fvec2 & parentSize)
	:
	_id(id),
	_parentId(parentId)
{
	_fe3d = fe3d;
	_parentPosition = parentPosition;
	_parentSize = parentSize;
}

void GuiScreen::update(bool isFocused)
{
	for(const auto & [scrollingListId, scrollingList] : _scrollingLists)
	{
		scrollingList->update(isFocused);
	}

	for(const auto & [inputBoxId, inputBox] : _inputBoxes)
	{
		inputBox->update(isFocused);
	}

	for(const auto & [buttonId, button] : _buttons)
	{
		button->update(isFocused);
	}
}

void GuiScreen::setVisible(bool value)
{
	for(const auto & [scrollingListId, scrollingList] : _scrollingLists)
	{
		scrollingList->setVisible(value);
	}

	for(const auto & [inputBoxId, inputBox] : _inputBoxes)
	{
		inputBox->setVisible(value);
	}

	for(const auto & [buttonId, button] : _buttons)
	{
		button->setVisible(value);
	}

	for(const auto & [quadFieldId, quadField] : _quadFields)
	{
		quadField->setVisible(value);
	}

	for(const auto & [textFieldId, textField] : _textFields)
	{
		textField->setVisible(value);
	}
}

const string & GuiScreen::getId() const
{
	return _id;
}

const string & GuiScreen::getParentId() const
{
	return _parentId;
}

const fvec2 GuiScreen::_convertPosition(const fvec2 & position) const
{
	const auto screenPosition = _parentPosition;
	const auto screenSize = _parentSize;
	const auto buttonPosition = (screenPosition + (position * (screenSize * 0.5f)));

	return buttonPosition;
}

const fvec2 GuiScreen::_convertSize(const fvec2 & size) const
{
	const auto screenPosition = _parentPosition;
	const auto screenSize = _parentSize;
	const auto buttonSize = ((size * 0.5f) * screenSize);

	return buttonSize;
}