#include "bottom_viewport_controller.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.04f, 2.0f)

void BottomViewportController::initialize()
{
	// Bottom-viewport: statistics
	_gui->getViewport("bottom")->addWindow("statistics", vec2(-0.25f, 0.0f), vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui->getViewport("bottom")->getWindow("statistics")->addScreen("main");
	_gui->getViewport("bottom")->getWindow("statistics")->setActiveScreen("main");
	_statsScreen = _gui->getViewport("bottom")->getWindow("statistics")->getScreen("main");

	// General statistics
	_statsScreen->addTextfield("fps", vec2(-1.0f, 0.85f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("gpuName", vec2(-1.0f, 0.7f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("openglVersion", vec2(-1.0f, 0.55f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cameraPosition", vec2(-1.0f, 0.4f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cameraYawPitch", vec2(-1.0f, 0.25f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cursorPosition", vec2(-1.0f, 0.1f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("triangleCount", vec2(-1.0f, -0.05f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("gameEntityCount", vec2(-1.0f, -0.2f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("billboardEntityCount", vec2(-1.0f, -0.35f), vec2(0.0f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("lightEntityCount", vec2(-1.0f, -0.5f), vec2(0.0f), "", vec3(1.0f), false);

	// Performance profiling
	auto performanceStats = _fe3d.misc_getPerformanceProfilingStatistics();
	int counter = 1;
	for (auto& [key, value] : performanceStats)
	{
		_statsScreen->addTextfield(key, vec2(-0.25f, 1.0f - (static_cast<float>(counter) * 0.15f)), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
		counter++;
	}

	// Console window
	_gui->getViewport("bottom")->addWindow("console", vec2(0.25f, 0.0f), vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui->getViewport("bottom")->getWindow("console")->addScreen("main");
	_gui->getViewport("bottom")->getWindow("console")->setActiveScreen("main");
}

void BottomViewportController::update()
{
	// Update FPS
	static float totalFPS = 0.0f;
	static int fpsCount = 0;
	if (_fe3d.misc_checkInterval("fps", 50))
	{
		string fpsTextID = _statsScreen->getTextfield("fps")->getEntityID();
		string text = "FPS: " + to_string(static_cast<int>(totalFPS / fpsCount));
		_fe3d.textEntity_setTextContent(fpsTextID, text, _charSize.x, _charSize.y);
		totalFPS = 0.0f;
		fpsCount = 0;
	}
	else
	{
		totalFPS += _fe3d.misc_getFPS();
		fpsCount++;
	}

	// Update GPU stats
	if (_fe3d.misc_checkInterval("gpuName", 10000))
	{
		string textID = _statsScreen->getTextfield("gpuName")->getEntityID();
		string text = "GPU: " + _fe3d.misc_getGpuName();
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update OpenGL version
	if (_fe3d.misc_checkInterval("openglVersion", 10000))
	{
		string textID = _statsScreen->getTextfield("openglVersion")->getEntityID();
		string text = "OpenGL version: " + _fe3d.misc_getOpenglVersion();
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update camera position
	if (_fe3d.misc_checkInterval("cameraPosition", 1))
	{
		string textID = _statsScreen->getTextfield("cameraPosition")->getEntityID();
		string text = "Camera position: " + _fe3d.misc_vec2str(ivec3(_fe3d.camera_getPosition()));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update camera pitch & yaw
	if (_fe3d.misc_checkInterval("cameraYawPitch", 1))
	{
		string textID = _statsScreen->getTextfield("cameraYawPitch")->getEntityID();
		string text = "Camera yaw & pitch: " + 
			to_string(static_cast<int>(_fe3d.camera_getYaw())) + " " + to_string(static_cast<int>(_fe3d.camera_getPitch()));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update cursor position
	if (_fe3d.misc_checkInterval("cursorPosition", 1))
	{
		string textID = _statsScreen->getTextfield("cursorPosition")->getEntityID();
		string text = "Raycast position: " + _fe3d.misc_vec2str(ivec3(_fe3d.terrainEntity_getMousePoint()));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update triangle count
	if (_fe3d.misc_checkInterval("triangleCount", 10))
	{
		string textID = _statsScreen->getTextfield("triangleCount")->getEntityID();
		string text = "Triangles: " + to_string(static_cast<int>(_fe3d.misc_getTriangleCount()));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update game entity count
	if (_fe3d.misc_checkInterval("gameEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("gameEntityCount")->getEntityID();

		int total = 0;
		for (auto& ID : _fe3d.gameEntity_getAllIDs())
		{
			if (_fe3d.gameEntity_isVisible(ID))
			{
				total++;
			}
		}

		string text = "Game entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update billboard entity count
	if (_fe3d.misc_checkInterval("billboardEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("billboardEntityCount")->getEntityID();

		int total = 0;
		for (auto& ID : _fe3d.billboardEntity_getAllIDs())
		{
			if (_fe3d.billboardEntity_isVisible(ID))
			{
				total++;
			}
		}

		string text = "Billboard entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update light entity count
	if (_fe3d.misc_checkInterval("lightEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("lightEntityCount")->getEntityID();

		int total = 0;
		for (auto& ID : _fe3d.lightEntity_getAllIDs())
		{
			if (_fe3d.lightEntity_isVisible(ID))
			{
				total++;
			}
		}

		string text = "Light entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update performance profiling
	if (_fe3d.misc_checkInterval("performanceProfiling", 50))
	{
		auto performanceStats = _fe3d.misc_getPerformanceProfilingStatistics();
		for (auto& [key, value] : performanceStats)
		{
			string textID = _statsScreen->getTextfield(key)->getEntityID();
			_fe3d.textEntity_setTextContent(textID, key + ": " + to_string(value) + "%", _charSize.x, _charSize.y);
		}
	}

	// Synchronize console text with core logger
	auto loggerMessages = _fe3d.logger_getMessageStack();
	if (_consoleMessageStack.size() != loggerMessages.size())
	{
		auto synchronizationCount = loggerMessages.size() - _consoleMessageStack.size();

		// Synchronize messages
		for (size_t i = loggerMessages.size() - synchronizationCount; i < loggerMessages.size(); i++)
		{
			_addConsoleMessage(loggerMessages[i]);
		}
	}

	// Update console window
	_updateConsoleScrolling();
}

void BottomViewportController::_updateConsoleScrolling()
{
	// No scrolling for empty console
	if (!_consoleMessageStack.empty())
	{
		// Handy values
		auto window = _gui->getViewport("bottom")->getWindow("console");
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
	auto window = _gui->getViewport("bottom")->getWindow("console");
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
		for (unsigned int i = 0; i < message.size(); i++)
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
		begin:for (unsigned int i = 0; i < messagePartText.size(); i++)
		{
			// Check if message length is bigger than window size
			float offset = _charSize.x * static_cast<float>(timePartLength + 1);
			if (offset + (i * _charSize.x) > window->getOriginalSize().x)
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
				vec2(0.99f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));

			// Add separator textfield & add boundaries
			screen->addTextfield(ID + "_separator", vec2(-1.0f + timePartOffset, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", separatorPartColor, false);
			_fe3d.textEntity_setTextContent(screen->getTextfield(ID + "_separator")->getEntityID(), separatorPartText, _charSize.x, _charSize.y);
			_fe3d.textEntity_setMaxPosition(screen->getTextfield(ID + "_separator")->getEntityID(),
				vec2(0.99f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));
		}
		else // Console prints multiple lines reversed
		{
			reverse(messageParts.begin(), messageParts.end());
		}

		// Add textfield for every message part
		for (unsigned int i = 0; i < messageParts.size(); i++)
		{
			// ID for this message part
			string textfieldID = ID + "_msg_" + to_string(i);

			// Add textfield
			screen->addTextfield(textfieldID, vec2(-1.0f + timePartOffset + separatorPartOffset, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", messagePartColor, false);
			_fe3d.textEntity_setTextContent(screen->getTextfield(textfieldID)->getEntityID(), messageParts[i], _charSize.x, _charSize.y);

			// Add boundaries
			_fe3d.textEntity_setMaxPosition(screen->getTextfield(textfieldID)->getEntityID(),
				vec2(0.99f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));

			// If printing the message in multiple parts, time should be printed last
			if ((messageParts.size() > 1) && i == (messageParts.size() - 1))
			{
				// Add time textfield & add boundaries
				screen->addTextfield(ID + "_time", vec2(-1.0f, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", timePartColor, false);
				_fe3d.textEntity_setTextContent(screen->getTextfield(ID + "_time")->getEntityID(), timePartText, _charSize.x, _charSize.y);
				_fe3d.textEntity_setMaxPosition(screen->getTextfield(ID + "_time")->getEntityID(),
					vec2(0.99f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));

				// Add separator textfield & add boundaries
				screen->addTextfield(ID + "_separator", vec2(-1.0f + timePartOffset, -0.85f + static_cast<float>(index) * yOffset), vec2(0.0f), "", separatorPartColor, false);
				_fe3d.textEntity_setTextContent(screen->getTextfield(ID + "_separator")->getEntityID(), separatorPartText, _charSize.x, _charSize.y);
				_fe3d.textEntity_setMaxPosition(screen->getTextfield(ID + "_separator")->getEntityID(),
					vec2(0.99f, window->getOriginalPosition().y + (window->getOriginalSize().y / 2.0f)));
			}

			// Update index for Y positioning of next messages
			index++;
		}
	}
	reverse(_consoleMessageStack.begin(), _consoleMessageStack.end()); // Set order back to normal
}