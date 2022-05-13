#include "gui_overlay.hpp"

GuiOverlay::GuiOverlay(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void GuiOverlay::update(bool isInteractable)
{
	_updateForms();

	for(const auto & [scrollingListId, scrollingList] : _scrollingLists)
	{
		scrollingList->update(isInteractable);
	}

	for(const auto & [inputBoxId, inputBox] : _inputBoxes)
	{
		inputBox->update(isInteractable);
	}

	for(const auto & [buttonId, button] : _buttons)
	{
		button->update(isInteractable);
	}
}

const bool GuiOverlay::isFocused() const
{
	return _isFocused;
}