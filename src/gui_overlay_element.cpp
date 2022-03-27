#include "gui_overlay.hpp"

void GuiOverlay::createScrollingList(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
{
	_scrollingLists.insert({id, make_shared<GuiScrollingList>(_fe3d, id, "overlay", position, size, color, defaultQuadColor, hoveredQuadColor, defaultTextColor, hoveredTextColor, isCentered)});
}

void GuiOverlay::createInputField(const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	_inputFields.insert({id, make_shared<GuiInputField>(_fe3d, id, "overlay", position, size, color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered)});
}

void GuiOverlay::createButton(const string & id, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
{
	_buttons.insert({id, make_shared<GuiButton>(_fe3d, id, "overlay", position, size, diffuseMapPath, defaultQuadColor, hoveredQuadColor, textContent, defaultTextColor, hoveredTextColor, isCentered)});
}

void GuiOverlay::createQuadField(const string & id, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered)
{
	_quadFields.insert({id, make_shared<GuiQuadField>(_fe3d, id, "overlay", position, size, diffuseMapPath, color, isCentered)});
}

void GuiOverlay::createTextField(const string & id, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & textColor, bool isCentered)
{
	_textFields.insert({id, make_shared<GuiTextField>(_fe3d, id, "overlay", position, size, textContent, textColor, isCentered)});
}

const bool GuiOverlay::hasScrollingList(const string & id) const
{
	return (_scrollingLists.find(id) != _scrollingLists.end());
}

const bool GuiOverlay::hasInputField(const string & id) const
{
	return (_inputFields.find(id) != _inputFields.end());
}

const bool GuiOverlay::hasButton(const string & id) const
{
	return (_buttons.find(id) != _buttons.end());
}

const bool GuiOverlay::hasQuadField(const string & id) const
{
	return (_quadFields.find(id) != _quadFields.end());
}

const bool GuiOverlay::hasTextField(const string & id) const
{
	return (_textFields.find(id) != _textFields.end());
}

const shared_ptr<GuiScrollingList> GuiOverlay::getScrollingList(const string & id) const
{
	auto iterator = _scrollingLists.find(id);

	if(iterator == _scrollingLists.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiInputField> GuiOverlay::getInputField(const string & id) const
{
	auto iterator = _inputFields.find(id);

	if(iterator == _inputFields.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiButton> GuiOverlay::getButton(const string & id) const
{
	auto iterator = _buttons.find(id);

	if(iterator == _buttons.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiQuadField> GuiOverlay::getQuadField(const string & id) const
{
	auto iterator = _quadFields.find(id);

	if(iterator == _quadFields.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<GuiTextField> GuiOverlay::getTextField(const string & id) const
{
	auto iterator = _textFields.find(id);

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

const unordered_map<string, shared_ptr<GuiInputField>> & GuiOverlay::getInputFields() const
{
	return _inputFields;
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

void GuiOverlay::deleteScrollingList(const string & id)
{
	if(!hasScrollingList(id))
	{
		abort();
	}

	_scrollingLists.erase(id);
}

void GuiOverlay::deleteInputField(const string & id)
{
	if(!hasInputField(id))
	{
		abort();
	}

	_inputFields.erase(id);
}

void GuiOverlay::deleteButton(const string & id)
{
	if(!hasButton(id))
	{
		abort();
	}

	_buttons.erase(id);
}

void GuiOverlay::deleteQuadField(const string & id)
{
	if(!hasQuadField(id))
	{
		abort();
	}

	_quadFields.erase(id);
}

void GuiOverlay::deleteTextField(const string & id)
{
	if(!hasTextField(id))
	{
		abort();
	}

	_textFields.erase(id);
}

void GuiOverlay::deleteScrollingLists()
{
	_scrollingLists.clear();
}

void GuiOverlay::deleteInputFields()
{
	_inputFields.clear();
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