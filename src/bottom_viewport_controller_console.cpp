#include "bottom_viewport_controller.hpp"

void BottomViewportController::_updateConsole()
{
	if(_scriptExecutor->isRunning())
	{
		return;
	}

	const auto window = _gui->getBottomViewport()->getWindow("console");
	float scrollingSpeed = static_cast<float>(_fe3d->input_getMouseWheelY()) * static_cast<float>(window->isHovered()) * 0.1f;

	if(!_consoleMessageQueue.empty() && scrollingSpeed != 0.0f)
	{
		const auto screen = window->getScreen("main");
		const float minY = window->getInitialPosition().y - (window->getInitialSize().y * 0.5f);
		const float maxY = window->getInitialPosition().y + (window->getInitialSize().y * 0.5f);
		const float oldestMessage = _fe3d->text2d_getPosition(screen->getTextField(_consoleMessageQueue[0].first + "_time")->getEntityId()).y + CHAR_SIZE.y;

		const string latestMessageId = _consoleMessageQueue.back().first;
		const string entityId = screen->getTextField(latestMessageId + "_msg_0")->getEntityId();
		float latestMessageY = _fe3d->text2d_getPosition(entityId).y - CHAR_SIZE.y;

		unsigned int messageLineCount = static_cast<unsigned int>(_consoleMessageQueue.size());
		for(const auto& [key, message] : _consoleMessageQueue)
		{
			int count = 0;
			while(screen->isTextFieldExisting(key + "_msg_" + to_string(count)))
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

			for(const auto& [key, message] : _consoleMessageQueue)
			{
				_fe3d->text2d_move(screen->getTextField(key + "_time")->getEntityId(), fvec2(0.0f, -scrollingSpeed));

				_fe3d->text2d_move(screen->getTextField(key + "_separator")->getEntityId(), fvec2(0.0f, -scrollingSpeed));

				unsigned int index = 0;
				while(screen->isTextFieldExisting(key + "_msg_" + to_string(index)))
				{
					_fe3d->text2d_move(screen->getTextField(key + "_msg_" + to_string(index))->getEntityId(), fvec2(0.0f, -scrollingSpeed));
					index++;
				}
			}
		}
	}
}

