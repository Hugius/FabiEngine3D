#include "gui_screen.hpp"

void GuiScreen::createScrollingList(const string & scrollingListId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, const fvec2 & characterSize, float scrollingSpeed, bool isCentered)
{
	_scrollingLists.insert({scrollingListId, make_shared<GuiScrollingList>(_fe3d, scrollingListId, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), color, defaultQuadColor, hoveredQuadColor, defaultTextColor, hoveredTextColor, characterSize, scrollingSpeed, isCentered)});
}

void GuiScreen::createInputBox(const string & inputBoxId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered)
{
	_inputBoxes.insert({inputBoxId, make_shared<GuiInputBox>(_fe3d, (_parentId + "_" + _id), inputBoxId, _convertPosition(position), _convertSize(size), color, hoverColor, textColor, textHoverColor, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed, isCentered)});
}

void GuiScreen::createButton(const string & buttonId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
{
	_buttons.insert({buttonId, make_shared<GuiButton>(_fe3d, buttonId, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), diffuseMapPath, defaultQuadColor, hoveredQuadColor, textContent, defaultTextColor, hoveredTextColor, isCentered)});
}

void GuiScreen::createQuadField(const string & quadFieldId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered)
{
	_quadFields.insert({quadFieldId, make_shared<GuiQuadField>(_fe3d, quadFieldId, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), diffuseMapPath, color, isCentered)});
}

void GuiScreen::createTextField(const string & textFieldId, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & textColor, bool isCentered)
{
	_textFields.insert({textFieldId, make_shared<GuiTextField>(_fe3d, textFieldId, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), textContent, textColor, isCentered)});
}

void GuiScreen::deleteScrollingList(const string & scrollingListId)
{
	if(!hasScrollingList(scrollingListId))
	{
		abort();
	}

	_scrollingLists.erase(scrollingListId);
}

void GuiScreen::deleteInputBox(const string & inputBoxId)
{
	if(!hasInputBox(inputBoxId))
	{
		abort();
	}

	_inputBoxes.erase(inputBoxId);
}

void GuiScreen::deleteButton(const string & buttonId)
{
	if(!hasButton(buttonId))
	{
		abort();
	}

	_buttons.erase(buttonId);
}

void GuiScreen::deleteQuadField(const string & quadFieldId)
{
	if(!hasQuadField(quadFieldId))
	{
		abort();
	}

	_quadFields.erase(quadFieldId);
}

void GuiScreen::deleteTextField(const string & textFieldId)
{
	if(!hasTextField(textFieldId))
	{
		abort();
	}

	_textFields.erase(textFieldId);
}

void GuiScreen::deleteScrollingLists()
{
	_scrollingLists.clear();
}

void GuiScreen::deleteInputBoxes()
{
	_inputBoxes.clear();
}

void GuiScreen::deleteButtons()
{
	_buttons.clear();
}

void GuiScreen::deleteQuadFields()
{
	_quadFields.clear();
}

void GuiScreen::deleteTextFields()
{
	_textFields.clear();
}

const bool GuiScreen::hasScrollingList(const string & scrollingListId) const
{
	return (_scrollingLists.find(scrollingListId) != _scrollingLists.end());
}

const bool GuiScreen::hasInputBox(const string & inputBoxId) const
{
	return (_inputBoxes.find(inputBoxId) != _inputBoxes.end());
}

const bool GuiScreen::hasButton(const string & buttonId) const
{
	return (_buttons.find(buttonId) != _buttons.end());
}

const bool GuiScreen::hasQuadField(const string & quadFieldId) const
{
	return (_quadFields.find(quadFieldId) != _quadFields.end());
}

const bool GuiScreen::hasTextField(const string & textFieldId) const
{
	return (_textFields.find(textFieldId) != _textFields.end());
}

const shared_ptr<GuiScrollingList> GuiScreen::getScrollingList(const string & scrollingListId) const
{
	auto iterator = _scrollingLists.find(scrollingListId);

	if(iterator == _scrollingLists.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiInputBox> GuiScreen::getInputBox(const string & inputBoxId) const
{
	auto iterator = _inputBoxes.find(inputBoxId);

	if(iterator == _inputBoxes.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiButton> GuiScreen::getButton(const string & buttonId) const
{
	auto iterator = _buttons.find(buttonId);

	if(iterator == _buttons.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiQuadField> GuiScreen::getQuadField(const string & quadFieldId) const
{
	auto iterator = _quadFields.find(quadFieldId);

	if(iterator == _quadFields.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiTextField> GuiScreen::getTextField(const string & textFieldId) const
{
	auto iterator = _textFields.find(textFieldId);

	if(iterator == _textFields.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<GuiScrollingList>> & GuiScreen::getScrollingLists() const
{
	return _scrollingLists;
}

const unordered_map<string, shared_ptr<GuiInputBox>> & GuiScreen::getInputBoxes() const
{
	return _inputBoxes;
}

const unordered_map<string, shared_ptr<GuiButton>> & GuiScreen::getButtons() const
{
	return _buttons;
}

const unordered_map<string, shared_ptr<GuiQuadField>> & GuiScreen::getQuadFields() const
{
	return _quadFields;
}

const unordered_map<string, shared_ptr<GuiTextField>> & GuiScreen::getTextFields() const
{
	return _textFields;
}