#include "bottom_viewport_controller.hpp"

void BottomViewportController::_updateConsoleScrolling()
{
	// Temporary values
	const auto WINDOW = _gui.getViewport("bottom")->getWindow("console");
	float scrollingSpeed = static_cast<float>(_fe3d.input_getMouseWheelY()) * static_cast<float>(WINDOW->isHovered()) * 0.1f;

	// No scrolling for empty console
	if (!_consoleMessageStack.empty() && scrollingSpeed != 0.0f)
	{
		// Temporary values
		const auto SCREEN = WINDOW->getScreen("main");
		const float MIN_Y = WINDOW->getOriginalPosition().y - (WINDOW->getOriginalSize().y / 2.0f);
		const float MAX_Y = WINDOW->getOriginalPosition().y + (WINDOW->getOriginalSize().y / 2.0f);
		const float OLDEST_MESSAGE = _fe3d.textEntity_getPosition(SCREEN->getTextfield(_consoleMessageStack[0].first + "_time")->getEntityID()).y + _charSize.y;

		// Calculate message part count for latest message Y
		const string LATEST_MESSAGE_ID = _consoleMessageStack.back().first;
		const string ENTITY_ID = SCREEN->getTextfield(LATEST_MESSAGE_ID + "_msg_0")->getEntityID();
		float latestMessageY = _fe3d.textEntity_getPosition(ENTITY_ID).y - _charSize.y;

		// Count all message text lines
		unsigned int messageLineCount = _consoleMessageStack.size();
		for (auto& [ID, message] : _consoleMessageStack)
		{
			// If a message is too long for 1 line, count all the text lines
			int count = 0;
			while (SCREEN->getTextfield(ID + "_msg_" + to_string(count)) != nullptr)
			{
				count++;
			}
			if (count > 1)
			{
				messageLineCount += (count - 1);
			}
		}

		// Check if there are enough messages to scroll through
		if ((static_cast<float>(messageLineCount) * _charSize.y) > WINDOW->getOriginalSize().y)
		{
			// Only allow scrolling when not trying to scroll too far
			if 
			(
				(latestMessageY >= MIN_Y && scrollingSpeed < 0.0f)
				|| 
				(OLDEST_MESSAGE <= MAX_Y && scrollingSpeed > 0.0f)
			)
			{
				scrollingSpeed = 0.0f;
			}

			// Move all messages
			for (auto& [ID, message] : _consoleMessageStack)
			{
				// Move time part
				_fe3d.textEntity_move(SCREEN->getTextfield(ID + "_time")->getEntityID(), Vec2(0.0f, -scrollingSpeed));

				// Move separator part
				_fe3d.textEntity_move(SCREEN->getTextfield(ID + "_separator")->getEntityID(), Vec2(0.0f, -scrollingSpeed));

				// Move all message parts
				unsigned int index = 0;
				while (SCREEN->getTextfield(ID + "_msg_" + to_string(index)) != nullptr)
				{
					_fe3d.textEntity_move(SCREEN->getTextfield(ID + "_msg_" + to_string(index))->getEntityID(), Vec2(0.0f, -scrollingSpeed));
					index++;
				}
			}
		}
	}
}

