#include "logger.hpp"

#include <windows.h>

const vector<string> & Logger::getMessageList()
{
	return _messageList;
}

unsigned int Logger::getMessageCount()
{
	return _messageCount;
}

void Logger::_printPrefix(LoggerMessageType type)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	ostringstream oss;

	auto rawTimestamp = new char[9];
	auto current = time(nullptr);
	auto format = tm();
	localtime_s(&format, &current);
	strftime(rawTimestamp, 9, "%H:%M:%S", &format);
	auto timestamp = string(rawTimestamp);
	delete[] rawTimestamp;

	SetConsoleTextAttribute(console, static_cast<DWORD>(TIME_COLOR));
	cout << "[" << timestamp << "] ";
	oss << "[" << timestamp << "] ";
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
	cout << "[" + TYPE_STRINGS[static_cast<unsigned int>(type)] + "]";
	oss << "[" + TYPE_STRINGS[static_cast<unsigned int>(type)] + "]";
	SetConsoleTextAttribute(console, 15);

	if((type == LoggerMessageType::DEBUG) || (type == LoggerMessageType::ERR))
	{
		cout << "> ";
	}
	else
	{
		cout << " > ";
	}

	oss << " > ";
	_messageList.push_back(oss.str());
}