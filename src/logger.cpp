#include "logger.hpp"

void Logger::setCustomMessageQueue(const vector<string>& customMessages)
{
	_messageQueue = customMessages;
}

void Logger::clearMessageQueue()
{
	_messageCount = 0;
	_messageQueue.clear();
}

const vector<string>& Logger::getMessageQueue()
{
	return _messageQueue;
}

unsigned int Logger::getMessageCount()
{
	return _messageCount;
}

void Logger::_printPrefix(MessageType type)
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

	SetConsoleTextAttribute(console, 6);
	cout << "[" + LEVEL_STRING[static_cast<unsigned int>(type)] + "]";
	oss << "[" + LEVEL_STRING[static_cast<unsigned int>(type)] + "]";
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