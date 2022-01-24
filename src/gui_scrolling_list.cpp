#include "gui_scrolling_list.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

GuiScrollingList::GuiScrollingList(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& id, const fvec2& position, const fvec2& size, const fvec3& color, const fvec3& buttonColor, const fvec3& buttonHoverColor, const fvec3& textColor, const fvec3& textHoverColor, const fvec2& charSize, bool isCentered)
	:
	GuiRectangle(fe3d, parentID + "_scrollingList", id, position, size, color, isCentered),
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
	_buttons.push_back(make_shared<GuiButton>(_fe3d, _parentID, id, fvec2(position.x, position.y), fvec2(size.x, size.y),
					   _buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor, _fe3d->quad2d_isCentered(_entityId)));

	string rectangleID = _buttons.back()->getRectangle()->getEntityId();
	string textID = _buttons.back()->getTextField()->getEntityId();
	_fe3d->quad2d_setMinPosition(rectangleID, fvec2(-1.0f, _initialPosition.y - (_initialSize.y / 2.0f)));
	_fe3d->text2d_setMinPosition(textID, fvec2(-1.0f, _initialPosition.y - (_initialSize.y / 2.0f)));
	_fe3d->quad2d_setMaxPosition(rectangleID, fvec2(1.0f, _initialPosition.y + (_initialSize.y / 2.0f)));
	_fe3d->text2d_setMaxPosition(textID, fvec2(1.0f, _initialPosition.y + (_initialSize.y / 2.0f)));
}

void GuiScrollingList::deleteButton(const string& id)
{
	for(size_t i = 0; i < _buttons.size(); i++)
	{
		if(id == _buttons[i]->getId())
		{
			_buttons.erase(_buttons.begin() + i);

			vector<string> buttonIDs;
			vector<string> textContents;
			for(size_t j = 0; j < _buttons.size(); j++)
			{
				buttonIDs.push_back(_buttons[j]->getId());
				textContents.push_back(_fe3d->text2d_getContent(_buttons[j]->getTextField()->getEntityId()));
			}

			deleteButtons();

			for(size_t j = 0; j < buttonIDs.size(); j++)
			{
				createButton(buttonIDs[j], textContents[j]);
			}

			return;
		}
	}

	Logger::throwError("GuiScrollingList::deleteButton");
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

	fvec2 cursorPosition = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition()));
	fvec2 listPosition = _fe3d->quad2d_getPosition(_entityId);
	fvec2 listSize = _fe3d->quad2d_getSize(_entityId);

	if(cursorPosition.x > listPosition.x - (listSize.x / 2.0f) && cursorPosition.x < listPosition.x + (listSize.x / 2.0f))
	{
		if(cursorPosition.y > listPosition.y - (listSize.y / 2.0f) && cursorPosition.y < listPosition.y + (listSize.y / 2.0f))
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

		fvec2 cursorPosition = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition()));
		if(cursorPosition.x > _initialPosition.x - (_initialSize.x / 2.0f) && cursorPosition.x < _initialPosition.x + (_initialSize.x / 2.0f))
		{
			if(cursorPosition.y > _initialPosition.y - (_initialSize.y / 2.0f) && cursorPosition.y < _initialPosition.y + (_initialSize.y / 2.0f))
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
		float edgeOffset = (_fe3d->quad2d_getSize(_entityId).y / 2.0f);
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
			string rectangleID = button->getRectangle()->getEntityId();
			string textID = button->getTextField()->getEntityId();

			if(mustReset)
			{
				_fe3d->quad2d_setPosition(rectangleID, button->getRectangle()->getInitialPosition());
				_fe3d->text2d_setPosition(textID, button->getTextField()->getInitialPosition());
			}
			else
			{
				_fe3d->quad2d_move(rectangleID, fvec2(0.0f, _scrollingSpeed));
				_fe3d->text2d_move(textID, fvec2(0.0f, _scrollingSpeed));
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
	fvec2 buttonPosition = (listPosition + (position * (listSize / 2.0f)));

	return buttonPosition;
}

const fvec2 GuiScrollingList::_convertSize(const fvec2& size) const
{
	fvec2 listPosition = _fe3d->quad2d_getPosition(_entityId);
	fvec2 listSize = _fe3d->quad2d_getSize(_entityId);
	fvec2 buttonSize = (size / 2.0f) * listSize;

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