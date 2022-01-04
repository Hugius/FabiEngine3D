#include "networking_server_message.hpp"

NetworkingServerMessage::NetworkingServerMessage(const string& content, const NetworkProtocol protocol)
	:
	_content(content),
	_protocol(protocol)
{

}

const string& NetworkingServerMessage::getContent() const
{
	return _content;
}

const NetworkProtocol NetworkingServerMessage::getProtocol() const
{
	return _protocol;
}