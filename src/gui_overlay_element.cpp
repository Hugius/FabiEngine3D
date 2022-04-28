#include "gui_overlay.hpp"

void GuiOverlay::createScrollingList(const string & scrollingListId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, const fvec2 & characterSize, float scrollingSpeed, bool isCentered)
{
	_scrollingLists.insert({scrollingListId, make_shared<GuiScrollingList>(_fe3d, scrollingListId, "overlay", position, size, color, defaultQuadColor, hoveredQuadColor, defaultTextColor, hoveredTextColor, characterSize, scrollingSpeed, isCentered)});
}

void GuiOverlay::createInputBox(const string & inputBoxId, const fvec2 & position, const fvec2 & size, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered)
{
	_inputBoxes.insert({inputBoxId, make_shared<GuiInputBox>(_fe3d, inputBoxId, "overlay", position, size, defaultQuadColor, hoveredQuadColor, defaultTextColor, hoveredTextColor, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed, isCentered)});
}

void GuiOverlay::createButton(const string & buttonId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
{
	_buttons.insert({buttonId, make_shared<GuiButton>(_fe3d, buttonId, "overlay", position, size, diffuseMapPath, defaultQuadColor, hoveredQuadColor, textContent, defaultTextColor, hoveredTextColor, isCentered)});
}

void GuiOverlay::createQuadField(const string & quadFieldId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered)
{
	_quadFields.insert({quadFieldId, make_shared<GuiQuadField>(_fe3d, quadFieldId, "overlay", position, size, diffuseMapPath, color, isCentered)});
}

void GuiOverlay::createTextField(const string & textFieldId, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & textColor, bool isCentered)
{
	_textFields.insert({textFieldId, make_shared<GuiTextField>(_fe3d, textFieldId, "overlay", position, size, textContent, textColor, isCentered)});
}

const bool GuiOverlay::hasScrollingList(const string & scrollingListId) const
{
	return (_scrollingLists.find(scrollingListId) != _scrollingLists.end());
}

const bool GuiOverlay::hasInputBox(const string & inputBoxId) const
{
	return (_inputBoxes.find(inputBoxId) != _inputBoxes.end());
}

const bool GuiOverlay::hasButton(const string & buttonId) const
{
	return (_buttons.find(buttonId) != _buttons.end());
}

const bool GuiOverlay::hasQuadField(const string & quadFieldId) const
{
	return (_quadFields.find(quadFieldId) != _quadFields.end());
}

const bool GuiOverlay::hasTextField(const string & textFieldId) const
{
	return (_textFields.find(textFieldId) != _textFields.end());
}

const shared_ptr<GuiScrollingList> GuiOverlay::getScrollingList(const string & scrollingListId) const
{
	auto iterator = _scrollingLists.find(scrollingListId);

	if(iterator == _scrollingLists.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiInputBox> GuiOverlay::getInputBox(const string & inputBoxId) const
{
	auto iterator = _inputBoxes.find(inputBoxId);

	if(iterator == _inputBoxes.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiButton> GuiOverlay::getButton(const string & buttonId) const
{
	auto iterator = _buttons.find(buttonId);

	if(iterator == _buttons.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiQuadField> GuiOverlay::getQuadField(const string & quadFieldId) const
{
	auto iterator = _quadFields.find(quadFieldId);

	if(iterator == _quadFields.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiTextField> GuiOverlay::getTextField(const string & textFieldId) const
{
	auto iterator = _textFields.find(textFieldId);

	if(iterator == _textFields.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<GuiScrollingList>> & GuiOverlay::getScrollingLists() const
{
	return _scrollingLists;
}

const unordered_map<string, shared_ptr<GuiInputBox>> & GuiOverlay::getInputBoxes() const
{
	return _inputBoxes;
}

const unordered_map<string, shared_ptr<GuiButton>> & GuiOverlay::getButtons() const
{
	return _buttons;
}

const unordered_map<string, shared_ptr<GuiQuadField>> & GuiOverlay::getQuadFields() const
{
	return _quadFields;
}

const unordered_map<string, shared_ptr<GuiTextField>> & GuiOverlay::getTextFields() const
{
	return _textFields;
}

void GuiOverlay::deleteScrollingList(const string & scrollingListId)
{
	if(!hasScrollingList(scrollingListId))
	{
		abort();
	}

	_scrollingLists.erase(scrollingListId);
}

void GuiOverlay::deleteInputBox(const string & inputBoxId)
{
	if(!hasInputBox(inputBoxId))
	{
		abort();
	}

	_inputBoxes.erase(inputBoxId);
}

void GuiOverlay::deleteButton(const string & buttonId)
{
	if(!hasButton(buttonId))
	{
		abort();
	}

	_buttons.erase(buttonId);
}

void GuiOverlay::deleteQuadField(const string & quadFieldId)
{
	if(!hasQuadField(quadFieldId))
	{
		abort();
	}

	_quadFields.erase(quadFieldId);
}

void GuiOverlay::deleteTextField(const string & textFieldId)
{
	if(!hasTextField(textFieldId))
	{
		abort();
	}

	_textFields.erase(textFieldId);
}

void GuiOverlay::deleteScrollingLists()
{
	_scrollingLists.clear();
}

void GuiOverlay::deleteInputBoxes()
{
	_inputBoxes.clear();
}

void GuiOverlay::deleteButtons()
{
	_buttons.clear();
}

void GuiOverlay::deleteQuadFields()
{
	_quadFields.clear();
}

void GuiOverlay::deleteTextFields()
{
	_textFields.clear();
}