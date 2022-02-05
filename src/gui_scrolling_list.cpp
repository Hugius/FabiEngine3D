#include "gui_scrolling_list.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

GuiScrollingList::GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered)
	:
	GuiRectangle(fe3d, parentId + "_scrollingList", id, position, size, color, isCentered),
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
	_updateButtons(isHoverable);
}

void GuiScrollingList::createButton(const string& id, const string& textContent)
{
	float x = 0.0f;
	float y = (1.0f - _charSize.y - (_buttons.size() * (_charSize.y * 1.5f)));
	float w = (_charSize.x * textContent.size());
	float h = _charSize.y;

	fvec2 position = _convertPosition(fvec2(x, y));
	fvec2 size = _convertSize(fvec2(w, h));
	_buttons.push_back(make_shared<GuiButton>(_fe3d, _parentId, id, fvec2(position.x, position.y), fvec2(size.x, size.y),
					   _buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor, _fe3d->quad2d_isCentered(_entityId)));

	string rectangleId = _buttons.back()->getRectangle()->getEntityId();
	string textId = _buttons.back()->getTextField()->getEntityId();
	_fe3d->quad2d_setMinPosition(rectangleId, fvec2(-1.0f, _initialPosition.y - (_initialSize.y * 0.5f)));
	_fe3d->text2d_setMinPosition(textId, fvec2(-1.0f, _initialPosition.y - (_initialSize.y * 0.5f)));
	_fe3d->quad2d_setMaxPosition(rectangleId, fvec2(1.0f, _initialPosition.y + (_initialSize.y * 0.5f)));
	_fe3d->text2d_setMaxPosition(textId, fvec2(1.0f, _initialPosition.y + (_initialSize.y * 0.5f)));
}

void GuiScrollingList::deleteButton(const string& id)
{
	for(size_t i = 0; i < _buttons.size(); i++)
	{
		if(id == _buttons[i]->getId())
		{
			_buttons.erase(_buttons.begin() + i);

			vector<string> buttonIds;
			vector<string> textContents;
			for(size_t j = 0; j < _buttons.size(); j++)
			{
				buttonIds.push_back(_buttons[j]->getId());
				textContents.push_back(_fe3d->text2d_getContent(_buttons[j]->getTextField()->getEntityId()));
			}

			deleteButtons();

			for(size_t j = 0; j < buttonIds.size(); j++)
			{
				createButton(buttonIds[j], textContents[j]);
			}

			return;
		}
	}

	abort();
}

void GuiScrollingList::deleteButtons()
{
	_buttons.clear();
	_scrollingOffset = 0.0f;
	_scrollingSpeed = 0.0f;
}

void GuiScrollingList::setVisible(bool isVisible)
{
	GuiRectangle::setVisible(isVisible);

	for(const auto& button : _buttons)
	{
		button->setVisible(isVisible);
	}
}

void GuiScrollingList::_updateHovering()
{
	_isHovered = false;

	fvec2 cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
	fvec2 listPosition = _fe3d->quad2d_getPosition(_entityId);
	fvec2 listSize = _fe3d->quad2d_getSize(_entityId);

	if(cursorPosition.x > listPosition.x - (listSize.x * 0.5f) && cursorPosition.x < listPosition.x + (listSize.x * 0.5f))
	{
		if(cursorPosition.y > listPosition.y - (listSize.y * 0.5f) && cursorPosition.y < listPosition.y + (listSize.y * 0.5f))
		{
			_isHovered = true;
		}
	}
}

void GuiScrollingList::_updateScrolling()
{
	if(!_buttons.empty())
	{
		bool mustReset = false;

		fvec2 cursorPosition = Tools::convertToNdc(_fe3d->misc_getCursorPosition());
		if(cursorPosition.x > _initialPosition.x - (_initialSize.x * 0.5f) && cursorPosition.x < _initialPosition.x + (_initialSize.x * 0.5f))
		{
			if(cursorPosition.y > _initialPosition.y - (_initialSize.y * 0.5f) && cursorPosition.y < _initialPosition.y + (_initialSize.y * 0.5f))
			{
				float scrollingAcceleration = (static_cast<float>(-_fe3d->input_getMouseWheelY()) / SCROLL_WHEEL_DIVIDER);
				_scrollingSpeed += scrollingAcceleration;
			}
		}

		_scrollingSpeed *= 0.95f;

		_scrollingOffset += _scrollingSpeed;

		if(_scrollingOffset < 0.0f)
		{
			_scrollingOffset = 0.0f;
			_scrollingSpeed = 0.0f;
			mustReset = true;
		}

		float firstButtonHeight = _fe3d->quad2d_getPosition(_buttons[0]->getRectangle()->getEntityId()).y;
		float lastButtonHeight = _fe3d->quad2d_getPosition(_buttons[_buttons.size() - 1]->getRectangle()->getEntityId()).y;
		float listHeight = _fe3d->quad2d_getPosition(_entityId).y;
		float edgeOffset = (_fe3d->quad2d_getSize(_entityId).y * 0.5f);
		if(lastButtonHeight >= listHeight - edgeOffset + (_charSize.y / 3.0f))
		{
			if(_scrollingSpeed > 0.0f)
			{
				_scrollingSpeed = 0.0f;
			}
		}

		if(firstButtonHeight <= listHeight + edgeOffset - (_charSize.y / 3.0f))
		{
			if(_scrollingSpeed < 0.0f)
			{
				_scrollingSpeed = 0.0f;
			}
		}

		for(const auto& button : _buttons)
		{
			string rectangleId = button->getRectangle()->getEntityId();
			string textId = button->getTextField()->getEntityId();

			if(mustReset)
			{
				_fe3d->quad2d_setPosition(rectangleId, button->getRectangle()->getInitialPosition());
				_fe3d->text2d_setPosition(textId, button->getTextField()->getInitialPosition());
			}
			else
			{
				_fe3d->quad2d_move(rectangleId, fvec2(0.0f, _scrollingSpeed));
				_fe3d->text2d_move(textId, fvec2(0.0f, _scrollingSpeed));
			}
		}
	}
}

void GuiScrollingList::_updateButtons(bool isHoverable)
{
	for(const auto& button : _buttons)
	{
		button->update(isHoverable && _isHovered);
	}
}

const fvec2 GuiScrollingList::_convertPosition(const fvec2& position) const
{
	fvec2 listPosition = _fe3d->quad2d_getPosition(_entityId);
	fvec2 listSize = _fe3d->quad2d_getSize(_entityId);
	fvec2 buttonPosition = (listPosition + (position * (listSize * 0.5f)));

	return buttonPosition;
}

const fvec2 GuiScrollingList::_convertSize(const fvec2& size) const
{
	fvec2 listPosition = _fe3d->quad2d_getPosition(_entityId);
	fvec2 listSize = _fe3d->quad2d_getSize(_entityId);
	fvec2 buttonSize = (size * 0.5f) * listSize;

	return buttonSize;
}

const bool GuiScrollingList::isHovered() const
{
	return _isHovered;
}

shared_ptr<GuiButton> GuiScrollingList::getButton(const string& id) const
{
	for(const auto& button : _buttons)
	{
		if(id == button->getId())
		{
			return button;
		}
	}

	return nullptr;
}

const vector<shared_ptr<GuiButton>>& GuiScrollingList::getButtons() const
{
	return _buttons;
}