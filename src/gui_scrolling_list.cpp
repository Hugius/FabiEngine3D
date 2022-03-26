#include "gui_scrolling_list.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

GuiScrollingList::GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & buttonColor, const fvec3 & buttonHoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, const fvec2 & charSize, bool isCentered)
	:
	GuiQuadField(fe3d, "GuiScrollingList", (parentId + "_" + id), position, size, color, isCentered),
	_buttonColor(buttonColor),
	_buttonHoverColor(buttonHoverColor),
	_textColor(textColor),
	_textHoverColor(textHoverColor),
	_charSize(charSize)
{

}

void GuiScrollingList::update(bool isHoverable)
{
	_updateHovering();
	_updateScrolling();

	for(const auto & [buttonId, button] : _buttons)
	{
		button->update(isHoverable && _isHovered);
	}
}

void GuiScrollingList::createButton(const string & id, const string & textContent)
{
	if(hasButton(id))
	{
		abort();
	}

	_buttons.insert({id, make_shared<GuiButton>(_fe3d, _parentId, id, fvec2(0.0f), fvec2(0.0f), _buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor, _fe3d->quad2d_isCentered(_entityId))});

	//string quadFieldId = _buttons.back()->getQuadField()->getEntityId();
	//string textFieldId = _buttons.back()->getTextField()->getEntityId();
	//_fe3d->quad2d_setMinPosition(quadFieldId, fvec2(-1.0f, _initialPosition.y - (_initialSize.y * 0.5f)));
	//_fe3d->text2d_setMinPosition(textFieldId, fvec2(-1.0f, _initialPosition.y - (_initialSize.y * 0.5f)));
	//_fe3d->quad2d_setMaxPosition(quadFieldId, fvec2(1.0f, _initialPosition.y + (_initialSize.y * 0.5f)));
	//_fe3d->text2d_setMaxPosition(textFieldId, fvec2(1.0f, _initialPosition.y + (_initialSize.y * 0.5f)));
}

void GuiScrollingList::deleteButton(const string & id)
{
	if(!hasButton(id))
	{
		abort();
	}

	_buttons.erase(id);
}

void GuiScrollingList::deleteButtons()
{
	_buttons.clear();
}

void GuiScrollingList::setVisible(bool isVisible)
{
	GuiQuadField::setVisible(isVisible);

	for(const auto & [buttonId, button] : _buttons)
	{
		button->setVisible(isVisible);
	}
}

void GuiScrollingList::_updateHovering()
{
	_isHovered = false;

	const auto cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
	const auto listPosition = getPosition();
	const auto listSize = getSize();

	if(cursorPosition.x > (listPosition.x - (listSize.x * 0.5f)))
	{
		if(cursorPosition.x < (listPosition.x + (listSize.x * 0.5f)))
		{
			if(cursorPosition.y > (listPosition.y - (listSize.y * 0.5f)))
			{
				if(cursorPosition.y < (listPosition.y + (listSize.y * 0.5f)))
				{
					_isHovered = true;
				}
			}
		}
	}
}

void GuiScrollingList::_updateScrolling()
{
	if(!_buttons.empty())
	{
		if(_isHovered)
		{
			_scrollingOffset -= static_cast<float>(_fe3d->input_getMouseWheelY());
		}

		_scrollingOffset = clamp(_scrollingOffset, 0.0f, 999999999999999.0f);

		for(const auto & [buttonId, button] : _buttons)
		{

		}
	}
}

const fvec2 GuiScrollingList::_convertPosition(const fvec2 & position) const
{
	const auto listPosition = _fe3d->quad2d_getPosition(_entityId);
	const auto listSize = _fe3d->quad2d_getSize(_entityId);
	const auto buttonPosition = (listPosition + (position * (listSize * 0.5f)));

	return buttonPosition;
}

const fvec2 GuiScrollingList::_convertSize(const fvec2 & size) const
{
	const auto listPosition = _fe3d->quad2d_getPosition(_entityId);
	const auto listSize = _fe3d->quad2d_getSize(_entityId);
	const auto buttonSize = ((size * 0.5f) * listSize);

	return buttonSize;
}

const bool GuiScrollingList::hasButton(const string & id)
{
	return (_buttons.find(id) != _buttons.end());
}

const bool GuiScrollingList::isHovered() const
{
	return _isHovered;
}

const shared_ptr<GuiButton> GuiScrollingList::getButton(const string & id) const
{
	auto iterator = _buttons.find(id);

	if(iterator == _buttons.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<GuiButton>> & GuiScrollingList::getButtons() const
{
	return _buttons;
}