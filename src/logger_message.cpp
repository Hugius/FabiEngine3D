#include "logger_message.hpp"

LoggerMessage::LoggerMessage(LoggerMessageType type, const string & timestamp, const string & content)
	:
	_type(type),
	_timestamp(timestamp),
	_content(content)
{

}

const LoggerMessageType LoggerMessage::getType() const
{
	return _type;
}

const string & LoggerMessage::getTimestamp() const
{
	return _timestamp;
}

const string & LoggerMessage::getContent() const
{
	return _content;
}