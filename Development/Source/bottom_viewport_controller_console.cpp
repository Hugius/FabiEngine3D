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
		int messagePartCount = 0;
		const string latestMessageID = _consoleMessageStack.back().first;
		while (screen->getTextfield(latestMessageID + "_msg_" + to_string(messagePartCount)) != nullptr)
		{
			messagePartCount++;
		}
		const string entityID = screen->getTextfield(latestMessageID + "_msg_" + to_string(messagePartCount - 1))->getEntityID();
		float latestMessageY = _fe3d.textEntity_getPosition(entityID).y - _charSize.y;

		// Count all message text lines
		int messageLineCount = _consoleMessageStack.size();
		for (auto& [ID, message] : _consoleMessageStack)
		{
			// If a message is too long for 1 line, count all the text lines
			int count = 0;
			while (screen->getTextfield(ID + "_msg_" + to_string(count++)) != nullptr) {}
			if (count > 1)
			{
				messageLineCount += count;
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
				_fe3d.textEntity_move(screen->getTextfield(ID + "_time")->getEntityID(), vec2(0.0f, -_scrollingAcceleration));

				// Move separator part
				_fe3d.textEntity_move(screen->getTextfield(ID + "_separator")->getEntityID(), vec2(0.0f, -_scrollingAcceleration));

				// Move all message parts
				int index = 0;
				while (screen->getTextfield(ID + "_msg_" + to_string(index)) != nullptr)
				{
					_fe3d.textEntity_move(screen->getTextfield(ID + "_msg_" + to_string(index))->getEntityID(), vec2(0.0f, -_scrollingAcceleration));
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
	// Handy values
	auto window = _gui.getViewport("bottom")->getWindow("console");
	auto screen = window->getScreen("main");

	// Add to stack for synchronization
	string newID = to_string(_consoleMessageStack.size());
	_consoleMessageStack.push_back(make_pair(newID, newMessage));

	// Remove console message textfields
	for (auto& [ID, message] : _consoleMessageStack)
	{
		// Can only delete old textfields
		if (ID != newID)
		{
			// Delete time part
			screen->deleteTextfield(ID + "_time");

			// Delete separator part
			screen->deleteTextfield(ID + "_separator");

			// Delete all message parts
			int index = 0;
			while (screen->getTextfield(ID + "_msg_" + to_string(index)) != nullptr)
			{
				screen->deleteTextfield(ID + "_msg_" + to_string(index));
				index++;
			}
		}
	}

	// Generate everything again
	reverse(_consoleMessageStack.begin(), _consoleMessageStack.end()); // Console prints reversed
	unsigned int index = 0;
	for (auto& [ID, message] : _consoleMessageStack)
	{
		// Part colors
		vec3 timePartColor = vec3(1.0f, 0.0f, 1.0f);
		vec3 separatorPartColor = vec3(1.0f, 0.85f, 0.0f);
		vec3 messagePartColor = vec3(1.0f);

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
			messagePartColor = vec3(1.0f, 0.0f, 0.0f);
		}

		// Different parts
		const unsigned int timePartLength = 10;
		const unsigned int seperatorPartLength = 3;
		const float yOffset = 0.2f; // Vertical offset between messages
		const float timePartOffset = _charSize.x * static_cast<float>(timePartLength) * 2.0f; // Offset from time part
		const float separatorPartOffset = _charSize.x * static_cast<float>(seperatorPartLength) * 2.0f; // Offset from separator part
		const string timePartText = message.substr(typePartLength, timePartLength); // Time text" [HH:MM::SS]
		const string separatorPartText = message.substr(typePartLength + timePartLength, seperatorPartLength); // Seperator part
		string messagePartText = message.substr(typePartLength + timePartLength + seperatorPartLength); // Message part

		// Check if message part takes multiple lines
		vector<string> messageParts;
		begin: for (size_t i = 0; i < messagePartText.size(); i++)
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
			// Add time textfield & add boundaries
			screen->addTextfield(ID + "_time", vec2(-1.0f, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", timePartColor, false);
			_fe3d.textEntity_setTextContent(screen->getTextfield(ID + "_time")->getEntityID(), timePartText, _charSize.x, _charSize.y);
			_fe3d.textEntity_setMaxPosition(screen->getTextfield(ID + "_time")->getEntityID(),
				vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));

			// Add separator textfield & add boundaries
			screen->addTextfield(ID + "_separator", vec2(-1.0f + timePartOffset, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", separatorPartColor, false);
			_fe3d.textEntity_setTextContent(screen->getTextfield(ID + "_separator")->getEntityID(), separatorPartText, _charSize.x, _charSize.y);
			_fe3d.textEntity_setMaxPosition(screen->getTextfield(ID + "_separator")->getEntityID(),
				vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));
		}
		else // Console prints multiple lines reversed
		{
			reverse(messageParts.begin(), messageParts.end());
		}

		// Add textfield for every message part
		for (size_t i = 0; i < messageParts.size(); i++)
		{
			// ID for this message part
			string textfieldID = ID + "_msg_" + to_string(i);

			// Add textfield
			screen->addTextfield(textfieldID, vec2(-1.0f + timePartOffset + separatorPartOffset, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", messagePartColor, false);
			_fe3d.textEntity_setTextContent(screen->getTextfield(textfieldID)->getEntityID(), messageParts[i], _charSize.x, _charSize.y);

			// Add boundaries
			_fe3d.textEntity_setMaxPosition(screen->getTextfield(textfieldID)->getEntityID(),
				vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));

			// If printing the message in multiple parts, time should be printed last
			if ((messageParts.size() > 1) && i == (messageParts.size() - 1))
			{
				// Add time textfield & add boundaries
				screen->addTextfield(ID + "_time", vec2(-1.0f, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", timePartColor, false);
				_fe3d.textEntity_setTextContent(screen->getTextfield(ID + "_time")->getEntityID(), timePartText, _charSize.x, _charSize.y);
				_fe3d.textEntity_setMaxPosition(screen->getTextfield(ID + "_time")->getEntityID(),
					vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));

				// Add separator textfield & add boundaries
				screen->addTextfield(ID + "_separator", vec2(-1.0f + timePartOffset, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", separatorPartColor, false);
				_fe3d.textEntity_setTextContent(screen->getTextfield(ID + "_separator")->getEntityID(), separatorPartText, _charSize.x, _charSize.y);
				_fe3d.textEntity_setMaxPosition(screen->getTextfield(ID + "_separator")->getEntityID(),
					vec2(0.995f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));
			}

			// Update index for Y positioning of next messages
			index++;
		}
	}
	reverse(_consoleMessageStack.begin(), _consoleMessageStack.end()); // Set order back to normal
}