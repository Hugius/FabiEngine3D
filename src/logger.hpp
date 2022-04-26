#pragma once

#include "logger_message.hpp"
#include "configuration.hpp"

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>

using std::endl;
using std::vector;
using std::string;
using std::cout;
using std::ostringstream;
using std::shared_ptr;

class Logger final
{
public:
	Logger() = delete;

	template<typename T, typename...Rest> static void throwInfo(T first, Rest...rest)
	{
		_print(LoggerMessageType::INFO, first, rest...);
	}
	template<typename T, typename...Rest> static void throwDebug(T first, Rest...rest)
	{
		_print(LoggerMessageType::DEBUG, first, rest...);
	}
	template<typename T, typename...Rest> static void throwWarning(T first, Rest...rest)
	{
		_print(LoggerMessageType::WARNING, first, rest...);

		while(Configuration::getInst().isApplicationExported())
		{

		}
	}
	template<typename T, typename...Rest> static void throwError(T first, Rest...rest)
	{
		_print(LoggerMessageType::ERR, first, rest...);

		while(true)
		{

		}
	}

	static const vector<shared_ptr<LoggerMessage>> & getMessageList()
	{
		return _messageList;
	}

	static unsigned int getMessageCount()
	{
		return _messageCount;
	}

private:
	template<typename T, typename...Rest> static void _print(LoggerMessageType type, T first, Rest&&...rest)
	{
		const auto console = GetStdHandle(STD_OUTPUT_HANDLE);

		auto rawTimestamp = new char[9];
		auto current = time(nullptr);
		auto format = tm();
		localtime_s(&format, &current);
		strftime(rawTimestamp, 9, "%H:%M:%S", &format);
		auto timestamp = string(rawTimestamp);
		delete[] rawTimestamp;

		SetConsoleTextAttribute(console, static_cast<DWORD>(TIMESTAMP_COLOR));

		cout << "[" << timestamp << "] ";

		if(type == LoggerMessageType::INFO)
		{
			SetConsoleTextAttribute(console, static_cast<DWORD>(INFO_COLOR));
		}
		if(type == LoggerMessageType::DEBUG)
		{
			SetConsoleTextAttribute(console, static_cast<DWORD>(DEBUG_COLOR));
		}
		if(type == LoggerMessageType::WARNING)
		{
			SetConsoleTextAttribute(console, static_cast<DWORD>(WARNING_COLOR));
		}
		if(type == LoggerMessageType::ERR)
		{
			SetConsoleTextAttribute(console, static_cast<DWORD>(ERROR_COLOR));
		}

		cout << "[" + TYPE_STRINGS[static_cast<int>(type)] + "]";

		SetConsoleTextAttribute(console, CONTENT_COLOR);

		if((type == LoggerMessageType::DEBUG) || (type == LoggerMessageType::ERR))
		{
			cout << "> ";
		}
		else
		{
			cout << " > ";
		}

		cout << first;
		(cout << ... << rest);
		cout << endl;

		ostringstream oss = {};
		oss << first;
		(oss << ... << rest);

		_messageList.push_back(make_shared<LoggerMessage>(type, timestamp, oss.str()));
		_messageCount++;
	}

	static inline const string TYPE_STRINGS[4] = {"INFO", "DEBUG", "WARN", "ERROR"};

	static inline constexpr int TIMESTAMP_COLOR = 6;
	static inline constexpr int INFO_COLOR = 2;
	static inline constexpr int DEBUG_COLOR = 8;
	static inline constexpr int WARNING_COLOR = 13;
	static inline constexpr int ERROR_COLOR = 12;
	static inline constexpr int CONTENT_COLOR = 15;

	static inline vector<shared_ptr<LoggerMessage>> _messageList = {};

	static inline unsigned int _messageCount = 0;
};