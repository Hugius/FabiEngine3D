#include "gui_overlay.hpp"

GuiOverlay::GuiOverlay(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d)
{

}

void GuiOverlay::update()
{
	// Update scrolling lists
	for(const auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(true);
	}

	// Update writeFields
	for(const auto& writeField : _writeFields)
	{
		writeField->update(true);
	}

	// Update buttons
	for(const auto& button : _buttons)
	{
		button->update(true);
	}

	// Miscellaneous
	_updateValueFormDeleting();
}

void GuiOverlay::setFocused(bool value)
{
	_isFocused = value;
}

const bool GuiOverlay::isFocused() const
{
	return _isFocused;
}