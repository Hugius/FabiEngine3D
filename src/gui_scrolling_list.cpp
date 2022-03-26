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

void GuiScrollingList::update(bool isFocused)
{
	_updateHovering();
	_updateScrolling();

	for(const auto & button : _buttons)
	{
		button->update(isFocused && _isHovered);
	}
}

void GuiScrollingList::createButton(const string & id, const string & textContent, const fvec2 & size)
{
	if(hasButton(id))
	{
		abort();
	}

	_buttons.push_back(make_shared<GuiButton>(_fe3d, id, _parentId, fvec2(0.0f), size, _buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor, _fe3d->quad2d_isCentered(_entityId)));

	_buttons.back()->setVisible(isVisible());
}

void GuiScrollingList::deleteButton(const string & id)
{
	for(unsigned int index = 0; index < _buttons.size(); index++)
	{
		if(id == _buttons[index]->getId())
		{
			_buttons.erase(_buttons.begin() + index);
			return;
		}
	}

	abort();
}

void GuiScrollingList::deleteButtons()
{
	_buttons.clear();
}

void GuiScrollingList::setVisible(bool value)
{
	GuiQuadField::setVisible(value);

	for(const auto & button : _buttons)
	{
		button->setVisible(value);
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

		float y = 0.0f;

		for(const auto & button : _buttons)
		{
			const auto listPosition = getPosition();
			const auto listSize = getSize();

			const auto buttonPosition = fvec2(listPosition.x, listPosition.y - y - _scrollingOffset);
			const auto buttonSize = button->getSize();

			button->setPosition(buttonPosition);
			button->setMinPosition(fvec2(-1.0f, listPosition.y - (listSize.y * 0.5f)));
			button->setMaxPosition(fvec2(1.0f, listPosition.y + (listSize.y * 0.5f)));

			y += buttonSize.y;
		}
	}
}

const fvec2 GuiScrollingList::_convertPosition(const fvec2 & position) const
{
	const auto listPosition = getPosition();
	const auto listSize = getSize();
	const auto buttonPosition = (listPosition + (position * (listSize * 0.5f)));

	return buttonPosition;
}

const fvec2 GuiScrollingList::_convertSize(const fvec2 & size) const
{
	const auto listPosition = getPosition();
	const auto listSize = getSize();
	const auto buttonSize = ((size * 0.5f) * listSize);

	return buttonSize;
}

const bool GuiScrollingList::hasButton(const string & id)
{
	for(const auto & button : _buttons)
	{
		if(id == button->getId())
		{
			return true;
		}
	}

	return false;
}

const bool GuiScrollingList::isHovered() const
{
	return _isHovered;
}

const shared_ptr<GuiButton> GuiScrollingList::getButton(const string & id) const
{
	for(const auto & button : _buttons)
	{
		if(id == button->getId())
		{
			return button;
		}
	}

	abort();
}

const fvec2 & GuiScrollingList::getPosition() const
{
	return _fe3d->quad2d_getPosition(_entityId);
}

const fvec2 & GuiScrollingList::getSize() const
{
	return _fe3d->quad2d_getSize(_entityId);
}

const vector<shared_ptr<GuiButton>> & GuiScrollingList::getButtons() const
{
	return _buttons;
}