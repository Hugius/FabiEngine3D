#include "bottom_viewport_controller.hpp"

void BottomViewportController::_updateConsoleScrolling()
{
	// No scrolling for empty console
	if (!_consoleMessageStack.empty())
	{
		// Handy values
		auto window = _gui.getViewport("bottom")->getWindow("console");
		auto screen = window->getScreen("main");
		float minY = window->getOriginalPosition().y - (window->getOriginalSize().y / 2.0f);
		float maxY = window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f);
		float oldestMessage = _fe3d.textEntity_getPosition(screen->getTextfield(_consoleMessageStack[0].first + "_time")->getEntityID()).y + _charSize.y;
		float scrollValue = static_cast<float>(_fe3d.input_getMouseWheelY()) * static_cast<float>(window->isHovered());

		// Calculate message part count for latest message Y
		const string latestMessageID = _consoleMessageStack.back().first;
		const string entityID = screen->getTextfield(latestMessageID + "_msg_0")->getEntityID();
		float latestMessageY = _fe3d.textEntity_getPosition(entityID).y - _charSize.y;

		// Count all message text lines
		int messageLineCount = _consoleMessageStack.size();
		for (auto& [ID, message] : _consoleMessageStack)
		{
			// If a message is too long for 1 line, count all the text lines
			int count = 0;
			while (screen->getTextfield(ID + "_msg_" + to_string(count)) != nullptr) 
			{
				count++;
			}
			if (count > 1)
			{
				messageLineCount += (count - 1);
			}
		}

		// Check if there are enough messages to scroll through
		if ((static_cast<float>(messageLineCount) * _charSize.y) > window->getOriginalSize().y)
		{
			// Update acceleration
			_scrollingAcceleration += (scrollValue * 0.01f);
			_scrollingAcceleration *= 0.95f;

			// Only allow scrolling when not trying to scroll too far
			if ((latestMessageY == minY && _scrollingAcceleration < 0.0f) || (oldestMessage == maxY && scrollValue > 0.0f))
			{
				_scrollingAcceleration = 0.0f;
			}

			// Reset scrolling Y when scrolled too far
			bool resetY = false;
			if (latestMessageY > minY)
			{
				_scrollingAcceleration = latestMessageY - minY;
				resetY = true;
			}
			else if (oldestMessage < maxY)
			{
				_scrollingAcceleration = oldestMessage - maxY;
				resetY = true;
			}

			// Move all messages
			for (auto& [ID, message] : _consoleMessageStack)
			{
				// Move time part
				_fe3d.textEntity_move(screen->getTextfield(ID + "_time")->getEntityID(), Vec2(0.0f, -_scrollingAcceleration));

				// Move separator part
				_fe3d.textEntity_move(screen->getTextfield(ID + "_separator")->getEntityID(), Vec2(0.0f, -_scrollingAcceleration));

				// Move all message parts
				unsigned int index = 0;
				while (screen->getTextfield(ID + "_msg_" + to_string(index)) != nullptr)
				{
					_fe3d.textEntity_move(screen->getTextfield(ID + "_msg_" + to_string(index))->getEntityID(), Vec2(0.0f, -_scrollingAcceleration));
					index++;
				}
			}

			// Console not scrolling
			if (resetY)
			{
				_scrollingAcceleration = 0.0f;
			}
		}
	}
}

