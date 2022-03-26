#include "gui_screen.hpp"

void GuiScreen::createScrollingList(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & buttonColor, const fvec3 & buttonHoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, const fvec2 & charSize, bool isCentered)
{
	_scrollingLists.insert({id, make_shared<GuiScrollingList>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize, isCentered)});
}

void GuiScreen::createInputField(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	_inputFields.insert({id, make_shared<GuiInputField>(_fe3d, (_parentId + "_" + _id), id, _convertPosition(position), _convertSize(size), color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered)});
}

void GuiScreen::createButton(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const string & textContent, const fvec3 & textColor, const fvec3 & textHoverColor, bool isCentered)
{
	_buttons.insert({id, make_shared<GuiButton>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), color, hoverColor, textContent, textColor, textHoverColor, isCentered)});
}

void GuiScreen::createButton(const string & id, const fvec2 & position, const fvec2 & size, const string & texturePath, const fvec3 & hoverColor, bool isCentered)
{
	_buttons.insert({id, make_shared<GuiButton>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), texturePath, hoverColor, isCentered)});
}

void GuiScreen::createQuadField(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, bool isCentered)
{
	_quadFields.insert({id, make_shared<GuiQuadField>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), color, isCentered)});
}

void GuiScreen::createQuadField(const string & id, const fvec2 & position, const fvec2 & size, const string & texturePath, bool isCentered)
{
	_quadFields.insert({id, make_shared<GuiQuadField>(_fe3d, id, (_parentId + "_" + _id), _convertPosition(position), _convertSize(size), texturePath, isCentered)});
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

void GuiScreen::deleteInputField(const string & id)
{
	if(!hasInputField(id))
	{
		abort();
	}

	_inputFields.erase(id);
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

void GuiScreen::deleteInputFields()
{
	_inputFields.clear();
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

const bool GuiScreen::hasInputField(const string & id) const
{
	return (_inputFields.find(id) != _inputFields.end());
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

const shared_ptr<GuiInputField> GuiScreen::getInputField(const string & id) const
{
	auto iterator = _inputFields.find(id);

	if(iterator == _inputFields.end())
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

const unordered_map<string, shared_ptr<GuiInputField>> & GuiScreen::getInputFields() const
{
	return _inputFields;
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