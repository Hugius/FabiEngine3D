#include "gui_scrolling_list.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

GuiScrollingList::GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, const fvec2 & characterSize, float scrollingSpeed, bool isCentered)
	:
	_id(id),
	_parentId(parentId)
{
	if(_id.empty())
	{
		abort();
	}

	_fe3d = fe3d;
	_defaultQuadColor = defaultQuadColor;
	_hoveredQuadColor = hoveredQuadColor;
	_defaultTextColor = defaultTextColor;
	_hoveredTextColor = hoveredTextColor;
	_characterSize = characterSize;
	_scrollingSpeed = scrollingSpeed;

	_quadField = make_shared<GuiQuadField>(_fe3d, "GuiScrollingList", (_parentId + "_" + _id), position, size, "", color, isCentered);
}

void GuiScrollingList::update(bool isInteractable)
{
	_updateHovering(isInteractable);
	_updateScrolling();

	for(const auto & button : _buttons)
	{
		button->update(isInteractable);
	}
}

void GuiScrollingList::createOption(const string & id, const string & textContent)
{
	if(hasOption(id))
	{
		abort();
	}

	_buttons.push_back(make_shared<GuiButton>(_fe3d, id, (_parentId + "_" + _id), fvec2(0.0f), fvec2(0.0f), "", _defaultQuadColor, _hoveredQuadColor, textContent, _defaultTextColor, _hoveredTextColor, _quadField->isCentered()));

	_buttons.back()->setVisible(isVisible());
}

void GuiScrollingList::deleteOption(const string & id)
{
	for(unsigned int index = 0; index < static_cast<unsigned int>(_buttons.size()); index++)
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

void GuiScrollingList::setColor(const fvec3 & value)
{
	_quadField->setColor(value);
}

void GuiScrollingList::setPosition(const fvec2 & value)
{
	_quadField->setPosition(value);
}

void GuiScrollingList::setSize(const fvec2 & value)
{
	_quadField->setSize(value);
}

const fvec3 & GuiScrollingList::getDefaultQuadColor()
{
	return _defaultQuadColor;
}

const fvec3 & GuiScrollingList::getHoveredQuadColor()
{
	return _hoveredQuadColor;
}

const fvec3 & GuiScrollingList::getDefaultTextColor()
{
	return _defaultTextColor;
}

const fvec3 & GuiScrollingList::getHoveredTextColor()
{
	return _hoveredTextColor;
}

void GuiScrollingList::setDefaultQuadColor(const fvec3 & value)
{
	_hoveredQuadColor = value;

	for(const auto & button : _buttons)
	{
		button->setDefaultQuadColor(value);
	}
}

void GuiScrollingList::setHoveredQuadColor(const fvec3 & value)
{
	_hoveredTextColor = value;

	for(const auto & button : _buttons)
	{
		button->setHoveredQuadColor(value);
	}
}

void GuiScrollingList::setDefaultTextColor(const fvec3 & value)
{
	_defaultQuadColor = value;

	for(const auto & button : _buttons)
	{
		button->setDefaultTextColor(value);
	}
}

void GuiScrollingList::setHoveredTextColor(const fvec3 & value)
{
	_defaultTextColor = value;

	for(const auto & button : _buttons)
	{
		button->setHoveredTextColor(value);
	}
}

void GuiScrollingList::setCharacterSize(const fvec2 & value)
{
	_characterSize = value;
}

void GuiScrollingList::setScrollingSpeed(float value)
{
	_scrollingSpeed = value;
}

void GuiScrollingList::setHoverable(bool value)
{
	_isHoverable = value;

	_quadField->setOpacity(_isHoverable ? FULL_OPACITY : PART_OPACITY);

	for(const auto & button : _buttons)
	{
		button->setHoverable(value);
	}
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

const string GuiScrollingList::getId() const
{
	return _id;
}

const string GuiScrollingList::getParentId() const
{
	return _parentId;
}

void GuiScrollingList::_updateHovering(bool isInteractable)
{
	_isHovered = false;

	if(isVisible())
	{
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
						if(isInteractable && _isHoverable)
						{
							_isHovered = true;
						}
					}
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
			_scrollingOffset += (static_cast<float>(_fe3d->input_getMouseWheelY()) * _scrollingSpeed);
		}

		const auto totalHeight = ((static_cast<float>(_buttons.size()) * _characterSize.y * 1.5f) + (_characterSize.y * 0.5f));

		if(totalHeight < 2.0f)
		{
			_scrollingOffset = 0.0f;
		}
		else
		{
			_scrollingOffset = clamp(_scrollingOffset, -(totalHeight - 2.0f), 0.0f);
		}

		auto yOffset = _characterSize.y;

		for(const auto & button : _buttons)
		{
			const auto listPosition = getPosition();
			const auto listSize = getSize();
			const auto buttonPosition = _convertPosition(fvec2(0.0f, (1.0f - yOffset - _scrollingOffset)));
			const auto buttonSize = _convertSize(fvec2((_characterSize.x * static_cast<float>(button->getTextContent().size())), _characterSize.y));

			button->setPosition(buttonPosition);
			button->setSize(buttonSize);
			button->setMinPosition(fvec2(-1.0f, listPosition.y - (listSize.y * 0.5f)));
			button->setMaxPosition(fvec2(1.0f, listPosition.y + (listSize.y * 0.5f)));

			yOffset += (_characterSize.y * 1.5f);
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

const fvec3 & GuiScrollingList::getColor() const
{
	return _quadField->getColor();
}

const bool GuiScrollingList::isHovered() const
{
	return _isHovered;
}

const bool GuiScrollingList::isHoverable() const
{
	return _isHoverable;
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

const fvec2 & GuiScrollingList::getCharacterSize() const
{
	return _characterSize;
}

const float GuiScrollingList::getScrollingSpeed() const
{
	return _scrollingSpeed;
}