void BottomViewportController::_addConsoleMessage(const string& newMessage)
{
	//Temporary values
	auto window = _gui.getViewport("bottom")->getWindow("console");
	auto screen = window->getScreen("main");
	const unsigned int timePartLength = 10;
	const unsigned int seperatorPartLength = 3;
	const float yOffset = 0.2f; // Vertical offset between messages
	const float timePartOffset = _charSize.x * static_cast<float>(timePartLength) * 2.0f; // Offset from time part
	const float separatorPartOffset = _charSize.x * static_cast<float>(seperatorPartLength) * 2.0f; // Offset from separator part
	const Vec2 minPosition = Vec2(-1.0f, window->getOriginalPosition().y - (window->getOriginalSize().y / 2.0f));
	const Vec2 maxPosition = Vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f));

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
		const string timePartText = message.substr(typePartLength, timePartLength); // Time text" [HH:MM::SS]
		const string separatorPartText = message.substr(typePartLength + timePartLength, seperatorPartLength); // Seperator part
		string messagePartText = message.substr(typePartLength + timePartLength + seperatorPartLength); // Message part

		// Check if message part takes multiple lines
		vector<string> messageParts;
		begin:
		for (size_t i = 0; i < messagePartText.size(); i++)
		{
			// Check if message length is bigger than window size
			float offset = _charSize.x * static_cast<float>(timePartLength + 3);
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
					screen->convertPosition(Vec2(-1.0f, (-1.0f + yOffset) + (floatIndex * yOffset))));
				_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_separator")->getEntityID(), 
					screen->convertPosition(Vec2(-1.0f + timePartOffset, (-1.0f + yOffset) + (floatIndex * yOffset))));
			}
			else // New message
			{
				// Add time textfield & add boundaries
				screen->addTextfield(ID + "_time", Vec2(-1.0f, (-1.0f + yOffset) + (floatIndex * yOffset)), Vec2(0.0f), "", timePartColor, false);
				string timeID = screen->getTextfield(ID + "_time")->getEntityID();
				_fe3d.textEntity_setTextContent(timeID, timePartText, _charSize.x, _charSize.y);
				_fe3d.textEntity_setMinPosition(timeID, minPosition);
				_fe3d.textEntity_setMaxPosition(timeID, maxPosition);

				// Add separator textfield & add boundaries
				screen->addTextfield(ID + "_separator", Vec2(-1.0f + timePartOffset, (-1.0f + yOffset) + (floatIndex * yOffset)), Vec2(0.0f), "", separatorPartColor, false);
				string separatorID = screen->getTextfield(ID + "_separator")->getEntityID();
				_fe3d.textEntity_setTextContent(separatorID, separatorPartText, _charSize.x, _charSize.y);
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
					screen->convertPosition(Vec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + yOffset) + (floatIndex * yOffset))));
			}
			else // New message
			{
				// Add message part
				screen->addTextfield(textfieldID, Vec2(-1.0f + timePartOffset + separatorPartOffset, (-1.0f + yOffset) + (floatIndex * yOffset)),
					Vec2(0.0f), "", messagePartColor, false);
				_fe3d.textEntity_setTextContent(screen->getTextfield(textfieldID)->getEntityID(), messageParts[i], _charSize.x, _charSize.y);

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
						screen->convertPosition(Vec2(-1.0f, (-1.0f + yOffset) + (floatIndex * yOffset))));
					_fe3d.textEntity_setPosition(screen->getTextfield(ID + "_separator")->getEntityID(), 
						screen->convertPosition(Vec2(-1.0f + timePartOffset, (-1.0f + yOffset) + (floatIndex * yOffset))));
				}
				else // New message
				{
					// Add time textfield & add boundaries
					screen->addTextfield(ID + "_time", Vec2(-1.0f, (-1.0f + yOffset) + (floatIndex * yOffset)), Vec2(0.0f), "", timePartColor, false);
					string timeID = screen->getTextfield(ID + "_time")->getEntityID();
					_fe3d.textEntity_setTextContent(timeID, timePartText, _charSize.x, _charSize.y);
					_fe3d.textEntity_setMinPosition(timeID, minPosition);
					_fe3d.textEntity_setMaxPosition(timeID, maxPosition);

					// Add separator textfield & add boundaries
					screen->addTextfield(ID + "_separator", Vec2(-1.0f + timePartOffset, (-1.0f + yOffset) + (floatIndex * yOffset)), Vec2(0.0f), "", separatorPartColor, false);
					string separatorID = screen->getTextfield(ID + "_separator")->getEntityID();
					_fe3d.textEntity_setTextContent(separatorID, separatorPartText, _charSize.x, _charSize.y);
					_fe3d.textEntity_setMinPosition(separatorID, minPosition);
					_fe3d.textEntity_setMaxPosition(separatorID, maxPosition);
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