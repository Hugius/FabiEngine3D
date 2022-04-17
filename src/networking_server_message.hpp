#pragma once

#include "networking_protocol_type.hpp"

#include <string>

using std::string;

class NetworkingServerMessage final
{
public:
	NetworkingServerMessage(const string & content, const NetworkingProtocolType protocol);

	const string & getContent() const;

	const NetworkingProtocolType getProtocol() const;

private:
	const string _content;

	const NetworkingProtocolType _protocol;
};