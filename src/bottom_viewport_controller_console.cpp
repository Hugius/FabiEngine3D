#include "bottom_viewport_controller.hpp"

void BottomViewportController::_updateConsole()
{
	if(_topViewportController.isScriptRunning())
	{
		return;
	}

	const auto window = _gui.getViewport("bottom")->getWindow("console");
	float scrollingSpeed = static_cast<float>(_fe3d.input_getMouseWheelY()) * static_cast<float>(window->isHovered()) * 0.1f;

	if(!_consoleMessageQueue.empty() && scrollingSpeed != 0.0f)
	{
		const auto screen = window->getScreen("main");
		const float minY = window->getInitialPosition().y - (window->getInitialSize().y / 2.0f);
		const float maxY = window->getInitialPosition().y + (window->getInitialSize().y / 2.0f);
		const float oldestMessage = _fe3d.text_getPosition(screen->getTextField(_consoleMessageQueue[0].first + "_time")->getEntityID()).y + CHAR_SIZE.y;

		const string latestMessageID = _consoleMessageQueue.back().first;
		const string entityID = screen->getTextField(latestMessageID + "_msg_0")->getEntityID();
		float latestMessageY = _fe3d.text_getPosition(entityID).y - CHAR_SIZE.y;

		unsigned int messageLineCount = static_cast<unsigned int>(_consoleMessageQueue.size());
		for(const auto& [ID, message] : _consoleMessageQueue)
		{
			int count = 0;
			while(screen->isTextFieldExisting(ID + "_msg_" + to_string(count)))
			{
				count++;
			}
			if(count > 1)
			{
				messageLineCount += static_cast<unsigned int>(count - 1);
			}
		}

		if((static_cast<float>(messageLineCount) * CHAR_SIZE.y) > window->getInitialSize().y)
		{
			if
				(
				(latestMessageY >= minY && scrollingSpeed < 0.0f)
				||
				(oldestMessage <= maxY && scrollingSpeed > 0.0f)
				)
			{
				scrollingSpeed = 0.0f;
			}

			for(const auto& [ID, message] : _consoleMessageQueue)
			{
				_fe3d.text_move(screen->getTextField(ID + "_time")->getEntityID(), fvec2(0.0f, -scrollingSpeed));

				_fe3d.text_move(screen->getTextField(ID + "_separator")->getEntityID(), fvec2(0.0f, -scrollingSpeed));

				unsigned int index = 0;
				while(screen->isTextFieldExisting(ID + "_msg_" + to_string(index)))
				{
					_fe3d.text_move(screen->getTextField(ID + "_msg_" + to_string(index))->getEntityID(), fvec2(0.0f, -scrollingSpeed));
					index++;
				}
			}
		}
	}
}

