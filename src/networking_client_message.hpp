#pragma once

#include "network_protocol.hpp"

#include <string>

using std::string;

class NetworkingClientMessage final
{
public:
	NetworkingClientMessage(const string& username, const string& content, const NetworkProtocol protocol);

	// STRING
	const string& getUsername() const;
	const string& getContent() const;

	// MISCELLANEOUS
	const NetworkProtocol getProtocol() const;

private:
	// STRING
	string _username;
	string _content;

	// MISCELLANEOUS
	NetworkProtocol _protocol;
};