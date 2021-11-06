#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

class NetworkClientMessage final
{
public:
	NetworkClientMessage(const string& username, const string& content, const NetworkProtocol protocol);

	// Strings
	const string& getUsername() const;
	const string& getContent() const;

	// Miscellaneous
	const NetworkProtocol getProtocol() const;

private:
	// Strings
	const string _username;
	const string _content;

	// Miscellaneous
	const NetworkProtocol _protocol;
};