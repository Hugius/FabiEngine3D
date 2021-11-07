#include "network_server_message.hpp"

NetworkServerMessage::NetworkServerMessage(const string& content, const NetworkProtocol protocol)
	:
	_content(content),
	_protocol(protocol)
{

}

const string& NetworkServerMessage::getContent() const
{
	return _content;
}

const NetworkProtocol NetworkServerMessage::getProtocol() const
{
	return _protocol;
}