#include "gui_screen.hpp"

void GuiScreen::createScrollingList(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, const fvec2 & characterSize, float scrollingSpeed, bool isCentered)
{
	_scrollingLists.insert({id, make_shared<GuiScrollingList>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), color, defaultQuadColor, hoveredQuadColor, defaultTextColor, hoveredTextColor, characterSize, scrollingSpeed, isCentered)});
}

void GuiScreen::createInputBox(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCapsAllowed, bool isCentered)
{
	_inputBoxes.insert({id, make_shared<GuiInputBox>(_fe3d, (_parentId + "_" + _id), id, _convertPosition(position), _convertSize(size), color, hoverColor, textColor, textHoverColor, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed, isCapsAllowed, isCentered)});
}

void GuiScreen::createButton(const string & id, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
{
	_buttons.insert({id, make_shared<GuiButton>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), diffuseMapPath, defaultQuadColor, hoveredQuadColor, textContent, defaultTextColor, hoveredTextColor, isCentered)});
}

void GuiScreen::createQuadField(const string & id, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered)
{
	_quadFields.insert({id, make_shared<GuiQuadField>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), diffuseMapPath, color, isCentered)});
}

void GuiScreen::createTextField(const string & id, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & textColor, bool isCentered)
{
	_textFields.insert({id, make_shared<GuiTextField>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), textContent, textColor, isCentered)});
}

void GuiScreen::deleteScrollingList(const string & id)
{
	if(!hasScrollingList(id))
	{
		abort();
	}

	_scrollingLists.erase(id);
}

void GuiScreen::deleteInputBox(const string & id)
{
	if(!hasInputBox(id))
	{
		abort();
	}

	_inputBoxes.erase(id);
}

void GuiScreen::deleteButton(const string & id)
{
	if(!hasButton(id))
	{
		abort();
	}

	_buttons.erase(id);
}

void GuiScreen::deleteQuadField(const string & id)
{
	if(!hasQuadField(id))
	{
		abort();
	}

	_quadFields.erase(id);
}

void GuiScreen::deleteTextField(const string & id)
{
	if(!hasTextField(id))
	{
		abort();
	}

	_textFields.erase(id);
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

const bool GuiScreen::hasScrollingList(const string & id) const
{
	return (_scrollingLists.find(id) != _scrollingLists.end());
}

const bool GuiScreen::hasInputBox(const string & id) const
{
	return (_inputBoxes.find(id) != _inputBoxes.end());
}

const bool GuiScreen::hasButton(const string & id) const
{
	return (_buttons.find(id) != _buttons.end());
}

const bool GuiScreen::hasQuadField(const string & id) const
{
	return (_quadFields.find(id) != _quadFields.end());
}

const bool GuiScreen::hasTextField(const string & id) const
{
	return (_textFields.find(id) != _textFields.end());
}

const shared_ptr<GuiScrollingList> GuiScreen::getScrollingList(const string & id) const
{
	auto iterator = _scrollingLists.find(id);

	if(iterator == _scrollingLists.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiInputBox> GuiScreen::getInputBox(const string & id) const
{
	auto iterator = _inputBoxes.find(id);

	if(iterator == _inputBoxes.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiButton> GuiScreen::getButton(const string & id) const
{
	auto iterator = _buttons.find(id);

	if(iterator == _buttons.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiQuadField> GuiScreen::getQuadField(const string & id) const
{
	auto iterator = _quadFields.find(id);

	if(iterator == _quadFields.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiTextField> GuiScreen::getTextField(const string & id) const
{
	auto iterator = _textFields.find(id);

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