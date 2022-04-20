#pragma once

#include "logger_message_type.hpp"

#include <string>

using std::string;

class LoggerMessage final
{
public:
	LoggerMessage(LoggerMessageType type, const string & timestamp, const string & content);

	const LoggerMessageType getType() const;

	const string & getTimestamp() const;
	const string & getContent() const;

private:
	const string _timestamp;
	const string _content;

	const LoggerMessageType _type;
};