void BottomViewportController::_addConsoleMessage(const string& newMessage)
{
	//Temporary values
	auto window = _gui.getViewport("bottom")->getWindow("console");
	auto screen = window->getScreen("main");
	const unsigned int TIME_PART_LENGTH = 10;
	const unsigned int SEPARATOR_PART_LENGTH = 3;
	const float Y_OFFSET = 0.2f; // Vertical offset between messages
	const float TIME_PART_OFFSET = _charSize.x * static_cast<float>(TIME_PART_LENGTH) * 2.0f; // Offset from time part
	const float SEPARATOR_PART_OFFSET = _charSize.x * static_cast<float>(SEPARATOR_PART_LENGTH) * 2.0f; // Offset from separator part
	const Vec2 MIN_POSITION = Vec2(-1.0f, window->getOriginalPosition().y - (window->getOriginalSize().y / 2.0f));
	const Vec2 MAX_POSITION = Vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f));

	// Add to stack for synchronization
	string newID = to_string(_consoleMessageStack.size());
	_consoleMessageStack.push_back(make_pair(newID, newMessage));

	// Reposition previous messages & add new message
	reverse(_consoleMessageStack.begin(), _consoleMessageStack.end()); // Console prints reversed
	unsigned int index = 0;
	for (auto& [ID, message] : _consoleMessageStack)
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
				typePartLength = i + 1;
				break;
			}
		}

		// Check if message is a warning, aka an "error" for the engine user
		if (typeString == "[Warn]")
		{
			messagePartColor = Vec3(1.0f, 0.0f, 0.0f);
		}

		// Different parts
		const string TIME_PART_TEXT = message.substr(typePartLength, TIME_PART_LENGTH); // Time text" [HH:MM::SS]
		const string SEPARATOR_PART_TEXT = message.substr(typePartLength + TIME_PART_LENGTH, SEPARATOR_PART_LENGTH); // Seperator part
		string messagePartText = message.substr(typePartLength + TIME_PART_LENGTH + SEPARATOR_PART_LENGTH); // Message part

		// Check if message part takes multiple lines
		vector<string> messageParts;
		begin:
		for (size_t i = 0; i < messagePartText.size(); i++)
		{
			// Check if message length is bigger than window size
			float offset = _charSize.x * static_cast<float>(TIME_PART_LENGTH + 3);
			if (offset + (static_cast<float>(i) * _charSize.x) > window->getOriginalSize().x)
			{
				// Cut a part of the full message
				messageParts.push_back(messagePartText.substr(0, i));

				// Set the remaining message
				messagePartText = messagePartText.substr(i, messagePartText.size() - i);
				goto begin;
			}
		}

		// Add remaining message part
		messageParts.push_back(messagePartText);

		// If printing full message, time & seperator should be printed first
		if (messageParts.size() == 1)
		{
			if(alreadyExisting) // Previous message
			{
				_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_time")->getEntityID(), 
					screen->convertPosition(Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_separator")->getEntityID(), 
					screen->convertPosition(Vec2(-1.0f + TIME_PART_OFFSET, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else // New message
			{
				// Add time textfield & add boundaries
				screen->addTextfield(ID + "_time", Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", timePartColor, false);
				string timeID = screen->getTextfield(ID + "_time")->getEntityID();
				_fe3d.textEntity_setTextContent(timeID, TIME_PART_TEXT, _charSize.x, _charSize.y);
				_fe3d.textEntity_setMinPosition(timeID, MIN_POSITION);
				_fe3d.textEntity_setMaxPosition(timeID, MAX_POSITION);

				// Add separator textfield & add boundaries
				screen->addTextfield(ID + "_separator", Vec2(-1.0f + TIME_PART_OFFSET, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", separatorPartColor, false);
				string separatorID = screen->getTextfield(ID + "_separator")->getEntityID();
				_fe3d.textEntity_setTextContent(separatorID, SEPARATOR_PART_TEXT, _charSize.x, _charSize.y);
				_fe3d.textEntity_setMinPosition(separatorID, MIN_POSITION);
				_fe3d.textEntity_setMaxPosition(separatorID, MAX_POSITION);
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
					screen->convertPosition(Vec2(-1.0f + TIME_PART_OFFSET + SEPARATOR_PART_OFFSET, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
			}
			else // New message
			{
				// Add message part
				screen->addTextfield(textfieldID, Vec2(-1.0f + TIME_PART_OFFSET + SEPARATOR_PART_OFFSET, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)),
					Vec2(0.0f), "", messagePartColor, false);
				_fe3d.textEntity_setTextContent(screen->getTextfield(textfieldID)->getEntityID(), messageParts[i], _charSize.x, _charSize.y);

				// Add boundaries
				_fe3d.textEntity_setMinPosition(screen->getTextfield(textfieldID)->getEntityID(), MIN_POSITION);
				_fe3d.textEntity_setMaxPosition(screen->getTextfield(textfieldID)->getEntityID(), MAX_POSITION);
			}

			// If printing the message in multiple parts, time & seperator should be printed last
			if ((messageParts.size() > 1) && i == (messageParts.size() - 1))
			{
				if (alreadyExisting) // Previous message
				{
					_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_time")->getEntityID(), 
						screen->convertPosition(Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
					_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_separator")->getEntityID(), 
						screen->convertPosition(Vec2(-1.0f + TIME_PART_OFFSET, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET))));
				}
				else // New message
				{
					// Add time textfield & add boundaries
					screen->addTextfield(ID + "_time", Vec2(-1.0f, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", timePartColor, false);
					string timeID = screen->getTextfield(ID + "_time")->getEntityID();
					_fe3d.textEntity_setTextContent(timeID, TIME_PART_TEXT, _charSize.x, _charSize.y);
					_fe3d.textEntity_setMinPosition(timeID, MIN_POSITION);
					_fe3d.textEntity_setMaxPosition(timeID, MAX_POSITION);

					// Add separator textfield & add boundaries
					screen->addTextfield(ID + "_separator", Vec2(-1.0f + TIME_PART_OFFSET, (-1.0f + Y_OFFSET) + (floatIndex * Y_OFFSET)), Vec2(0.0f), "", separatorPartColor, false);
					string separatorID = screen->getTextfield(ID + "_separator")->getEntityID();
					_fe3d.textEntity_setTextContent(separatorID, SEPARATOR_PART_TEXT, _charSize.x, _charSize.y);
					_fe3d.textEntity_setMinPosition(separatorID, MIN_POSITION);
					_fe3d.textEntity_setMaxPosition(separatorID, MAX_POSITION);
				}
			}

			// Update index for Y positioning of next messages
			index++;
		}
	}
	reverse(_consoleMessageStack.begin(), _consoleMessageStack.end()); // Set order back to normal
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