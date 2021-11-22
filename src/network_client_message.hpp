#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

class NetworkClientMessage final
{
public:
	NetworkClientMessage(const string& username, const string& content, const NetworkProtocol protocol);

	// STRING
	const string& getUsername() const;
	const string& getContent() const;

	// Miscellaneous
	const NetworkProtocol getProtocol() const;

private:
	// STRING
	string _username;
	string _content;

	// Miscellaneous
	NetworkProtocol _protocol;
};