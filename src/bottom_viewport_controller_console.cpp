#include "bottom_viewport_controller.hpp"
#include "logger.hpp"
#include "configuration.hpp"

void BottomViewportController::_updateConsole()
{
	const auto loggerMessageList = Logger::getMessageQueue();
	const auto loggerMessageCount = Logger::getMessageCount();

	if(_consoleMessageQueue.size() != loggerMessageList.size())
	{
		const auto synchronizationCount = static_cast<unsigned int>(loggerMessageList.size() - _consoleMessageQueue.size());

		for(unsigned int index = loggerMessageCount - synchronizationCount; index < loggerMessageCount; index++)
		{
			_createConsoleMessage(loggerMessageList[index]);
		}
	}
}

void BottomViewportController::_createConsoleMessage(const string & newMessage)
{
	/*auto window = _gui->getBottomViewport()->getWindow("console");
	auto screen = window->getScreen("main");
	const float timePartOffset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH) * 2.0f;
	const float separatorPartOffset = CHAR_SIZE.x * static_cast<float>(SEPARATOR_PART_LENGTH) * 2.0f;
	const fvec2 minPosition = fvec2(-1.0f, window->getPosition().y - (window->getSize().y * 0.5f));
	const fvec2 maxPosition = fvec2(0.995f, window->getPosition().y + (window->getSize().y * 0.5f));

	const auto newId = to_string(_consoleMessageQueue.size());
	_consoleMessageQueue.push_back({newId, newMessage});

	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end());
	unsigned int messageIndex = 0;
	for(const auto & [key, message] : _consoleMessageQueue)
	{
		bool alreadyExisting = screen->hasTextField(key + "_time");
		float floatIndex = static_cast<float>(messageIndex);
		fvec3 timePartColor = fvec3(1.0f, 0.0f, 1.0f);
		fvec3 separatorPartColor = fvec3(1.0f, 0.85f, 0.0f);

		unsigned int typePartLength = 0;
		string typeString = "";
		for(unsigned int index = 0; index < static_cast<unsigned int>(message.size()); index++)
		{
			typeString.push_back(message[index]);

			if(message[index] == ']')
			{
				typePartLength = static_cast<unsigned int>(index + 1);
				break;
			}
		}

		const fvec3 messagePartColor = ((typeString == "[Warn]") ? fvec3(1.0f, 0.0f, 0.0f) : (typeString == "[Debug]") ? fvec3(1.0f, 0.25f, 0.0f) : fvec3(1.0f));

		const string timePartText = message.substr(typePartLength, TIME_PART_LENGTH);
		const string separatorPartText = message.substr((typePartLength + TIME_PART_LENGTH), SEPARATOR_PART_LENGTH);
		string messagePartText = message.substr((typePartLength + TIME_PART_LENGTH) + SEPARATOR_PART_LENGTH);

		vector<string> messageParts;
		BEGIN:;
		for(unsigned int index = 0; index < static_cast<unsigned int>(messagePartText.size()); index++)
		{
			float offset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH + 3);
			if(offset + (static_cast<float>(index) * CHAR_SIZE.x) > window->getSize().x)
			{
				messageParts.push_back(messagePartText.substr(0, index));

				messagePartText = messagePartText.substr(index, messagePartText.size() - index);
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

		for(unsigned int index = 0; index < static_cast<unsigned int>(messageParts.size()); index++)
		{
			floatIndex = static_cast<float>(messageIndex);

			string textFieldId = key + "_msg_" + to_string(index);

			if(alreadyExisting)
			{
				_fe3d->text2d_setPosition(screen->getTextField(textFieldId)->getEntityId(),
										  screen->convertPosition(fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else
			{
				screen->createTextField(textFieldId, fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)),
										fvec2(0.0f), "", messagePartColor, false);

				_fe3d->text2d_setContent(screen->getTextField(textFieldId)->getEntityId(), messageParts[index]);
				_fe3d->text2d_setSize(screen->getTextField(textFieldId)->getEntityId(), fvec2(CHAR_SIZE.x * static_cast<float>(messageParts[index].size()), CHAR_SIZE.y));

				_fe3d->text2d_setMinPosition(screen->getTextField(textFieldId)->getEntityId(), minPosition);
				_fe3d->text2d_setMaxPosition(screen->getTextField(textFieldId)->getEntityId(), maxPosition);
			}

			if((messageParts.size() > 1) && index == (messageParts.size() - 1))
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

			messageIndex++;
		}
	}
	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end());*/
}

void BottomViewportController::_deleteConsoleMessage(const string & id)
{
	auto window = _gui->getBottomViewport()->getWindow("console");
	auto screen = window->getScreen("main");

	screen->deleteTextField(id + "_time");

	screen->deleteTextField(id + "_separator");

	unsigned int index = 0;
	while(screen->hasTextField(id + "_msg_" + to_string(index)))
	{
		screen->deleteTextField(id + "_msg_" + to_string(index));
		index++;
	}
}