#include "gui_overlay.hpp"

GuiOverlay::GuiOverlay(shared_ptr<EngineInterface> fe3d)
	:
	_fe3d(fe3d)
{

}

void GuiOverlay::update()
{
	for(const auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(true);
	}

	for(const auto& inputField : _inputFields)
	{
		inputField->update(true);
	}

	for(const auto& button : _buttons)
	{
		button->update(true);
	}

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