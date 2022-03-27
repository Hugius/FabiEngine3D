#include "gui_scrolling_list.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

GuiScrollingList::GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_defaultQuadColor(defaultQuadColor),
	_hoveredQuadColor(hoveredQuadColor),
	_defaultTextColor(defaultTextColor),
	_hoveredTextColor(hoveredTextColor)
{
	_quadField = make_shared<GuiQuadField>(fe3d, "GuiScrollingList", (parentId + "_" + id), position, size, color, isCentered);
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

void GuiScrollingList::createOption(const string & id, const string & textContent)
{
	if(hasOption(id))
	{
		abort();
	}

	_buttons.push_back(make_shared<GuiButton>(_fe3d, id, _parentId, fvec2(0.0f), fvec2(0.0f), _defaultQuadColor, _hoveredQuadColor, textContent, _defaultTextColor, _hoveredTextColor, _quadField->isCentered()));

	_buttons.back()->setVisible(isVisible());
}

void GuiScrollingList::deleteOption(const string & id)
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

void GuiScrollingList::deleteOptions()
{
	_buttons.clear();
}

void GuiScrollingList::setPosition(const fvec2 & value)
{
	_quadField->setPosition(value);
}

void GuiScrollingList::setSize(const fvec2 & value)
{
	_quadField->setSize(value);
}

void GuiScrollingList::setVisible(bool value)
{
	_quadField->setVisible(value);

	for(const auto & button : _buttons)
	{
		button->setVisible(value);
	}
}

const vector<string> GuiScrollingList::getOptionIds() const
{
	vector<string> result = {};

	for(const auto & button : _buttons)
	{
		result.push_back(button->getId());
	}

	return result;
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
			_scrollingOffset += (static_cast<float>(_fe3d->input_getMouseWheelY()) * SCROLLING_SPEED);
		}

		_scrollingOffset = clamp(_scrollingOffset, 0.0f, 999999999999999.0f);

		float yOffset = CHARACTER_HEIGHT;

		for(const auto & button : _buttons)
		{
			const auto listPosition = getPosition();
			const auto listSize = getSize();
			const auto buttonPosition = _convertPosition(fvec2(0.0f, (1.0f - yOffset + _scrollingOffset)));
			const auto buttonSize = _convertSize(fvec2(CHARACTER_WIDTH * 5.0f, CHARACTER_HEIGHT));

			button->setPosition(buttonPosition);
			button->setMinPosition(fvec2(-1.0f, listPosition.y - (listSize.y * 0.5f)));
			button->setMaxPosition(fvec2(1.0f, listPosition.y + (listSize.y * 0.5f)));

			yOffset += (CHARACTER_HEIGHT * 1.5f);
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

const bool GuiScrollingList::hasOption(const string & id) const
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

const string GuiScrollingList::getHoveredOptionId() const
{
	for(const auto & button : _buttons)
	{
		if(button->isHovered())
		{
			return button->getId();
		}
	}

	return "";
}

const bool GuiScrollingList::isHovered() const
{
	return _isHovered;
}

const bool GuiScrollingList::isVisible() const
{
	return _quadField->isVisible();
}

const bool GuiScrollingList::isCentered() const
{
	return _quadField->isCentered();
}

const fvec2 & GuiScrollingList::getPosition() const
{
	return _quadField->getPosition();
}

const fvec2 & GuiScrollingList::getSize() const
{
	return _quadField->getSize();
}