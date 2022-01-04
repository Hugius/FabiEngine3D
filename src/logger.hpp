#pragma once

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

using std::endl;
using std::vector;
using std::string;
using std::cout;
using std::ostringstream;

class Logger final
{
public:
	Logger() = delete;

	template<typename T, typename...Rest> inline static void throwInfo(T first, Rest...rest)
	{
		_printPrefix(MessageType::INFO);
		_printMessage(first, rest...);
	}
	template<typename T, typename...Rest> inline static void throwDebug(T first, Rest...rest)
	{
		_printPrefix(MessageType::DEBUG);
		_printMessage(first, rest...);
	}
	template<typename T, typename...Rest> inline static void throwWarning(T first, Rest...rest)
	{
		_printPrefix(MessageType::WARNING);
		_printMessage(first, rest...);
	}
	template<typename T, typename...Rest> inline static void throwFatalWarning(T first, Rest...rest)
	{
		cout << endl;
		_printPrefix(MessageType::WARNING);
		_printMessage(first, rest...);
		cout << endl;
		throwInfo("Press a key to continue...");
		auto temp = _getch();
		exit(420);
	}
	template<typename T, typename...Rest> inline static void throwError(T first, Rest...rest)
	{
		cout << endl;
		_printPrefix(MessageType::ERR);
		_printMessage(first, rest...);
		cout << endl;
		throwInfo("Press a key to continue...");
		auto temp = _getch();
		exit(420);
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

	inline static const vector<string>& getMessageQueue()
	{
		return _messageQueue;
	}

	inline static unsigned int getMessageCount()
	{
		return _messageCount;
	}

private:
	inline static void _printPrefix(MessageType type)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		ostringstream oss;

		auto timestamp = new char[64];
		auto current = time(nullptr);
		auto format = tm();
		localtime_s(&format, &current);
		strftime(timestamp, 64, "%H:%M:%S", &format);

		SetConsoleTextAttribute(console, 6);
		cout << "[" + _level_string[static_cast<unsigned int>(type)] + "]";
		oss << "[" + _level_string[static_cast<unsigned int>(type)] + "]";
		SetConsoleTextAttribute(console, 12);
		cout << "[" << timestamp << "]";
		oss << "[" << timestamp << "]";
		SetConsoleTextAttribute(console, 7);

		if(type == MessageType::DEBUG || type == MessageType::ERR)
		{
			cout << "> ";
		}
		else
		{
			cout << " > ";
		}

		oss << " > ";
		_messageQueue.push_back(oss.str());
	}
	template<typename T, typename...Rest> inline static void _printMessage(T first, Rest&&...rest)
	{
		ostringstream oss;

		cout << first;
		(cout << ... << rest);
		cout << endl;

		oss << first;
		(oss << ... << rest);

		_messageQueue.back() += oss.str();
		_messageCount++;
	}

	inline static vector<string> _messageQueue;
	inline static string _level_string[4] = {"Info", "Error", "Debug", "Warn"};

	inline static unsigned int _messageCount = 0;
};