#include "bottom_viewport_controller.hpp"

void BottomViewportController::_updateConsoleScrolling()
{
	// Temporary values
	const auto window = _gui.getViewport("bottom")->getWindow("console");
	float scrollingSpeed = static_cast<float>(_fe3d.input_getMouseWheelY()) * static_cast<float>(window->isHovered()) * 0.1f;

	// No scrolling for empty console
	if(!_consoleMessageQueue.empty() && scrollingSpeed != 0.0f)
	{
		// Temporary values
		const auto screen = window->getScreen("main");
		const float minY = window->getInitialPosition().y - (window->getInitialSize().y / 2.0f);
		const float maxY = window->getInitialPosition().y + (window->getInitialSize().y / 2.0f);
		const float oldestMessage = _fe3d.text_getPosition(screen->getTextField(_consoleMessageQueue[0].first + "_time")->getEntityID()).y + CHAR_SIZE.y;

		// Calculate message part count for latest message Y
		const string latestMessageID = _consoleMessageQueue.back().first;
		const string entityID = screen->getTextField(latestMessageID + "_msg_0")->getEntityID();
		float latestMessageY = _fe3d.text_getPosition(entityID).y - CHAR_SIZE.y;

		// Count all message text lines
		unsigned int messageLineCount = static_cast<unsigned int>(_consoleMessageQueue.size());
		for(const auto& [ID, message] : _consoleMessageQueue)
		{
			// If a message is too long for 1 line, count all the text lines
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

		// Check if there are enough messages to scroll through
		if((static_cast<float>(messageLineCount) * CHAR_SIZE.y) > window->getInitialSize().y)
		{
			// Only allow scrolling when not trying to scroll too far
			if
				(
				(latestMessageY >= minY && scrollingSpeed < 0.0f)
				||
				(oldestMessage <= maxY && scrollingSpeed > 0.0f)
				)
			{
				scrollingSpeed = 0.0f;
			}

			// Move all messages
			for(const auto& [ID, message] : _consoleMessageQueue)
			{
				// Move time part
				_fe3d.text_move(screen->getTextField(ID + "_time")->getEntityID(), fvec2(0.0f, -scrollingSpeed));

				// Move separator part
				_fe3d.text_move(screen->getTextField(ID + "_separator")->getEntityID(), fvec2(0.0f, -scrollingSpeed));

				// Move all message parts
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
	// Temporary values
	auto window = _gui.getViewport("bottom")->getWindow("console");
	auto screen = window->getScreen("main");
	const float timePartOffset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH) * 2.0f; // Offset from time part
	const float separatorPartOffset = CHAR_SIZE.x * static_cast<float>(SEPARATOR_PART_LENGTH) * 2.0f; // Offset from separator part
	const fvec2 minPosition = fvec2(-1.0f, window->getInitialPosition().y - (window->getInitialSize().y / 2.0f));
	const fvec2 maxPosition = fvec2(0.995f, window->getInitialPosition().y + (window->getInitialSize().y / 2.0f));

	// Add to stack for synchronization
	string newID = to_string(_consoleMessageQueue.size());
	_consoleMessageQueue.push_back(make_pair(newID, newMessage));

	// Reposition previous messages & add new message
	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end()); // Console prints reversed
	unsigned int index = 0;
	for(const auto& [ID, message] : _consoleMessageQueue)
	{
		// Temporary values
		bool alreadyExisting = screen->isTextFieldExisting(ID + "_time");
		float floatIndex = static_cast<float>(index);
		fvec3 timePartColor = fvec3(1.0f, 0.0f, 1.0f);
		fvec3 separatorPartColor = fvec3(1.0f, 0.85f, 0.0f);

		// Extract message type
		unsigned int typePartLength = 0;
		string typeString = "";
		for(size_t i = 0; i < message.size(); i++)
		{
			// Add current character
			typeString.push_back(message[i]);

			// Check if type text ended
			if(message[i] == ']')
			{
				typePartLength = static_cast<unsigned int>(i + 1);
				break;
			}
		}

		// Choose message part color
		const fvec3 messagePartColor = ((typeString == "[Warn]") ? fvec3(1.0f, 0.0f, 0.0f) : (typeString == "[Debug]") ? fvec3(1.0f, 0.25f, 0.0f) : fvec3(1.0f));

		// Different parts
		const string timePartText = message.substr(typePartLength, TIME_PART_LENGTH); // Time text" [HH:MM::SS]
		const string separatorPartText = message.substr((typePartLength + TIME_PART_LENGTH), SEPARATOR_PART_LENGTH); // Seperator part
		string messagePartText = message.substr((typePartLength + TIME_PART_LENGTH) + SEPARATOR_PART_LENGTH); // Message part

		// Check if message part takes multiple lines
		vector<string> messageParts;
	BEGIN:
		for(size_t i = 0; i < messagePartText.size(); i++)
		{
			// Check if message length is bigger than window size
			float offset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH + 3);
			if(offset + (static_cast<float>(i) * CHAR_SIZE.x) > window->getInitialSize().x)
			{
				// Cut a part of the full message
				messageParts.push_back(messagePartText.substr(0, i));

				// Set the remaining message
				messagePartText = messagePartText.substr(i, messagePartText.size() - i);
				goto BEGIN;
			}
		}

		// Add remaining message part
		messageParts.push_back(messagePartText);

		// If printing full message, time & seperator should be printed first
		if(messageParts.size() == 1)
		{
			if(alreadyExisting) // Previous message
			{
				_fe3d.text_setPosition(screen->getTextField(ID + "_time")->getEntityID(),
											 screen->convertPosition(fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				_fe3d.text_setPosition(screen->getTextField(ID + "_separator")->getEntityID(),
											 screen->convertPosition(fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else // New message
			{
				// Add time TextField & add boundaries
				screen->createTextField(ID + "_time", fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", timePartColor, false, false);
				string timeID = screen->getTextField(ID + "_time")->getEntityID();
				_fe3d.text_setTextContent(timeID, timePartText, CHAR_SIZE.x, CHAR_SIZE.y);
				_fe3d.text_setMinPosition(timeID, minPosition);
				_fe3d.text_setMaxPosition(timeID, maxPosition);

				// Add separator TextField & add boundaries
				screen->createTextField(ID + "_separator", fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", separatorPartColor, false, false);
				string separatorID = screen->getTextField(ID + "_separator")->getEntityID();
				_fe3d.text_setTextContent(separatorID, separatorPartText, CHAR_SIZE.x, CHAR_SIZE.y);
				_fe3d.text_setMinPosition(separatorID, minPosition);
				_fe3d.text_setMaxPosition(separatorID, maxPosition);
			}
		}
		else // Console prints multiple lines reversed
		{
			reverse(messageParts.begin(), messageParts.end());
		}

		// Add TextField for every message part
		for(size_t i = 0; i < messageParts.size(); i++)
		{
			// Update floatcasted index
			floatIndex = static_cast<float>(index);

			// ID for this message part
			string TextFieldID = ID + "_msg_" + to_string(i);

			if(alreadyExisting) // Previous message
			{
				_fe3d.text_setPosition(screen->getTextField(TextFieldID)->getEntityID(),
											 screen->convertPosition(fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else // New message
			{
				// Add message part
				screen->createTextField(TextFieldID, fvec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)),
										fvec2(0.0f), "", messagePartColor, false, false);
				_fe3d.text_setTextContent(screen->getTextField(TextFieldID)->getEntityID(), messageParts[i], CHAR_SIZE.x, CHAR_SIZE.y);

				// Add boundaries
				_fe3d.text_setMinPosition(screen->getTextField(TextFieldID)->getEntityID(), minPosition);
				_fe3d.text_setMaxPosition(screen->getTextField(TextFieldID)->getEntityID(), maxPosition);
			}

			// If printing the message in multiple parts, time & seperator should be printed last
			if((messageParts.size() > 1) && i == (messageParts.size() - 1))
			{
				if(alreadyExisting) // Previous message
				{
					_fe3d.text_setPosition(screen->getTextField(ID + "_time")->getEntityID(),
												 screen->convertPosition(fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
					_fe3d.text_setPosition(screen->getTextField(ID + "_separator")->getEntityID(),
												 screen->convertPosition(fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				}
				else // New message
				{
					// Add time TextField & add boundaries
					screen->createTextField(ID + "_time", fvec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", timePartColor, false, false);
					string timeID = screen->getTextField(ID + "_time")->getEntityID();
					_fe3d.text_setTextContent(timeID, timePartText, CHAR_SIZE.x, CHAR_SIZE.y);
					_fe3d.text_setMinPosition(timeID, minPosition);
					_fe3d.text_setMaxPosition(timeID, maxPosition);

					// Add separator TextField & add boundaries
					screen->createTextField(ID + "_separator", fvec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), fvec2(0.0f), "", separatorPartColor, false, false);
					string separatorID = screen->getTextField(ID + "_separator")->getEntityID();
					_fe3d.text_setTextContent(separatorID, separatorPartText, CHAR_SIZE.x, CHAR_SIZE.y);
					_fe3d.text_setMinPosition(separatorID, minPosition);
					_fe3d.text_setMaxPosition(separatorID, maxPosition);
				}
			}

			// Update index for Y positioning of next messages
			index++;
		}
	}
	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end()); // Set order back to normal
}

void BottomViewportController::_deleteConsoleMessage(const string& ID)
{
	auto window = _gui.getViewport("bottom")->getWindow("console");
	auto screen = window->getScreen("main");

	// Delete time part
	screen->deleteTextField(ID + "_time");

	// Delete separator part
	screen->deleteTextField(ID + "_separator");

	// Delete all message parts
	unsigned int index = 0;
	while(screen->isTextFieldExisting(ID + "_msg_" + to_string(index)))
	{
		screen->deleteTextField(ID + "_msg_" + to_string(index));
		index++;
	}
}