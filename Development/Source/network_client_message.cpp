#include "network_client_message.hpp"

NetworkClientMessage::NetworkClientMessage(const string& username, const string& content, const NetworkProtocol protocol)
	:
	_username(username),
	_content(content),
	_protocol(protocol)
{

}

const string& NetworkClientMessage::getUsername() const
{
	return _username;
}

const string& NetworkClientMessage::getContent() const
{
	return _content;
}

const NetworkProtocol NetworkClientMessage::getProtocol() const
{
	return _protocol;
}