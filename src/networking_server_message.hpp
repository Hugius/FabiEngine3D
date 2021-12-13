#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

class NetworkingServerMessage final
{
public:
	NetworkingServerMessage(const string& content, const NetworkProtocol protocol);

	// STRING
	const string& getContent() const;

	// MISCELLANEOUS
	const NetworkProtocol getProtocol() const;

private:
	// STRING
	string _content;

	// MISCELLANEOUS
	NetworkProtocol _protocol;
};