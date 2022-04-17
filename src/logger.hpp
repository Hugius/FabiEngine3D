#pragma once

#include "logger_message_type.hpp"
#include "configuration.hpp"

#include <iostream>

#include <string>
#include <vector>
#include <sstream>

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
		_printPrefix(LoggerMessageType::INFO);

		_printMessage(first, rest...);
	}

	template<typename T, typename...Rest> static void throwDebug(T first, Rest...rest)
	{
		_printPrefix(LoggerMessageType::DEBUG);

		_printMessage(first, rest...);
	}

	template<typename T, typename...Rest> static void throwWarning(T first, Rest...rest)
	{
		_printPrefix(LoggerMessageType::WARNING);

		_printMessage(first, rest...);

		while(Configuration::getInst().isApplicationExported())
		{

		}
	}

	template<typename T, typename...Rest> static void throwError(T first, Rest...rest)
	{
		_printPrefix(LoggerMessageType::ERR);

		_printMessage(first, rest...);

		while(true)
		{

		}
	}

	static void setCustomMessageQueue(const vector<string> & customMessages);
	static void clearMessageQueue();

	static const vector<string> & getMessageQueue();

	static unsigned int getMessageCount();

private:
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

	static void _printPrefix(LoggerMessageType type);

	static inline vector<string> _messageQueue = {};

	static inline const string TYPE_STRING[4] = {"Info", "Error", "Debug", "Warn"};

	static inline unsigned int _messageCount = 0;
};