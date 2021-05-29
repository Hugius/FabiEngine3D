#pragma once

#pragma warning (disable : 4996)

#define NOMINMAX

#include "message_type.hpp"

#include <conio.h>
#include <windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>

using std::vector;
using std::string;

class Logger final
{
public:
	Logger() = delete;

	template<typename T, typename...Rest> 
	inline static void throwInfo(T first, Rest...rest)
	{
		_printPrefix(MessageType::INFO, first, rest...);
	}

	template<typename T, typename...Rest> 
	inline static void throwError(T first, Rest...rest)
	{
		std::cout << std::endl;
		_printPrefix(MessageType::ERR, first, rest...);
		std::cout << std::endl;
		throwInfo("Type something to quit...");
		auto temp = _getch();
		exit(420);
	}

	template<typename T, typename...Rest> 
	inline static void throwDebug(T first, Rest...rest)
	{
		_printPrefix(MessageType::DEBUG, first, rest...);
	}

	template<typename T, typename...Rest> 
	inline static void throwWarning(T first, Rest...rest)
	{
		_printPrefix(MessageType::WARNING, first, rest...);
	}

	inline static const vector<string>& getMessageQueue()
	{
		return _messageQueue;
	}

	inline static unsigned int getMessageCount()
	{
		return _messageCount;
	}

	inline static void setCustomMessageQueue(const vector<string>& customMessages)
	{
		_messageQueue = customMessages;
	}

	inline static void clearMessageQueue()
	{
		_messageCount = 0;
		_messageQueue.clear();
	}

private:
	inline static string _level_string[4] = { "Info", "Error", "Debug", "Warn" };

	inline static std::vector<string> _messageQueue;
	inline static unsigned int _messageCount = 0;

	template<typename T, typename...Rest> 
	inline static void _printPrefix(MessageType type, T first, Rest&&...rest)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Console access
		std::ostringstream oss; // For message queue

		// Current time
		char timeBuffer[64];
		auto t = std::time(nullptr);
		auto foo = *std::localtime(&t);
		std::strftime(timeBuffer, 64, "%H:%M:%S", &foo);

		SetConsoleTextAttribute(console, 6); // White
		std::cout << "[" + _level_string[static_cast<int>(type)] + "]";
		oss << "[" + _level_string[static_cast<int>(type)] + "]";
		SetConsoleTextAttribute(console, 12); // Red
		std::cout << "[" << timeBuffer << "]";
		oss << "[" << timeBuffer << "]";
		SetConsoleTextAttribute(console, 7); // Yellow

		// Proper indentation
		if (type == MessageType::DEBUG || type == MessageType::ERR) // 5 chars
		{
			std::cout << "> ";
		}
		else // 4 chars
		{
			std::cout << " > ";
		}

		// Add to message queue
		oss << " > ";
		_messageQueue.push_back(oss.str());

		// Print message body
		_printMessage(first, rest...);
	}

	template<typename T, typename...Rest>
	inline static void _printMessage(T first, Rest&&...rest)
	{
		// For message queue
		std::ostringstream oss;

		// Write onto console output
		std::cout << first;
		(std::cout << ... << rest);
		std::cout << std::endl;

		// Write into stream
		oss << first;
		(oss << ... << rest);
		
		// Add to message queue
		_messageQueue.back() += oss.str();
		_messageCount++;
	}
};