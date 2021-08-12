#include "bottom_viewport_controller.hpp"

void BottomViewportController::_updateConsoleScrolling()
{
	// Temporary values
	const auto window = _gui.getViewport("bottom")->getWindow("console");
	float scrollingSpeed = static_cast<float>(_fe3d.input_getMouseWheelY()) * static_cast<float>(window->isHovered()) * 0.1f;

	// No scrolling for empty console
	if (!_consoleMessageQueue.empty() && scrollingSpeed != 0.0f)
	{
		// Temporary values
		const auto screen = window->getScreen("main");
		const float minY = window->getOriginalPosition().y - (window->getOriginalSize().y / 2.0f);
		const float maxY = window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f);
		const float oldestMessage = _fe3d.textEntity_getPosition(screen->getTextfield(_consoleMessageQueue[0].first + "_time")->getEntityID()).y + CHAR_SIZE.y;

		// Calculate message part count for latest message Y
		const string latestMessageID = _consoleMessageQueue.back().first;
		const string entityID = screen->getTextfield(latestMessageID + "_msg_0")->getEntityID();
		float latestMessageY = _fe3d.textEntity_getPosition(entityID).y - CHAR_SIZE.y;

		// Count all message text lines
		unsigned int messageLineCount = static_cast<unsigned int>(_consoleMessageQueue.size());
		for (const auto& [ID, message] : _consoleMessageQueue)
		{
			// If a message is too long for 1 line, count all the text lines
			int count = 0;
			while (screen->getTextfield(ID + "_msg_" + to_string(count)) != nullptr)
			{
				count++;
			}
			if (count > 1)
			{
				messageLineCount += static_cast<unsigned int>(count - 1);
			}
		}

		// Check if there are enough messages to scroll through
		if ((static_cast<float>(messageLineCount) * CHAR_SIZE.y) > window->getOriginalSize().y)
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
			for (const auto& [ID, message] : _consoleMessageQueue)
			{
				// Move time part
				_fe3d.textEntity_move(screen->getTextfield(ID + "_time")->getEntityID(), Vec2(0.0f, -scrollingSpeed));

				// Move separator part
				_fe3d.textEntity_move(screen->getTextfield(ID + "_separator")->getEntityID(), Vec2(0.0f, -scrollingSpeed));

				// Move all message parts
				unsigned int index = 0;
				while (screen->getTextfield(ID + "_msg_" + to_string(index)) != nullptr)
				{
					_fe3d.textEntity_move(screen->getTextfield(ID + "_msg_" + to_string(index))->getEntityID(), Vec2(0.0f, -scrollingSpeed));
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
	const Vec2 minPosition = Vec2(-1.0f, window->getOriginalPosition().y - (window->getOriginalSize().y / 2.0f));
	const Vec2 maxPosition = Vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f));

	// Add to stack for synchronization
	string newID = to_string(_consoleMessageQueue.size());
	_consoleMessageQueue.push_back(make_pair(newID, newMessage));

	// Reposition previous messages & add new message
	reverse(_consoleMessageQueue.begin(), _consoleMessageQueue.end()); // Console prints reversed
	unsigned int index = 0;
	for (const auto& [ID, message] : _consoleMessageQueue)
	{
		// Temporary values
		bool alreadyExisting = screen->checkTextfield(ID + "_time");
		float floatIndex = static_cast<float>(index);
		Vec3 timePartColor = Vec3(1.0f, 0.0f, 1.0f);
		Vec3 separatorPartColor = Vec3(1.0f, 0.85f, 0.0f);
		Vec3 messagePartColor = Vec3(1.0f);

		// Extract message type
		unsigned int typePartLength = 0;
		string typeString = "";
		for (size_t i = 0; i < message.size(); i++)
		{
			// Add current character
			typeString.push_back(message[i]);

			// Check if type text ended
			if (message[i] == ']')
			{
				typePartLength = static_cast<unsigned int>(i + 1);
				break;
			}
		}

		// Check if message is a warning, aka an "error" for the engine user
		if (typeString == "[Warn]")
		{
			messagePartColor = Vec3(1.0f, 0.0f, 0.0f);
		}

		// Different parts
		const string timePartText = message.substr(typePartLength, TIME_PART_LENGTH); // Time text" [HH:MM::SS]
		const string separatorPartText = message.substr(typePartLength + TIME_PART_LENGTH, SEPARATOR_PART_LENGTH); // Seperator part
		string messagePartText = message.substr(typePartLength + TIME_PART_LENGTH + SEPARATOR_PART_LENGTH); // Message part

		// Check if message part takes multiple lines
		vector<string> messageParts;
	BEGIN:
		for (size_t i = 0; i < messagePartText.size(); i++)
		{
			// Check if message length is bigger than window size
			float offset = CHAR_SIZE.x * static_cast<float>(TIME_PART_LENGTH + 3);
			if (offset + (static_cast<float>(i) * CHAR_SIZE.x) > window->getOriginalSize().x)
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
		if (messageParts.size() == 1)
		{
			if (alreadyExisting) // Previous message
			{
				_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_time")->getEntityID(), 
					screen->convertPosition(Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_separator")->getEntityID(), 
					screen->convertPosition(Vec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else // New message
			{
				// Add time textfield & add boundaries
				screen->createTextfield(ID + "_time", Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", timePartColor, false);
				string timeID = screen->getTextfield(ID + "_time")->getEntityID();
				_fe3d.textEntity_setTextContent(timeID, timePartText, CHAR_SIZE.x, CHAR_SIZE.y);
				_fe3d.textEntity_setMinPosition(timeID, minPosition);
				_fe3d.textEntity_setMaxPosition(timeID, maxPosition);

				// Add separator textfield & add boundaries
				screen->createTextfield(ID + "_separator", Vec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", separatorPartColor, false);
				string separatorID = screen->getTextfield(ID + "_separator")->getEntityID();
				_fe3d.textEntity_setTextContent(separatorID, separatorPartText, CHAR_SIZE.x, CHAR_SIZE.y);
				_fe3d.textEntity_setMinPosition(separatorID, minPosition);
				_fe3d.textEntity_setMaxPosition(separatorID, maxPosition);
			}
		}
		else // Console prints multiple lines reversed
		{
			reverse(messageParts.begin(), messageParts.end());
		}

		// Add textfield for every message part
		for (size_t i = 0; i < messageParts.size(); i++)
		{
			// Update floatcasted index
			floatIndex = static_cast<float>(index);

			// ID for this message part
			string textfieldID = ID + "_msg_" + to_string(i);

			if (alreadyExisting) // Previous message
			{
				_fe3d.textEntity_setPosition(screen->getTextfield(textfieldID)->getEntityID(),
					screen->convertPosition(Vec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else // New message
			{
				// Add message part
				screen->createTextfield(textfieldID, Vec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)),
					Vec2(0.0f), "", messagePartColor, false);
				_fe3d.textEntity_setTextContent(screen->getTextfield(textfieldID)->getEntityID(), messageParts[i], CHAR_SIZE.x, CHAR_SIZE.y);

				// Add boundaries
				_fe3d.textEntity_setMinPosition(screen->getTextfield(textfieldID)->getEntityID(), minPosition);
				_fe3d.textEntity_setMaxPosition(screen->getTextfield(textfieldID)->getEntityID(), maxPosition);
			}

			// If printing the message in multiple parts, time & seperator should be printed last
			if ((messageParts.size() > 1) && i == (messageParts.size() - 1))
			{
				if (alreadyExisting) // Previous message
				{
					_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_time")->getEntityID(), 
						screen->convertPosition(Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
					_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_separator")->getEntityID(), 
						screen->convertPosition(Vec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				}
				else // New message
				{
					// Add time textfield & add boundaries
					screen->createTextfield(ID + "_time", Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", timePartColor, false);
					string timeID = screen->getTextfield(ID + "_time")->getEntityID();
					_fe3d.textEntity_setTextContent(timeID, timePartText, CHAR_SIZE.x, CHAR_SIZE.y);
					_fe3d.textEntity_setMinPosition(timeID, minPosition);
					_fe3d.textEntity_setMaxPosition(timeID, maxPosition);

					// Add separator textfield & add boundaries
					screen->createTextfield(ID + "_separator", Vec2(-1.0f + timePartOffset, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", separatorPartColor, false);
					string separatorID = screen->getTextfield(ID + "_separator")->getEntityID();
					_fe3d.textEntity_setTextContent(separatorID, separatorPartText, CHAR_SIZE.x, CHAR_SIZE.y);
					_fe3d.textEntity_setMinPosition(separatorID, minPosition);
					_fe3d.textEntity_setMaxPosition(separatorID, maxPosition);
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
	screen->deleteTextfield(ID + "_time");

	// Delete separator part
	screen->deleteTextfield(ID + "_separator");

	// Delete all message parts
	unsigned int index = 0;
	while (screen->getTextfield(ID + "_msg_" + to_string(index)) != nullptr)
	{
		screen->deleteTextfield(ID + "_msg_" + to_string(index));
		index++;
	}
}