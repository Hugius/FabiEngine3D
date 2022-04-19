#include "bottom_viewport_controller.hpp"
#include "logger.hpp"

void BottomViewportController::_updateConsole()
{
	const auto loggerMessageList = Logger::getMessageQueue();
	const auto loggerMessageCount = Logger::getMessageCount();

	if(_messageQueue.size() != loggerMessageList.size())
	{
		const auto synchronizationCount = static_cast<unsigned int>(loggerMessageList.size() - _messageQueue.size());

		_clearConsole();

		for(unsigned int index = loggerMessageCount - synchronizationCount; index < loggerMessageCount; index++)
		{
			if(_messageQueue.size() == MAX_MESSAGE_COUNT)
			{
				_messageQueue.erase(_messageQueue.begin());
			}

			_messageQueue.push_back(loggerMessageList[index]);
		}

		_fillConsole();
	}
}

void BottomViewportController::_fillConsole()
{
	const auto window = _gui->getBottomViewport()->getWindow("console");
	const auto screen = window->getScreen("main");
	const auto messageCount = static_cast<unsigned int>(_messageQueue.size());
	const auto minPosition = fvec2(-1.0f, window->getPosition().y - (window->getSize().y * 0.5f));
	const auto maxPosition = fvec2(1.0f, window->getPosition().y + (window->getSize().y * 0.5f));

	for(unsigned int index = 0; index < messageCount; index++)
	{
		const auto messageText = _messageQueue[index];
		const auto timeText = messageText.substr(0, MESSAGE_TIME_SIZE);
		const auto contentText = messageText.substr(messageText.find(">") + 2);
		const auto height = (-1.0f + (static_cast<float>(messageCount - index - 1) * CHAR_SIZE.y));
		const auto timeSize = fvec2((static_cast<float>(MESSAGE_TIME_SIZE) * CHAR_SIZE.x), CHAR_SIZE.y);
		const auto contentSize = fvec2((static_cast<float>(contentText.size()) * CHAR_SIZE.x), CHAR_SIZE.y);
		const auto isWarning = (messageText.substr(MESSAGE_TIME_SIZE, 7) == " [WARN]");

		screen->createTextField(("time_" + to_string(index)), fvec2(-1.0f, height), timeSize, timeText, TIME_COLOR, false);
		screen->createTextField(("content_" + to_string(index)), fvec2((-1.0f + timeSize.x + CHAR_SIZE.x), height), contentSize, contentText, (isWarning ? WARN_COLOR : INFO_COLOR), false);

		screen->getTextField("time_" + to_string(index))->setMinPosition(minPosition);
		screen->getTextField("time_" + to_string(index))->setMaxPosition(maxPosition);
		screen->getTextField("content_" + to_string(index))->setMinPosition(minPosition);
		screen->getTextField("content_" + to_string(index))->setMaxPosition(maxPosition);
	}
}

void BottomViewportController::_clearConsole()
{
	const auto screen = _gui->getBottomViewport()->getWindow("console")->getScreen("main");
	const auto messageCount = static_cast<unsigned int>(_messageQueue.size());

	for(unsigned int index = 0; index < messageCount; index++)
	{
		screen->deleteTextField("time_" + to_string(index));
		screen->deleteTextField("content_" + to_string(index));
	}
}