void BottomViewportController::_addConsoleMessage(const string& newMessage)
{
	auto window = _gui->getBottomViewport()->getWindow("console");
	auto screen = window->getScreen("main");
	const float timePartOffset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH) * 2.0f;
	const float separatorPartOffset = CHAR_SIZE.x * static_cast<float>(SEPARATOR_PART_LENGTH) * 2.0f;
	const fvec2 minPosition = fvec2(-1.0f, window->getInitialPosition().y - (window->getInitialSize().y * 0.5f));
	const fvec2 maxPosition = fvec2(0.995f, window->getInitialPosition().y + (window->getInitialSize().y * 0.5f));

	const auto newId = to_string(_consoleMessageQueue.size());
	_consoleMessageQueue.push_back({newId, newMessage});

	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end());
	unsigned int index = 0;
	for(const auto& [key, message] : _consoleMessageQueue)
	{
		bool alreadyExisting = screen->isTextFieldExisting(key + "_time");
		float floatIndex = static_cast<float>(index);
		fvec3 timePartColor = fvec3(1.0f, 0.0f, 1.0f);
		fvec3 separatorPartColor = fvec3(1.0f, 0.85f, 0.0f);

		unsigned int typePartLength = 0;
		string typeString = "";
		for(unsigned int i = 0; i < message.size(); i++)
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
		for(unsigned int i = 0; i < messagePartText.size(); i++)
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
				_fe3d->text2d_setPosition(screen->getTextField(key + "_time")->getEntityId(),
										  screen->convertPosition(fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				_fe3d->text2d_setPosition(screen->getTextField(key + "_separator")->getEntityId(),
										  screen->convertPosition(fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else
			{
				screen->createTextField(key + "_time", fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", timePartColor, false);
				string timeId = screen->getTextField(key + "_time")->getEntityId();
				_fe3d->text2d_setContent(timeId, timePartText);
				_fe3d->text2d_setSize(timeId, fvec2(CHAR_SIZE.x * static_cast<float>(timePartText.size()), CHAR_SIZE.y));
				_fe3d->text2d_setMinPosition(timeId, minPosition);
				_fe3d->text2d_setMaxPosition(timeId, maxPosition);

				screen->createTextField(key + "_separator", fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", separatorPartColor, false);
				string separatorId = screen->getTextField(key + "_separator")->getEntityId();
				_fe3d->text2d_setContent(separatorId, separatorPartText);
				_fe3d->text2d_setSize(separatorId, fvec2(CHAR_SIZE.x * static_cast<float>(separatorPartText.size()), CHAR_SIZE.y));
				_fe3d->text2d_setMinPosition(separatorId, minPosition);
				_fe3d->text2d_setMaxPosition(separatorId, maxPosition);
			}
		}
		else
		{
			reverse(messageParts.begin(), messageParts.end());
		}

		for(unsigned int i = 0; i < messageParts.size(); i++)
		{
			floatIndex = static_cast<float>(index);

			string textFieldId = key + "_msg_" + to_string(i);

			if(alreadyExisting)
			{
				_fe3d->text2d_setPosition(screen->getTextField(textFieldId)->getEntityId(),
										  screen->convertPosition(fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else
			{
				screen->createTextField(textFieldId, fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)),
										fvec2(0.0f), "", messagePartColor, false);

				_fe3d->text2d_setContent(screen->getTextField(textFieldId)->getEntityId(), messageParts[i]);
				_fe3d->text2d_setSize(screen->getTextField(textFieldId)->getEntityId(), fvec2(CHAR_SIZE.x * static_cast<float>(messageParts[i].size()), CHAR_SIZE.y));

				_fe3d->text2d_setMinPosition(screen->getTextField(textFieldId)->getEntityId(), minPosition);
				_fe3d->text2d_setMaxPosition(screen->getTextField(textFieldId)->getEntityId(), maxPosition);
			}

			if((messageParts.size() > 1) && i == (messageParts.size() - 1))
			{
				if(alreadyExisting)
				{
					_fe3d->text2d_setPosition(screen->getTextField(key + "_time")->getEntityId(),
											  screen->convertPosition(fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
					_fe3d->text2d_setPosition(screen->getTextField(key + "_separator")->getEntityId(),
											  screen->convertPosition(fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				}
				else
				{
					screen->createTextField(key + "_time", fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", timePartColor, false);
					string timeId = screen->getTextField(key + "_time")->getEntityId();
					_fe3d->text2d_setContent(timeId, timePartText);
					_fe3d->text2d_setSize(timeId, fvec2(CHAR_SIZE.x * static_cast<float>(timePartText.size()), CHAR_SIZE.y));
					_fe3d->text2d_setMinPosition(timeId, minPosition);
					_fe3d->text2d_setMaxPosition(timeId, maxPosition);

					screen->createTextField(key + "_separator", fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", separatorPartColor, false);
					string separatorId = screen->getTextField(key + "_separator")->getEntityId();
					_fe3d->text2d_setContent(separatorId, separatorPartText);
					_fe3d->text2d_setSize(separatorId, fvec2(CHAR_SIZE.x * static_cast<float>(separatorPartText.size()), CHAR_SIZE.y));
					_fe3d->text2d_setMinPosition(separatorId, minPosition);
					_fe3d->text2d_setMaxPosition(separatorId, maxPosition);
				}
			}

			index++;
		}
	}
	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end());
}

void BottomViewportController::_deleteConsoleMessage(const string& id)
{
	auto window = _gui->getBottomViewport()->getWindow("console");
	auto screen = window->getScreen("main");

	screen->deleteTextField(id + "_time");

	screen->deleteTextField(id + "_separator");

	unsigned int index = 0;
	while(screen->isTextFieldExisting(id + "_msg_" + to_string(index)))
	{
		screen->deleteTextField(id + "_msg_" + to_string(index));
		index++;
	}
}