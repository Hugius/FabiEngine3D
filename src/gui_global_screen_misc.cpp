#include "gui_global_screen.hpp"

GuiGlobalScreen::GuiGlobalScreen(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d)
{

}

void GuiGlobalScreen::update()
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

void GuiGlobalScreen::setFocus(bool focused)
{
	_isFocused = focused;
}

const bool GuiGlobalScreen::isFocused() const
{
	return _isFocused;
}