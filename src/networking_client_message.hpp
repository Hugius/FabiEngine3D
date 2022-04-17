#pragma once

#include "networking_protocol_type.hpp"

#include <string>

using std::string;

class NetworkingClientMessage final
{
public:
	NetworkingClientMessage(const string & username, const string & content, const NetworkingProtocolType protocol);

	const string & getUsername() const;
	const string & getContent() const;

	const NetworkingProtocolType getProtocol() const;

private:
	const string _username;
	const string _content;

	const NetworkingProtocolType _protocol;
};