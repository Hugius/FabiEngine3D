#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

class NetworkServerMessage final
{
public:
	NetworkServerMessage(const string& content, const NetworkProtocol protocol);

	// Strings
	const string& getContent() const;

	// Miscellaneous
	const NetworkProtocol getProtocol() const;

private:
	// Strings
	string _content;

	// Miscellaneous
	NetworkProtocol _protocol;
};