void BottomViewportController::_addConsoleMessage(const string& newMessage)
{
	auto window = _gui.getViewport("bottom")->getWindow("console");
	auto screen = window->getScreen("main");
	const float timePartOffset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH) * 2.0f;
	const float separatorPartOffset = CHAR_SIZE.x * static_cast<float>(SEPARATOR_PART_LENGTH) * 2.0f;
	const fvec2 minPosition = fvec2(-1.0f, window->getInitialPosition().y - (window->getInitialSize().y / 2.0f));
	const fvec2 maxPosition = fvec2(0.995f, window->getInitialPosition().y + (window->getInitialSize().y / 2.0f));

	string newID = to_string(_consoleMessageQueue.size());
	_consoleMessageQueue.push_back(make_pair(newID, newMessage));

	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end());
	unsigned int index = 0;
	for(const auto& [ID, message] : _consoleMessageQueue)
	{
		bool alreadyExisting = screen->isTextFieldExisting(ID + "_time");
		float floatIndex = static_cast<float>(index);
		fvec3 timePartColor = fvec3(1.0f, 0.0f, 1.0f);
		fvec3 separatorPartColor = fvec3(1.0f, 0.85f, 0.0f);

		unsigned int typePartLength = 0;
		string typeString = "";
		for(size_t i = 0; i < message.size(); i++)
		{
			typeString.push_back(message[i]);

			if(message[i] == ']')
			{
				typePartLength = static_cast<unsigned int>(i + 1);
				break;
			}
		}

		const fvec3 messagePartColor = ((typeString == "[Warn]") ? fvec3(1.0f, 0.0f, 0.0f) : (typeString == "[Debug]") ? fvec3(1.0f, 0.25f, 0.0f) : fvec3(1.0f));

		const string timePartText = message.substr(typePartLength, TIME_PART_LENGTH);
		const string separatorPartText = message.substr((typePartLength + TIME_PART_LENGTH), SEPARATOR_PART_LENGTH);
		string messagePartText = message.substr((typePartLength + TIME_PART_LENGTH) + SEPARATOR_PART_LENGTH);

		vector<string> messageParts;
		BEGIN:;
		for(size_t i = 0; i < messagePartText.size(); i++)
		{
			float offset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH + 3);
			if(offset + (static_cast<float>(i) * CHAR_SIZE.x) > window->getInitialSize().x)
			{
				messageParts.push_back(messagePartText.substr(0, i));

				messagePartText = messagePartText.substr(i, messagePartText.size() - i);
				goto BEGIN;
			}
		}

		messageParts.push_back(messagePartText);

		if(messageParts.size() == 1)
		{
			if(alreadyExisting)
			{
				_fe3d.text_setPosition(screen->getTextField(ID + "_time")->getEntityID(),
									   screen->convertPosition(fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				_fe3d.text_setPosition(screen->getTextField(ID + "_separator")->getEntityID(),
									   screen->convertPosition(fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else
			{
				screen->createTextField(ID + "_time", fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", timePartColor, false);
				string timeID = screen->getTextField(ID + "_time")->getEntityID();
				_fe3d.text_setContent(timeID, timePartText, CHAR_SIZE.x, CHAR_SIZE.y);
				_fe3d.text_setMinPosition(timeID, minPosition);
				_fe3d.text_setMaxPosition(timeID, maxPosition);

				screen->createTextField(ID + "_separator", fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", separatorPartColor, false);
				string separatorID = screen->getTextField(ID + "_separator")->getEntityID();
				_fe3d.text_setContent(separatorID, separatorPartText, CHAR_SIZE.x, CHAR_SIZE.y);
				_fe3d.text_setMinPosition(separatorID, minPosition);
				_fe3d.text_setMaxPosition(separatorID, maxPosition);
			}
		}
		else
		{
			reverse(messageParts.begin(), messageParts.end());
		}

		for(size_t i = 0; i < messageParts.size(); i++)
		{
			floatIndex = static_cast<float>(index);

			string TextFieldID = ID + "_msg_" + to_string(i);

			if(alreadyExisting)
			{
				_fe3d.text_setPosition(screen->getTextField(TextFieldID)->getEntityID(),
									   screen->convertPosition(fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else
			{
				screen->createTextField(TextFieldID, fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)),
										fvec2(0.0f), "", messagePartColor, false);
				_fe3d.text_setContent(screen->getTextField(TextFieldID)->getEntityID(), messageParts[i], CHAR_SIZE.x, CHAR_SIZE.y);

				_fe3d.text_setMinPosition(screen->getTextField(TextFieldID)->getEntityID(), minPosition);
				_fe3d.text_setMaxPosition(screen->getTextField(TextFieldID)->getEntityID(), maxPosition);
			}

			if((messageParts.size() > 1) && i == (messageParts.size() - 1))
			{
				if(alreadyExisting)
				{
					_fe3d.text_setPosition(screen->getTextField(ID + "_time")->getEntityID(),
										   screen->convertPosition(fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
					_fe3d.text_setPosition(screen->getTextField(ID + "_separator")->getEntityID(),
										   screen->convertPosition(fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				}
				else
				{
					screen->createTextField(ID + "_time", fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", timePartColor, false);
					string timeID = screen->getTextField(ID + "_time")->getEntityID();
					_fe3d.text_setContent(timeID, timePartText, CHAR_SIZE.x, CHAR_SIZE.y);
					_fe3d.text_setMinPosition(timeID, minPosition);
					_fe3d.text_setMaxPosition(timeID, maxPosition);

					screen->createTextField(ID + "_separator", fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", separatorPartColor, false);
					string separatorID = screen->getTextField(ID + "_separator")->getEntityID();
					_fe3d.text_setContent(separatorID, separatorPartText, CHAR_SIZE.x, CHAR_SIZE.y);
					_fe3d.text_setMinPosition(separatorID, minPosition);
					_fe3d.text_setMaxPosition(separatorID, maxPosition);
				}
			}

			index++;
		}
	}
	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end());
}

void BottomViewportController::_deleteConsoleMessage(const string& ID)
{
	auto window = _gui.getViewport("bottom")->getWindow("console");
	auto screen = window->getScreen("main");

	screen->deleteTextField(ID + "_time");

	screen->deleteTextField(ID + "_separator");

	unsigned int index = 0;
	while(screen->isTextFieldExisting(ID + "_msg_" + to_string(index)))
	{
		screen->deleteTextField(ID + "_msg_" + to_string(index));
		index++;
	}
}