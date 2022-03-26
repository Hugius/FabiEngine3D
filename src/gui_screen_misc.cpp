#include "gui_screen.hpp"
#include "logger.hpp"

GuiScreen::GuiScreen(shared_ptr<EngineInterface> fe3d, const string& id, const string& parentId, const fvec2& position, const fvec2& size)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_parentPosition(position),
	_parentSize(size)
{

}

void GuiScreen::update(bool isHoverable)
{
	for(const auto& [scrollingListId, scrollingList] : _scrollingLists)
	{
		scrollingList->update(isHoverable);

		scrollingList->setVisible(_isVisible);
	}

	for(const auto& [inputFieldId, inputField] : _inputFields)
	{
		inputField->update(isHoverable);

		inputField->setVisible(_isVisible);
	}

	for(const auto& [buttonId, button] : _buttons)
	{
		button->update(isHoverable);

		button->setVisible(_isVisible);
	}

	for(const auto& [quadFieldId, quadField] : _quadFields)
	{
		quadField->setVisible(_isVisible);
	}

	for(const auto& [textFieldId, textField] : _textFields)
	{
		textField->setVisible(_isVisible);
	}
}

void GuiScreen::setVisible(bool value)
{
	_isVisible = value;
}

const string& GuiScreen::getId() const
{
	return _id;
}

const string& GuiScreen::getParentId() const
{
	return _parentId;
}

const fvec2 GuiScreen::_convertPosition(const fvec2& position) const
{
	const auto screenPosition = _parentPosition;
	const auto screenSize = _parentSize;
	const auto buttonPosition = (screenPosition + (position * (screenSize * 0.5f)));

	return buttonPosition;
}

const fvec2 GuiScreen::_convertSize(const fvec2& size) const
{
	const auto screenPosition = _parentPosition;
	const auto screenSize = _parentSize;
	const auto buttonSize = ((size * 0.5f) * screenSize);

	return buttonSize;
}