#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

class NetworkingServerMessage final
{
public:
	NetworkingServerMessage(const string & content, const NetworkProtocol protocol);

	const string & getContent() const;

	const NetworkProtocol getProtocol() const;

private:
	const string _content;

	const NetworkProtocol _protocol;
};