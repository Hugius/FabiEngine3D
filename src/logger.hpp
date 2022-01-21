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

	template<typename T, typename...Rest> static void throwInfo(T first, Rest...rest)
	{
		_printPrefix(MessageType::INFO);
		_printMessage(first, rest...);
	}

	template<typename T, typename...Rest> static void throwDebug(T first, Rest...rest)
	{
		_printPrefix(MessageType::DEBUG);
		_printMessage(first, rest...);
	}

	template<typename T, typename...Rest> static void throwWarning(T first, Rest...rest)
	{
		_printPrefix(MessageType::WARNING);
		_printMessage(first, rest...);
	}

	template<typename T, typename...Rest> static void throwFatalWarning(T first, Rest...rest)
	{
		cout << endl;
		_printPrefix(MessageType::WARNING);
		_printMessage(first, rest...);
		cout << endl;
		throwInfo("Press a key to continue...");
		auto temp = _getch();
		exit(420);
	}

	template<typename T, typename...Rest> static void throwError(T first, Rest...rest)
	{
		cout << endl;
		_printPrefix(MessageType::ERR);
		_printMessage(first, rest...);
		cout << endl;
		throwInfo("Press a key to continue...");
		auto temp = _getch();
		exit(420);
	}

	static void setCustomMessageQueue(const vector<string>& customMessages);
	static void clearMessageQueue();

	static const vector<string>& getMessageQueue();

	static unsigned int getMessageCount();

private:
	static void _printPrefix(MessageType type);

	template<typename T, typename...Rest> static void _printMessage(T first, Rest&&...rest)
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

	static inline vector<string> _messageQueue = {};

	static inline const string TYPE_STRING[4] = {"Info", "Error", "Debug", "Warn"};

	static inline unsigned int _messageCount = 0;
};